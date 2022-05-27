#include "bootloader.h"

__attribute__((weak)) void bootloader_jump(void) {}

__attribute__((weak)) void enter_bootloader_mode_if_requested(void) {}
