#include "pelion_time.h"

#include <sys/time.h>
#include <unistd.h>

void
pelion_delay_ms(unsigned int ms) {

    usleep(ms * 1000);
}


unsigned long
get_current_timestamp_us() {

    struct timeval current_time;
    unsigned long result = 0;

    gettimeofday(&current_time, NULL);

    result = (unsigned long)current_time.tv_sec * 1000000;
    result = result + current_time.tv_usec;

    return result;
}

