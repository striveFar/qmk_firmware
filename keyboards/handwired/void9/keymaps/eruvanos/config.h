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

#pragma once

// place overrides here

// ws2812 RGB LED
#undef RGB_DI_PIN
#define RGB_DI_PIN B2
#undef RGBLED_NUM
#define RGBLED_NUM 3        // Number of LEDs

// Layers
// see https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgblight#lighting-layers
// #define RGBLIGHT_LAYERS
// #define RGBLIGHT_MAX_LAYERS 4
#define RGBLIGHT_VAL_STEP 17
#define RGBLIGHT_ANIMATIONS
