#include "pelion_log.h"

/**
 * @file device_pelion_log.c
 */


/**
 * <b>(device-specific)</b>
 *
 * This method initializes the log-backend for the device.
 */
void
pelion_init_log_on_device() {

}


/**
 * <b>(device-specific)</b>
 *
 * This method writes the log on the log-backend.
 */
void
pelion_write_log_on_device(const char * const log) {

}


/**
 * <b>(device-specific)</b>
 *
 * This method gets the current-log-level configured in the device.
 */
int
pelion_get_current_log_level() {

    return EVENT;
}

