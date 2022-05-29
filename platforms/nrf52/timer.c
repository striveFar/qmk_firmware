#include "app_timer.h"

#include "timer.h"

/* ticks per ms*/
#define TICKS_PER_MS (APP_TIMER_TICKS(1))
#define OVERFLOW_ADJUST_TICKS ((uint32_t)((UINT32_MAX / TICKS_PER_MS) * TICKS_PER_MS))
#define OVERFLOW_ADJUST_MS (OVERFLOW_ADJUST_TICKS/TICKS_PER_MS)


static uint32_t ticks_offset = 0;
static uint32_t last_ticks   = 0;
static uint32_t ms_offset    = 0;

void timer_init(void) {
    timer_clear();
}

void timer_clear(void) {
    ticks_offset = app_timer_cnt_get();
    last_ticks   = 0;
    ms_offset    = 0;
}

uint16_t timer_read(void)
{
  return (uint16_t)(timer_read32());
}

uint32_t timer_read32(void)
{
    uint32_t ticks = app_timer_cnt_get() - ticks_offset;
    if (ticks < last_ticks) {
        ticks -= OVERFLOW_ADJUST_TICKS;
        ticks_offset += OVERFLOW_ADJUST_TICKS;
        ms_offset += OVERFLOW_ADJUST_MS;
    }
    last_ticks = ticks;
  return (ticks/TICKS_PER_MS) + ms_offset;
}

uint16_t timer_elapsed(uint16_t last)
{
  return TIMER_DIFF_32(timer_read(), last);
}

uint32_t timer_elapsed32(uint32_t last)
{
    return TIMER_DIFF_32(timer_read32(), last);
}
