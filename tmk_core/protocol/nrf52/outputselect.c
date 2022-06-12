#include "outputselect.h"
#include "usb_util.h"

uint8_t desired_output = OUTPUT_DEFAULT;

/** \brief Set Output
 *
 * FIXME: Needs doc
 */
void set_output(uint8_t output) {
    set_output_user(output);
    desired_output = output;
}

/** \brief Set Output User
 *
 * FIXME: Needs doc
 */
__attribute__((weak)) void set_output_user(uint8_t output) {}

/** \brief Auto Detect Output
 *
 * FIXME: Needs doc
 */
uint8_t auto_detect_output(void) {
    if (usb_connected_state()) {
        return OUTPUT_USB;
    }

#ifdef BLUETOOTH_BLUEFRUIT_LE
    if (bluefruit_le_is_connected()) {
        return OUTPUT_BLUETOOTH;
    }
#endif

#ifdef BLUETOOTH_ENABLE
    return OUTPUT_BLUETOOTH; // should check if BT is connected here
#endif

    return OUTPUT_NONE;
}

/** \brief Where To Send
 *
 * FIXME: Needs doc
 */
uint8_t where_to_send(void) {
    if (desired_output == OUTPUT_AUTO) {
        return auto_detect_output();
    }
    return desired_output;
}
