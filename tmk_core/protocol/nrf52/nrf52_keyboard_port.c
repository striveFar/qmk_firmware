#include "nrf52_keyboard_port.h"
#include "outputselect.h"
#include "nrf52_usbd.h"
#include "nrf52_ble.h"
#include "nrf52_2g4.h"


/* declarations */
uint8_t keyboard_leds(void) {

    return 0;
}
void send_keyboard(report_keyboard_t *report) {
    // kb id
#ifdef NKRO_ENABLE
    if (keymap_config.nkro) { /* NKRO protocol */

    } else
#endif /* NKRO_ENABLE */
    {
        if (where_to_send() == OUTPUT_USB) {
            // nrf52_usbd_send_keyboard(report);
        } else if (where_to_send() == OUTPUT_BLUETOOTH) {

        } else if (where_to_send() == OUTPUT_2G4) {

        } else {

        }
    }
}
void send_mouse(report_mouse_t *report){

}
void send_system(uint16_t data) {

}
void send_consumer(uint16_t data) {

}
void send_programmable_button(uint32_t data) {

}
void send_digitizer(report_digitizer_t *report) {

}


void nrf52_keyboard_port_init(void) {
    nrf52_usbd_init();
}
