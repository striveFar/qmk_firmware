#include "nrf52_usbd.h"

#include "app_usbd.h"
#include "app_usbd_core.h"
#include "app_error.h"
#include "nrf_log.h"
#include "app_usbd_hid.h"
#include "app_usbd_hid_kbd.h"

#include "usb_device_state.h"
#include "usb_descriptor.h"

#ifdef NKRO_ENABLE
#    include "keycode_config.h"

extern keymap_config_t keymap_config;
#endif

#ifdef JOYSTICK_ENABLE
#    include "joystick.h"
#endif


static void nrf52_usbd_hid_kbd_ev_handler(app_usbd_class_inst_t const * p_inst,
                                app_usbd_hid_user_event_t event);

/*
 * Handles the GET_DESCRIPTOR callback
 *
 * Returns the proper descriptor
 */
// static const USBDescriptor *usb_get_descriptor_cb(USBDriver *usbp, uint8_t dtype, uint8_t dindex, uint16_t wIndex) {
//     (void)usbp;
//     static USBDescriptor desc;
//     uint16_t             wValue = ((uint16_t)dtype << 8) | dindex;
//     desc.ud_string              = NULL;
//     desc.ud_size                = get_usb_descriptor(wValue, wIndex, (const void **const) & desc.ud_string);
//     if (desc.ud_string == NULL)
//         return NULL;
//     else
//         return &desc;
// }

#ifndef KEYBOARD_SHARED_EP
/**
 * @brief Global HID keyboard instance
 */
APP_USBD_HID_KBD_GLOBAL_DEF(m_app_hid_kbd,
                            KEYBOARD_INTERFACE,
                            NRFX_USBD_EPIN1,
                            nrf52_usbd_hid_kbd_ev_handler,
                            APP_USBD_HID_SUBCLASS_BOOT);
#endif



static void nrf52_usbd_hid_kbd_ev_handler(app_usbd_class_inst_t const * p_inst,
                                app_usbd_hid_user_event_t event) {
    switch (event) {
    case APP_USBD_HID_USER_EVT_OUT_REPORT_READY: {
        NRF_LOG_INFO("USBD HID OUT report ready");
    } break;
    case APP_USBD_HID_USER_EVT_IN_REPORT_DONE: {
    } break;
    case APP_USBD_HID_USER_EVT_SET_BOOT_PROTO: {
        NRF_LOG_INFO("SET_BOOT_PROTO");
    } break;
    case APP_USBD_HID_USER_EVT_SET_REPORT_PROTO: {
        NRF_LOG_INFO("SET_REPORT_PROTO");
    } break;
    default:
        break;
    }
}

/**
 * @brief USBD library specific event handler.
 *
 * @param event     USBD library event.
 * */
static void usbd_user_ev_handler(app_usbd_event_type_t event)
{
    switch (event)
    {
        case APP_USBD_EVT_DRV_SOF:
            break;
        case APP_USBD_EVT_DRV_SUSPEND:
            app_usbd_suspend_req(); // Allow the library to put the peripheral into sleep mode
            break;
        case APP_USBD_EVT_DRV_RESUME:
            /* Restore LED state - during SUSPEND all LEDS are turned off */
            break;
        case APP_USBD_EVT_STARTED:
            break;
        case APP_USBD_EVT_STOPPED:
            app_usbd_disable();
            break;
        case APP_USBD_EVT_POWER_DETECTED:
            NRF_LOG_INFO("USB power detected");

            if (!nrf_drv_usbd_is_enabled())
            {
                app_usbd_enable();
            }
            break;
        case APP_USBD_EVT_POWER_REMOVED:
            NRF_LOG_INFO("USB power removed");
            app_usbd_stop();
            break;
        case APP_USBD_EVT_POWER_READY:
            NRF_LOG_INFO("USB ready");
            app_usbd_start();
            break;
        default:
            break;
    }
}

void nrf52_usbd_init(void) {
    ret_code_t                     ret;
    static const app_usbd_config_t usbd_config = {
        .ev_state_proc = usbd_user_ev_handler,
    };
    ret = app_usbd_init(&usbd_config);
    APP_ERROR_CHECK(ret);
}
