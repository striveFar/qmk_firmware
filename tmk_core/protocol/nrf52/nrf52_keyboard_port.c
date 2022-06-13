#include "nrf52_keyboard_port.h"
#include "outputselect.h"
#include "nrf52_usbd.h"

/* declarations */
uint8_t keyboard_leds(void) {

}
void send_keyboard(report_keyboard_t *report) {
    // kb id
#ifdef NKRO_ENABLE
    if (keymap_config.nkro) { /* NKRO protocol */

    }
#endif /* NKRO_ENABLE */
    if (where_to_send() == OUTPUT_USB) {
        nrf_usb_send_report(report);
    } else if (where_to_send() == OUTPUT_BLUETOOTH) {

    } else if (where_to_send() == OUTPUT_2G4) {

    } else {

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
