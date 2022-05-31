
#include <stdint.h>
#include <string.h>

#include "eeprom_nrf52.h"
#include "fds_nrf52.h"

#include "eeprom_driver.h"


/*****************************************************************************
 *  Bind to eeprom_driver.c
 *******************************************************************************/

void eeprom_driver_init(void) {
    fds_init();
 }

void eeprom_driver_erase(void) {
    /* Wipe out the EEPROM, setting values to zero */
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    /*
        Read a block of data:
            buf: target buffer
            addr: 0-based offset within the EEPROM
            len: length to read
     */
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    /*
        Write a block of data:
            buf: target buffer
            addr: 0-based offset within the EEPROM
            len: length to write
     */
}
