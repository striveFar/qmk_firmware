/* Copyright 2020 Hannes Hasselbring
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
 * ,--------------------.
 * |   7  |   8  |   9  |
 * |------+------+------|
 * |   4  |   5  |   6  |
 * |------+------+------|
 * |OSL(1)|OSL(2)|OSL(3)|
 * `--------------------'
 */
[0] = LAYOUT_ortho_3x3(
    KC_7,       KC_8,       KC_9,
    KC_4,       KC_5,       KC_6,
    OSL(1),  OSL(2),  OSL(3)
),

/* FN1
 * ,--------------------.
 * | F17  | F18  | F19  |
 * |------+------+------|
 * | F14  | F15  | F16  |
 * |------+------+------|
 * |      |      |      |
 * `--------------------'
 */
[1] = LAYOUT_ortho_3x3(
    KC_F17,       KC_F18,       KC_F19,
    KC_F14,       KC_F15,       KC_F16,
    KC_TRNS,     KC_TRNS,     KC_TRNS
),

/* FN2
 * ,--------------------.
 * | VOL+ | COPY |      |
 * |------+------+------|
 * | VOL- | PASTE|      |
 * |------+------+------|
 * |      |      |      |
 * `--------------------'
 */
[2] = LAYOUT_ortho_3x3(
    KC_VOLU,       KC_COPY,       KC_TRNS,
    KC_VOLD,       KC_PASTE,      KC_TRNS,
    KC_TRNS,       KC_TRNS,       KC_TRNS
),

/* FN3
 * ,--------------------.
 * |RGB_Tg|RESET | RESET|
 * |------+------+------|
 * |RGB_M+|RGBM- | DEBUG|
 * |------+------+------|
 * |      |      |      |
 * `--------------------'
 */
[3] = LAYOUT_ortho_3x3(
    RGB_TOG,       RESET,       RESET,
    RGB_RMOD,      RGB_MOD,     DEBUG,
    KC_TRNS,       KC_TRNS,     KC_TRNS
)
};

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
