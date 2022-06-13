#pragma once

/* declarations */
uint8_t keyboard_leds(void);
void    send_keyboard(report_keyboard_t *report);
void    send_mouse(report_mouse_t *report);
void    send_system(uint16_t data);
void    send_consumer(uint16_t data);
void    send_programmable_button(uint32_t data);
void    send_digitizer(report_digitizer_t *report);
