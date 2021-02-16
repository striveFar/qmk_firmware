/* Copyright 2020 Victor Lucachi
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
 * |KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC  |
 * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 * |KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT |
 * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 * |KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT |
 * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
 *                         KC_NO, KC_NO, KC_LGUI,   LOWER,  KC_SPC|  |  KC_ENT,  RAISE,  KC_RALT, KC_NO, KC_NO
 *                                       |------------------------|  |--------------------------|
 */
[_QWERTY] = LAYOUT_void_ergo(
    KC_ESC,     KC_Q,         KC_W,       KC_E,       KC_R,     KC_T,                     KC_Y,       KC_U,       KC_I,        KC_O,        KC_P,     KC_BSPC,
    KC_LSFT,    KC_A,         KC_S,       KC_D,       KC_F,     KC_G,                     KC_H,       KC_J,       KC_K,        KC_L,        KC_SCLN,  KC_QUOT,
    KC_LCTL,    KC_Z,         KC_X,       KC_C,       KC_V,     KC_B,                     KC_N,       KC_M,       KC_COMM,     KC_DOT,      KC_SLSH,  KC_ENT,
                LGUI(KC_C),   MO(_LOWER), KC_LGUI,    KC_SPC,   KC_LALT,                  KC_RALT,    KC_SPC,     KC_RGUI,     MO(_RAISE),  LGUI(KC_V)
),

[_LOWER] = LAYOUT_void_ergo(
    KC_TAB,     KC_EXLM,  KC_AT,      KC_HASH,    KC_DLR,   KC_PERC,                   KC_CIRC,    KC_AMPR,   KC_ASTR,     KC_LPRN,     KC_RPRN,  KC_TRNS,
    KC_TRNS,    KC_NO,    KC_UP,      KC_NO,      KC_NO,    KC_NO,                     KC_NO,      KC_UP,     KC_NO,       KC_NO,       KC_NO,    KC_TRNS,
    KC_TRNS,    KC_LEFT,  KC_DOWN,    KC_RIGHT,   KC_NO,    KC_NO,                     KC_LEFT,    KC_DOWN,   KC_RIGHT,    KC_NO,       KC_TRNS,  KC_TRNS,
                KC_TRNS,  MO(_LOWER), KC_TRNS,    KC_TRNS,  KC_TRNS,                   KC_TRNS,    KC_TRNS,   KC_TRNS,     MO(_RAISE),  KC_MUTE
),
[_RAISE] = LAYOUT_void_ergo(
    KC_1,       KC_2,     KC_3,       KC_4,       KC_5,     KC_6,                      KC_7,       KC_8,      LT(_ADJUST, KC_9),  LT(_ADJUST,  KC_0),   LT(_ADJUST, KC_MINS),  LT(_ADJUST, KC_EQL),
    KC_F1,      KC_F2,    KC_F3,      KC_F4,      KC_F5,    KC_F6,                     KC_F7,      KC_F8,     LT(_ADJUST, KC_F9), LT(_ADJUST,  KC_F10), KC_F11,                KC_F12,
    KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,                   KC_TRNS,    KC_TRNS,   KC_TRNS,            KC_TRNS,              KC_TRNS,               KC_TRNS,
                KC_MPLY,  MO(_LOWER), KC_TRNS,    KC_TRNS,  KC_TRNS,                   KC_TRNS,    KC_TRNS,   KC_TRNS,            MO(_RAISE),           KC_TRNS
),
  [_ADJUST] = LAYOUT_void_ergo(
    KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,                  KC_TRNS,     KC_TRNS,   KC_LPRN,           KC_RPRN,               KC_UNDS,               KC_PLUS,
    KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,                  KC_TRNS,     KC_TRNS,   KC_LCBR,           KC_RCBR,               KC_TRNS,               KC_TRNS,
    KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,                  KC_TRNS,     KC_TRNS,   KC_TRNS,           KC_TRNS,               KC_TRNS,               KC_TRNS,
                KC_MPLY,  KC_TRNS,    KC_TRNS,    KC_TRNS,  RESET,                    RESET,       KC_TRNS,   KC_TRNS,           KC_TRNS,               KC_MUTE
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

/*
 * ROTARY ENCODER
 */

static bool tabbing = false;
static uint16_t tabtimer;
#define TABBING_TIMER 750

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                tap_code(KC_MPRV);
            } else {
                tap_code(KC_MNXT);
            }
        } else {
            if (clockwise) {
                tap_code(KC_UP);
            } else {
                tap_code(KC_DOWN);
            }
        }
    } else if (index == 1) {
        if (IS_LAYER_ON(_LOWER)) {
            if (clockwise) {
                tap_code(KC__VOLUP);
            } else {
                tap_code(KC__VOLDOWN);
            }
        } else {
            if (clockwise) {
                tap_code(KC_RIGHT);
            } else {
                tap_code(KC_LEFT);
            }
        }
    }
}

void matrix_scan_user(void) {
    if (tabbing) {
        if (timer_elapsed(tabtimer) > TABBING_TIMER) {
            unregister_code(KC_LALT);
            tabbing = false;
        }
    }
}

void matrix_init_user(void) {

}
