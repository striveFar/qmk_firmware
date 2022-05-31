#include "fds_nrf52.h"

#include "fds.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

static volatile bool fds_ee_initialized = false;
static volatile bool eeprom_dirty = false;

extern void idle_state_handle(void);

static void wait_for_fds_ready(void)
{
    while(!ee_fds_initialized) {
        idle_state_handle();
    }
}

static void ee_evt_handler(fds_evt_t const *p_evt)
{
    switch(p_evt->id) {
    case FDS_EVT_WRITE:
    case FDS_EVT_UPDATE:
        if (p_evt->write.file_id == EE_FILEID && p_evt->write.record_key == EE_EEPROM_KEY) {
            if (p_evt->result != NRF_SUCCESS) {
                NRF_LOG_INFO("EEPROM write/update failed: %d, restart again", p_evt->result);
                ret_code_t err_code;
                err_code = app_timer_start(m_eeprom_update_timer_id, EEPROM_UPDATE_DELAY, NULL);
                APP_ERROR_CHECK(err_code);
            } else {
                NRF_LOG_INFO("EEPROM write/update success");
                eeprom_dirty = false;
            }
        }
        break;
    case FDS_EVT_DEL_RECORD:
    case FDS_EVT_DEL_FILE:
        break;
    case FDS_EVT_GC:
        if (eeprom_dirty) {
            ret_code_t err_code;
            err_code = app_timer_start(m_eeprom_update_timer_id, EEPROM_UPDATE_DELAY, NULL);
            APP_ERROR_CHECK(err_code);
        }
        break;
    case FDS_EVT_INIT:
        if (p_evt->result == NRF_SUCCESS) {
            ee_fds_initialized = true;
            NRF_LOG_INFO("FDS initialized.");
            /*ret_code_t err_code;
            err_code = app_timer_start(m_eeprom_update_timer_id, EEPROM_UPDATE_DELAY, NULL);
            APP_ERROR_CHECK(err_code);
            NRF_LOG_INFO("kickoff eeprom update timer for FDS init");
            */
        } else {
            NRF_LOG_INFO("Failed to initialized FDS, code: %d", p_evt->result);
        } break;
    default:
        break;
    }
}


void fds_init(void)
{
    if (!fds_ee_initialized) {
        ret_code_t err_code;
        NRF_LOG_INFO("Initializing fds...");
        fds_ee_initialized = false;
        fds_register(ee_evt_handler);
        err_code = fds_init();
        APP_ERROR_CHECK(err_code);

        err_code = app_timer_create(&m_eeprom_update_timer_id,
                                    APP_TIMER_MODE_SINGLE_SHOT,
                                    eeprom_update_timeout_handler);
        APP_ERROR_CHECK(err_code);
        wait_for_fds_ready();
    }
    fds_eeprom_restore();
}
