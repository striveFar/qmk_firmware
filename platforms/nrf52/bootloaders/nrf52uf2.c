#include "bootloader.h"
#include <stdint.h>
#include "nrf_nvic.h"
#include "nrf_soc.h"

// From tinyuf2's board_api.h
#define DBL_TAP_MAGIC 0xF01669EF

// defined by linker script
#define DBL_TAP_REG 0

__attribute__((weak)) void mcu_reset(void) {
    sd_nvic_SystemReset();
}

__attribute__((weak)) void bootloader_jump(void) {
    sd_power_gpregret_set(DBL_TAP_REG, DBL_TAP_MAGIC);
    sd_nvic_SystemReset();
}

/* not needed, no two-stage reset */
void enter_bootloader_mode_if_requested(void) {}
