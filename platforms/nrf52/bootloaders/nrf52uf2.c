#include "bootloader.h"
#include <stdint.h>
#include "nrf_nvic.h"

// From tinyuf2's board_api.h
#define DBL_TAP_MAGIC 0xF01669EF

// defined by linker script
extern uint32_t _board_dfu_dbl_tap[];
#define DBL_TAP_REG _board_dfu_dbl_tap[0]

__attribute__((weak)) void bootloader_jump(void) {
    DBL_TAP_REG = DBL_TAP_MAGIC;
    sd_nvic_SystemReset();
}

/* not needed, no two-stage reset */
void enter_bootloader_mode_if_requested(void) {}
