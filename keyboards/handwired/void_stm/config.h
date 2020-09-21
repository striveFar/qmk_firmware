/*
Copyright 2020 Victor Lucachi

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xF055
#define PRODUCT_ID 0x3536
#define DEVICE_VER 0x0001
#define MANUFACTURER Victor Lucachi
#define PRODUCT void_stm
#define DESCRIPTION A custom STM32 keyboard

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 2

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { B11, B10 }
#define MATRIX_COL_PINS { B3, B4 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN           A0
#define BACKLIGHT_PWM_DRIVER    PWMD2
#define BACKLIGHT_PWM_CHANNEL   1

#define RGB_DI_PIN A1

#define ADC_PIN A0

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
// #define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
