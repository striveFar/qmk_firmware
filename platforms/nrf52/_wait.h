#include "wait.h"
#include "nrf_delay.h"



void wait_ms(int ms)
{
    nrf_delay_ms(ms);
}

void wait_us(int us)
{
    nrf_delay_us(us);
}

// the nrf sdk use 4us for io delay
#ifndef GPIO_INPUT_PIN_DELAY
#    define GPIO_INPUT_PIN_DELAY 5
#endif

#define waitInputPinDelay() wait_us(GPIO_INPUT_PIN_DELAY)
