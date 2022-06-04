#include "eeprom_nrf52_defs.h"
#include "fds_nrf52.h"

#include "nrf_pwr_mgmt.h"
#include "app_scheduler.h"
#include "app_error.h"
#include "fds.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

static volatile bool fds_ee_initialized = false;
static volatile bool eeprom_dirty       = false;

__ALIGN(4) static uint8_t eeprom_buf[(FEE_DENSITY_BYTES + 3) & (~3)];  // pad to word size

static fds_record_t ee_record = {
    .file_id = FDS_EE_FILE_ID,
    .key = FDS_EE_RECORD_KEY,
    .data.p_data = &eeprom_buf[0],
    .data.length_words = (sizeof(eeprom_buf)+3)/sizeof(uint32_t),
};

static void idle_state_handle(void) {
    app_sched_execute();
    if (NRF_LOG_PROCESS() == false) {
        nrf_pwr_mgmt_run();
    }
}

static void fds_eeprom_buffer_restore(void)
{
    fds_record_desc_t desc = {0};
    fds_find_token_t token = {0};
    ret_code_t err_code = fds_record_find(FDS_EE_FILE_ID, FDS_EE_RECORD_KEY, &desc, &token);
    if (err_code == FDS_ERR_NOT_FOUND) {
        // no such record, initialized the buffered data to zero
        memset(eeprom_buf, 0, sizeof(eeprom_buf));
    } else {
        fds_flash_record_t record = {0};
        err_code = fds_record_open(&desc, &record);
        APP_ERROR_CHECK(err_code);
        memcpy(eeprom_buf, record.p_data, sizeof(eeprom_buf));
        err_code = fds_record_close(&desc);
        APP_ERROR_CHECK(err_code);
    }
}

static void fds_eeprom_buffer_update(void)
{
    fds_record_desc_t desc = {0};
    fds_find_token_t token = {0};
    ret_code_t err_code = fds_record_find(FDS_EE_FILE_ID, FDS_EE_RECORD_KEY, &desc, &token);
    if (err_code == NRF_SUCCESS) {
        err_code = fds_record_update(&desc, &ee_record);
        if (err_code  == FDS_ERR_NO_SPACE_IN_FLASH) {
            fds_gc();
        } else {
            APP_ERROR_CHECK(err_code);
        }
    } else {
        err_code = fds_record_write(&desc, &ee_record);
        if (err_code == FDS_ERR_NO_SPACE_IN_FLASH) {
            fds_gc();
        } else {
            APP_ERROR_CHECK(err_code);
        }
    }
}

static void fds_evt_handler(fds_evt_t const *p_evt) {
    switch (p_evt->id) {
        case FDS_EVT_INIT:
            if (p_evt->result == NRF_SUCCESS) {
                fds_ee_initialized = true;
                NRF_LOG_INFO("FDS initialized.");
            } else {
                NRF_LOG_INFO("Failed to initialized FDS, code: %d", p_evt->result);
            }
            break;
        case FDS_EVT_WRITE:
        case FDS_EVT_UPDATE:
            if (p_evt->write.file_id == FDS_EE_FILE_ID && p_evt->write.record_key == FDS_EE_RECORD_KEY) {
                if (p_evt->result != NRF_SUCCESS) {
                    NRF_LOG_INFO("EEPROM write/update failed: %d, restart again", p_evt->result);
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
            if (p_evt->result == NRF_SUCCESS) {
                NRF_LOG_INFO("FDS garbage collected success");
            }
            break;
        default:
            break;
    }
}

void fds_eeprom_init(void) {
    if (!fds_ee_initialized) {
        ret_code_t err_code;
        NRF_LOG_INFO("Initializing fds...");
        fds_ee_initialized = false;
        fds_register(fds_evt_handler);
        err_code = fds_init();
        APP_ERROR_CHECK(err_code);
        while (!fds_ee_initialized) {
            idle_state_handle();
        }
    }
    fds_eeprom_buffer_restore();
}


void fds_eeprom_write_byte(uint16_t addr, uint8_t data)
{
    if (eeprom_buf[addr] == data) return;

    eeprom_buf[addr] = data;
    eeprom_dirty = true;
    fds_eeprom_buffer_update();
}

uint8_t fds_eeprom_read_byte(uint16_t addr) { return eeprom_buf[addr]; }

void fds_eeprom_clear(void) {
    memset(eeprom_buf, 0, sizeof(eeprom_buf));
    eeprom_dirty = true;
    fds_eeprom_buffer_update();
}
