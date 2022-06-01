/**
 * @file eeconfig_flash.h
 *
 */

#pragma once

#include <stdint.h>

#ifndef FDS_EE_FILE_ID
#   define FDS_EE_FILE_ID      (0x1000)
#endif

#ifndef FDS_EE_RECORD_KEY
#   define FDS_EE_RECORD_KEY   (0x1001)
#endif

void fds_init(void);
void fds_eeprom_write_byte(uint16_t addr, uint8_t data);
uint8_t fds_eeprom_read_byte(uint16_t addr);
