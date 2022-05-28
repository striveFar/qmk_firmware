#include "nrf52.h"

#include "keyboard.h"



void protocol_setup(void) {
 // Initialize.
  timers_init();
  log_init();
  power_management_init();
  scheduler_init();
}

void protocol_pre_init(void);
void protocol_post_init(void);

void protocol_pre_task(void) {
    output_mode_select_task();
    // nrf_usb_task();
}
void protocol_post_task(void) {
    #ifdef CONSOLE_ENABLE
        console_task();
    #endif
    #ifdef MIDI_ENABLE
        midi_ep_task();
    #endif
    #ifdef VIRTSER_ENABLE
        virtser_task();
    #endif
    #ifdef RAW_ENABLE
        raw_hid_task();
    #endif

}

static void idle_state_handle(void) {
  app_sched_execute();
  if (NRF_LOG_PROCESS() == false) {
    nrf_pwr_mgmt_run();
  }
}
static void timers_init(void) {
  ret_code_t err_code;
  err_code = app_timer_init();
  APP_ERROR_CHECK(err_code);
}

int main(void) {
    platform_setup();
    protocol_setup();
    keyboard_setup();

    protocol_init();

    /* Main loop */
    while (true) {
        protocol_task();

#ifdef DEFERRED_EXEC_ENABLE
        // Run deferred executions
        deferred_exec_task();
#endif // DEFERRED_EXEC_ENABLE

        housekeeping_task();

        idle_state_handle();
    }
}
