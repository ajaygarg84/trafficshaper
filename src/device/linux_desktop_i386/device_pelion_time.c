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
 * micro-seconds.
 */
void
pelion_delay_us(unsigned long long us) {

    usleep(us);
}


/**
 * <b>(device-specific)</b>
 *
 * This method gets the current-timestamp in micro-seconds.
 */
unsigned long long
pelion_get_current_timestamp_us() {

    struct timeval current_time;
    unsigned long long result = 0;

    gettimeofday(&current_time, NULL);

    result = (unsigned long long)current_time.tv_sec * 1000000ULL;
    result = result + current_time.tv_usec;

    return result;
}

