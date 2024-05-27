#include "thumbstick.h"
#include "print.h"

void thumbstick_init(void) {
    thumbstickTimer       = 0;
    thumbstickScrollTimer = 0;

    thumbstick_state.config.mode           = THUMBSTICK_MODE_MOUSE;
    thumbstick_state.config.deadZone       = THUMBSTICK_DEAD_ZONE;
    thumbstick_state.config.fineZone       = THUMBSTICK_FINE_ZONE;
    thumbstick_state.config.speed          = THUMBSTICK_SPEED;
    thumbstick_state.config.fineSpeed      = THUMBSTICK_FINE_SPEED;
    thumbstick_state.config.axisSeparation = THUMBSTICK_AXIS_SEPARATION;
    thumbstick_state.config.eightAxis      = THUMBSTICK_EIGHT_AXIS;

#if defined THUMBSTICK_DEBUG
    rawX               = 0;
    rawY               = 0;
    distX              = 0;
    distY              = 0;
    thumbstickLogTimer = 0;
#endif
}

// Axis-level wrapper to read raw value, do logging and calculate speed
int16_t thumbstick_get_component(uint8_t pin) {
    uint16_t analogValue = analogReadPin(pin);
    // Compute direction
    bool directionIsPositive = (analogValue > THUMBSTICK_RANGE_CENTER);
    // Compute distance from the center
    uint16_t distance = directionIsPositive ? (analogValue - THUMBSTICK_RANGE_CENTER) : (THUMBSTICK_RANGE_CENTER - analogValue);
#if defined THUMBSTICK_DEBUG
    if (pin == THUMBSTICK_PIN_X) {
        rawX  = analogValue;
        distX = distance;
    } else {
        rawY  = analogValue;
        distY = distance;
    }
#endif
    // Compute component (range of [0 to 1023])
    return directionIsPositive ? distance : -(int16_t)distance;
}

void thumbstick_mode_set(thumbstick_mode_t mode) { thumbstick_state.config.mode = mode; }

thumbstick_mode_t thumbstick_mode_get(void) { return thumbstick_state.config.mode; }

/* 在mode列表中切换mode模式，reverse决定是否逆序切换 */
void thumbstick_mode_cycle(bool reverse) {
    thumbstick_mode_t mode = thumbstick_mode_get();
    if (reverse) {
        mode = (mode == 0) ? (_THUMBSTICK_MODE_LAST - 1) : (mode - 1);
    } else {
        mode = (mode == (_THUMBSTICK_MODE_LAST - 1)) ? 0 : (mode + 1);
    }
    thumbstick_mode_set(mode);
}

// Get mouse speed
int16_t thumbstick_get_mouse_speed(int16_t component) {
    int16_t  maxSpeed;
    uint16_t distance = abs(component);
    if (distance > THUMBSTICK_FINE_ZONE) {
        maxSpeed = THUMBSTICK_SPEED;
    } else if (distance > THUMBSTICK_DEAD_ZONE) {
        maxSpeed = THUMBSTICK_FINE_SPEED;
    } else {
	    return 0;
    }
    /* component 是遥杆当前的偏移量，取值范围为 [-THUMBSTICK_RANGE_CENTER, THUMBSTICK_RANGE_CENTER]。
     * maxSpeed 是根据偏移量确定的最大速度。
     * THUMBSTICK_RANGE_CENTER 是遥杆的中心点，通常是轴线的中点。
     * 这个计算公式的核心思想是将 component 的偏移量按比例缩放到 maxSpeed 范围内，以确保最终的速度是一个合理的值
     * 由于 component 可以是正数或负数，公式能够正确处理不同方向的输入
     * 这种计算方法有效地将遥杆的物理偏移量转换为对应的鼠标速度，保证了输入设备的线性响应和用户体验的平滑性
     * */
    return (float)maxSpeed * component / THUMBSTICK_RANGE_CENTER;
}

