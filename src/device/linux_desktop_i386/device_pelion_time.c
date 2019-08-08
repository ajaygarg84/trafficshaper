#include "pelion_time.h"

#include <sys/time.h>
#include <unistd.h>

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

    usleep(us);
}


/**
 * <b>(device-specific)</b>
 *
 * This method gets the current-timestamp in micro-seconds.
 */
unsigned long
pelion_get_current_timestamp_us() {

    struct timeval current_time;
    unsigned long result = 0;

    gettimeofday(&current_time, NULL);

    result = (unsigned long)current_time.tv_sec * 1000000;
    result = result + current_time.tv_usec;

    return result;
}

