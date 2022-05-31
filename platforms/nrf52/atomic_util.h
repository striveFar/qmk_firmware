/* Copyright 2022 JasonRen(biu)
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

#include "app_error.h"
#include "nrf_nvic.h"

static __inline__ uint8_t __interrupt_disable__(void) {
    uint8_t dummy = 0;
    uint32_t err_code = sd_nvic_critical_region_enter(&dummy);
    APP_ERROR_CHECK(err_code);
    return 1;
}

static __inline__ void __interrupt_enable__(const uint8_t *__s) {
    uint32_t err_code = sd_nvic_critical_region_exit(0);
    APP_ERROR_CHECK(err_code);
}

#define ATOMIC_BLOCK(type) for (type, __ToDo = __interrupt_disable__(); __ToDo; __ToDo = 0)
#define ATOMIC_FORCEON uint8_t sreg_save __attribute__((__cleanup__(__interrupt_enable__))) = 0

#define ATOMIC_BLOCK_RESTORESTATE _Static_assert(0, "ATOMIC_BLOCK_RESTORESTATE not implemented")
#define ATOMIC_BLOCK_FORCEON ATOMIC_BLOCK(ATOMIC_FORCEON)
