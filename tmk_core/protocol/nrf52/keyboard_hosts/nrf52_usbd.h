#pragma once

void nrf52_usbd_init(void);

/* declarations */
uint8_t nrf52_usbd_keyboard_leds(void);
void    nrf52_usbd_send_keyboard(report_keyboard_t *report);
void    nrf52_usbd_send_mouse(report_mouse_t *report);
void    nrf52_usbd_send_system(uint16_t data);
void    nrf52_usbd_send_consumer(uint16_t data);
void    nrf52_usbd_send_programmable_button(uint32_t data);
void    nrf52_usbd_send_digitizer(report_digitizer_t *report);