// Fix direction within one of 8 axes (or 4 if 8-axis is disabled)
thumbstick_direction_t thumbstick_get_discretized_direction(thumbstick_vector_t vector, float axisSeparation, bool eightAxis) {
    thumbstick_direction_t direction;
    uint16_t               absX                = abs(vector.x);
    uint16_t               absY                = abs(vector.y);
    uint16_t               maxComponent        = (absX > absY) ? absX : absY;
    bool                   insideDeadZone      = (maxComponent <= THUMBSTICK_DEAD_ZONE);
    /* 判断当前摇杆位置是否贴近x或y轴 */
    bool                   outsideDiagonalZone = ((abs(absX - absY) / (float)maxComponent) >= axisSeparation);
    if (insideDeadZone) {
        direction.up = direction.down = direction.left = direction.right = false;
    } else {
        direction.up    = (vector.y < 0);
        direction.down  = (vector.y > 0);
        direction.left  = (vector.x < 0);
        direction.right = (vector.x > 0);
	//在正确的条件下，只保留主导的方向
        // Let only the dominant direction remain under the right conditions
        if (outsideDiagonalZone || !eightAxis) {
            if (absX > absY) {
                direction.up = direction.down = false;
            } else {
                direction.left = direction.right = false;
            }
        }
    }
    return direction;
}

thumbstick_direction_t scrollDirection;  // Declaring global to save stack space
void                   thumbstick_process(void) {
    if (timer_elapsed(thumbstickTimer) > THUMBSTICK_TIMEOUT) {
        thumbstickTimer = timer_read();
#ifndef THUMBSTICK_FLIP_X
        thumbstick_state.vector.x = thumbstick_get_component(THUMBSTICK_PIN_X);
#else
        thumbstick_state.vector.x = -thumbstick_get_component(THUMBSTICK_PIN_X);
#endif
#ifndef THUMBSTICK_FLIP_Y
        thumbstick_state.vector.y = thumbstick_get_component(THUMBSTICK_PIN_Y);
#else
        thumbstick_state.vector.y = -thumbstick_get_component(THUMBSTICK_PIN_Y);
#endif
        switch (thumbstick_state.config.mode) {
            case THUMBSTICK_MODE_MOUSE:
                thumbstick_state.report.x = thumbstick_get_mouse_speed(thumbstick_state.vector.x);
                thumbstick_state.report.y = thumbstick_get_mouse_speed(thumbstick_state.vector.y);
                break;

            case THUMBSTICK_MODE_USE_VIA_SET:
            case THUMBSTICK_MODE_ARROWS:
                thumbstick_state.direction = thumbstick_get_discretized_direction(thumbstick_state.vector, thumbstick_state.config.axisSeparation, thumbstick_state.config.eightAxis);
                break;
            case THUMBSTICK_MODE_SCROLL:
                if (timer_elapsed(thumbstickScrollTimer) > THUMBSTICK_SCROLL_TIMEOUT) {
                    thumbstickScrollTimer     = timer_read();
                    scrollDirection           = thumbstick_get_discretized_direction(thumbstick_state.vector, thumbstick_state.config.axisSeparation, false);
                    thumbstick_state.report.v = (scrollDirection.up || scrollDirection.down) ? (scrollDirection.up ? THUMBSTICK_SCROLL_SPEED : -THUMBSTICK_SCROLL_SPEED) : 0;
                    thumbstick_state.report.h = (scrollDirection.left || scrollDirection.right) ? (scrollDirection.left ? -THUMBSTICK_SCROLL_SPEED : THUMBSTICK_SCROLL_SPEED) : 0;
                } else {
                    thumbstick_state.report.v = thumbstick_state.report.h = 0;
                }
                break;
//TODO
                break;
            default:
                break;
        }
    }
}

void update_keycode_status(uint16_t keycode, bool last, bool current) {
    if (last != current) {
        if (current) {
            register_code16(keycode);
        } else {
            unregister_code16(keycode);
        }
    }
}

void pointing_device_init(void) { thumbstick_init(); }

