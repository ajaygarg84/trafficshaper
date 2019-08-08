#include "pelion_time.h"


/**
 * @file device_pelion_time.c
 */

/**
 * <b>(device-specific)</b>
 *
 * @param us
 * Number of micro-seconds.
 *
 *
 * This method causes the current-thread to sleep for <b>us</b>
 * milli-seconds.
 */
void
pelion_delay_us(unsigned int us) {

}


/**
 * <b>(device-specific)</b>
 *
 * This method gets the current-timestamp in micro-seconds.
 */
unsigned long
pelion_get_current_timestamp_us() {

    return 0;
}

