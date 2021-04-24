/* Copyright 2020 Leo Dias
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "print.h"
#include "thumbstick.h"

#ifdef THUMBSTICK_ENABLE

#endif
// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY,
  _RAISE,
  _LOWER,
  _ADJUST

};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* OWERTY
 * |-----------------------------------------------------.                    .-----------------------------------------------------|
 * |KC_ESC     KC_Q     KC_W     KC_E     KC_R     KC_T                          KC_Y     KC_U    KC_I      KC_O    KC_P    KC_BSPC |
 * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 * |KC_LSFT    KC_A     KC_S     KC_D     KC_F     KC_G                          KC_H     KC_J    KC_K      KC_L    KC_SCLN KC_QUOT |
 * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 * |KC_LCTL    KC_Z     KC_X     KC_C     KC_V     KC_B                          KC_N     KC_M    KC_COMM   KC_DOT  KC_SLSH  KC_ENT |
 * |--------+--------+--------+--------+--------+--------+---------|  |-------+--------+--------+--------+--------+--------+--------|
 *                      COPY     LOWER    KC_LGUI  *KC_SPC  KC_ALT |  | KC_ALT   KC_SPC  KC_LGUI  RAISE    PASTE
 *                                       |-------------------------|  |---------------------------|
 */
[_QWERTY] = LAYOUT_void_ergo(
    KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,           KC_T,                    KC_Y,      KC_U,   KC_I,                                       KC_O,       KC_P,       KC_BSPC,
    KC_LSFT,    KC_A,       KC_S,       KC_D,       KC_F,           KC_G,                    KC_H,      KC_J,   KC_K,                                       KC_L,       KC_SCLN,    KC_QUOT,
    KC_LCTL,    KC_Z,       KC_X,       KC_C,       KC_V,           KC_B,                    KC_N,      KC_M,   KC_COMM,                                    KC_DOT,     KC_SLSH,    KC_ENT,
                LGUI(KC_C), MO(_LOWER), KC_LGUI,    KC_SPC,         KC_LAPO,                 KC_RAPC,   KC_SPC, LM(_LOWER, MOD_LCTL | MOD_LALT | MOD_LGUI), MO(_RAISE), LGUI(KC_V)
),
/* _LOWER
 * |-----------------------------------------------------.                    .-----------------------------------------------------|
 * |KC_TAB   KC_EXLM    KC_AT   KC_HASH  KC_DLR   KC_PERC                      KC_CIRC   KC_AMPR  KC_ASTR  KC_LBRC  KC_RBRC  KC_DEL |
 * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 * |KC_LSFT    KC_A     KC_S     ----     KC_UP    ----                          KC_M    KC_UP     ----    KC_MINS  KC_EQL  KC_BSLS |
 * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 * |KC_LCTL    KC_Z     ----   KC_LEFT  KC_DOWN   KC_RIGHT                      KC_LEFT  KC_DOWN  KC_RIGHT   ----   KC_SLSH  KC_ENT |
 * |--------+--------+--------+--------+--------+--------+---------|  |-------+--------+--------+--------+--------+--------+--------|
 *                      COPY     LOWER    KC_LGUI  *KC_SPC  KC_ALT |  | KC_ALT   KC_SPC  KC_LGUI  RAISE    KC_MUTE
 *                                       |-------------------------|  |---------------------------|
 */
[_LOWER] = LAYOUT_void_ergo(
    KC_TAB,     KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,         KC_PERC,                 KC_CIRC,   KC_AMPR,    KC_ASTR,    KC_LBRC,    KC_RBRC,    KC_DEL,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_NO,      KC_UP,          KC_NO,                   KC_M,      KC_UP,      KC_NO,      KC_MINS,    KC_EQL,     KC_BSLS,
    KC_TRNS,    KC_TRNS,    KC_NO,      KC_LEFT,    KC_DOWN,        KC_RIGHT,                KC_LEFT,   KC_DOWN,    KC_RIGHT,   KC_NO,      KC_TRNS,    KC_TRNS,
                KC_TRNS,    MO(_LOWER), KC_TRNS,    KC_TRNS,        KC_TRNS,                 KC_TRNS,   KC_TRNS,    KC_TRNS,    MO(_RAISE), KC_MUTE
),
/* _RAISE
 * |-----------------------------------------------------.                    .-----------------------------------------------------|
 * |KC_GRAVE   KC_1     KC_2     KC_3     KC_4     KC_5                          KC_6     KC_7    KC_8      KC_9    KC_0    KC_BSPC |
 * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 * |KC_LSFT    KC_F1    KC_F2    KC_F3    KC_F4    KC_F5                         KC_F6    KC_F7   KC_F8     KC_F9   KC_F10  KC_QUOT |
 * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 * |KC_LCTL    KC_Z     KC_X     KC_C     KC_V     KC_B                          KC_F11   KC_F12  KC_COMM   KC_DOT  KC_SLSH  KC_ENT |
 * |--------+--------+--------+--------+--------+--------+---------|  |-------+--------+--------+--------+--------+--------+--------|
 *                      KC_MPLY  LOWER    KC_LGUI  *KC_SPC  KC_ALT |  | KC_ALT   KC_SPC  KC_LGUI  RAISE    PASTE
 *                                       |-------------------------|  |---------------------------|
 */
[_RAISE] = LAYOUT_void_ergo(
    KC_GRAVE,   KC_1,       KC_2,       KC_3,       KC_4,           KC_5,                    KC_6,      KC_7,       KC_8,       KC_9,       KC_0,       KC_TRNS,
    KC_TRNS,    KC_F1,      KC_F2,      KC_F3,      KC_F4,          KC_F5,                   KC_F6,     KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,                 KC_F11,    KC_F12,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_MPLY,    MO(_LOWER), KC_TRNS,    KC_TRNS,        KC_TRNS,                 KC_TRNS,   KC_TRNS,    KC_TRNS,    MO(_RAISE), KC_TRNS
),
  [_ADJUST] = LAYOUT_void_ergo(
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,                 KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,                 KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,                 KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        RESET,                   RESET,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    print("..::DEBUG::..\n");
    #ifdef THUMBSTICK_ENABLE
        print(":) THUMBSTICK_ENABLED!\n");
    #endif
    #ifdef THUMBSTICK_DEBUG
        print("THUMBSTICK_DEBUG!\n");
    #endif
    switch (keycode) {
        #ifdef THUMBSTICK_ENABLE
            case TMB_MODE:
                if (record->event.pressed) {
                    thumbstick_mode_cycle(false);
                }
        #endif
    }
    print("..::END_DEBUG::..\n");
    return true;
}

void matrix_scan_user(void) {
//     if (tabbing) {
//         if (timer_elapsed(tabtimer) > TABBING_TIMER) {
//             unregister_code(KC_LALT);
//             tabbing = false;
//         }
//     }
        // dprint("..::matrix_scan_user::..");
        // #ifdef THUMBSTICK_ENABLE
        //     dprint("THUMBSTICK_ENABLE");
        // #endif
 }
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  print("keyboard_post_init_user ;)");
  #ifdef THUMBSTICK_ENABLE
    print("THUMBSTICK_ENABLE");
  #endif
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;
}