void pointing_device_task(void) {
    report_mouse_t report = pointing_device_get_report();

#ifndef THUMBSTICK_POSITION
#define THUMBSTICK_POSITION 0
#endif

#if THUMBSTICK_POSITION == 1
    if (!isLeftHand)
#elif THUMBSTICK_POSITION == 0
    if (isLeftHand)
#endif /* THUMBSTICK_POSITION */
    {
        thumbstick_process();
        switch (thumbstick_state.config.mode) {
            case THUMBSTICK_MODE_MOUSE:
                report.x = thumbstick_state.report.x;
                report.y = thumbstick_state.report.y;
#ifdef THUMBSTICK_DEBUG
                if (timer_elapsed(thumbstickLogTimer) > 100) {
                    thumbstickLogTimer = timer_read();
                    uprintf("Raw (%d, %d); Dist (%u, %u); Vec (%d, %d);\n", rawX, rawY, distX, distY, thumbstick_state.vector.x, thumbstick_state.vector.y);
                }
#endif
                break;
	    case THUMBSTICK_MODE_USE_VIA_SET:
		if (isLeftHand) {
			update_keycode_status(dynamic_keymap_get_keycode(biton32(layer_state),LEFT_JOY_POS_UP), thumbstick_state.lastDirection.up, thumbstick_state.direction.up);
			update_keycode_status(dynamic_keymap_get_keycode(biton32(layer_state),LEFT_JOY_POS_DOWN), thumbstick_state.lastDirection.down, thumbstick_state.direction.down);
			update_keycode_status(dynamic_keymap_get_keycode(biton32(layer_state),LEFT_JOY_POS_LEFT), thumbstick_state.lastDirection.left, thumbstick_state.direction.left);
			update_keycode_status(dynamic_keymap_get_keycode(biton32(layer_state),LEFT_JOY_POS_RIGHT), thumbstick_state.lastDirection.right, thumbstick_state.direction.right);
		} else {
			update_keycode_status(dynamic_keymap_get_keycode(biton32(layer_state),RIGHT_JOY_POS_UP), thumbstick_state.lastDirection.up, thumbstick_state.direction.up);
			update_keycode_status(dynamic_keymap_get_keycode(biton32(layer_state),RIGHT_JOY_POS_DOWN), thumbstick_state.lastDirection.down, thumbstick_state.direction.down);
			update_keycode_status(dynamic_keymap_get_keycode(biton32(layer_state),RIGHT_JOY_POS_LEFT), thumbstick_state.lastDirection.left, thumbstick_state.direction.left);
			update_keycode_status(dynamic_keymap_get_keycode(biton32(layer_state),RIGHT_JOY_POS_RIGHT), thumbstick_state.lastDirection.right, thumbstick_state.direction.right);
		}
		thumbstick_state.lastDirection = thumbstick_state.direction;
#ifdef THUMBSTICK_DEBUG
                if (timer_elapsed(thumbstickLogTimer) > 100) {
                    thumbstickLogTimer = timer_read();
                    uprintf("Up_Via %d; Down_Via %d; Left_Via: %d; Right_Via %d; Vec (%d, %d);\n", thumbstick_state.lastDirection.up, thumbstick_state.lastDirection.down, thumbstick_state.lastDirection.left, thumbstick_state.lastDirection.right, thumbstick_state.vector.x, thumbstick_state.vector.y);
                }
#endif
                break;
            case THUMBSTICK_MODE_ARROWS:
                update_keycode_status(KC_UP, thumbstick_state.lastDirection.up, thumbstick_state.direction.up);
                update_keycode_status(KC_DOWN, thumbstick_state.lastDirection.down, thumbstick_state.direction.down);
                update_keycode_status(KC_LEFT, thumbstick_state.lastDirection.left, thumbstick_state.direction.left);
                update_keycode_status(KC_RIGHT, thumbstick_state.lastDirection.right, thumbstick_state.direction.right);
                thumbstick_state.lastDirection = thumbstick_state.direction;
#ifdef THUMBSTICK_DEBUG
                if (timer_elapsed(thumbstickLogTimer) > 100) {
                    thumbstickLogTimer = timer_read();
                    uprintf("Up %d; Down %d; Left: %d; Right %d; Vec (%d, %d);\n", thumbstick_state.lastDirection.up, thumbstick_state.lastDirection.down, thumbstick_state.lastDirection.left, thumbstick_state.lastDirection.right, thumbstick_state.vector.x, thumbstick_state.vector.y);
                }
#endif
                break;
            case THUMBSTICK_MODE_SCROLL:
                report.v = thumbstick_state.report.v;
                report.h = thumbstick_state.report.h;
#ifdef THUMBSTICK_DEBUG
                if (timer_elapsed(thumbstickLogTimer) > 100) {
                    thumbstickLogTimer = timer_read();
                    uprintf("Scroll (%d, %d)\n", report.h, report.v);
                }
#endif
                break;
            default:
                break;
        }
    }
    pointing_device_set_report(report);
    pointing_device_send();
}
