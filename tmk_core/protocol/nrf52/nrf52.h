#pragma once

// #include "sdk_config.h"

#include "app_timer.h"
#include "nrf_pwr_mgmt.h"
#include "app_scheduler.h"
#include "app_error.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include <stdint.h>
#include <string.h>

/**< Maximum size of scheduler events. */
#define SCHED_MAX_EVENT_DATA_SIZE APP_TIMER_SCHED_EVENT_DATA_SIZE
/**< Maximum number of events in the scheduler queue. */
#define SCHED_QUEUE_SIZE 32


/**@brief Function for initializing the nrf log module.
 */
void log_init(void);
 /**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module.
 */
static void timers_init(void);
/**@brief Function for initializing power management.
 */
void power_management_init(void);

/**@brief Function for handling the idle state (main loop).
 *
 * @details If there is no pending log operation, then sleep until next the next event occurs.
 */
void idle_state_handle(void);

/**@brief Function for the Event Scheduler initialization.
 */
void scheduler_init(void);
