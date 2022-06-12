#pragma once

#include <stdint.h>

enum outputs {
    OUTPUT_AUTO,

    OUTPUT_NONE,
    OUTPUT_USB,
    OUTPUT_BLUETOOTH,
    OUTPUT_2G4
};

#ifndef OUTPUT_DEFAULT
#    define OUTPUT_DEFAULT OUTPUT_AUTO
#endif

void    set_output(uint8_t output);
void    set_output_user(uint8_t output);
uint8_t auto_detect_output(void);
uint8_t where_to_send(void);
