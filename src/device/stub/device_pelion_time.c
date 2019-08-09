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
 * micro-seconds.
 */
void
pelion_delay_us(unsigned long long us) {

}


/**
 * <b>(device-specific)</b>
 *
 * This method gets the current-timestamp in micro-seconds.
 */
unsigned long long
pelion_get_current_timestamp_us() {

    return 0;
}

