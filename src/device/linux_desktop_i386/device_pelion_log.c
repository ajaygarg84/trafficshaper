#include "pelion_log.h"

#include <stdio.h>

/**
 * @file device_pelion_log.c
 */

void init_log_on_device() {
}

void write_log_to_device(const char * const log) {
    printf("%s", log);
}

#include <stdio.h>

/**
 * <b>(device-specific)</b>
 *
 * This method gets the current-log-level configured in the device.
 */
int
pelion_get_current_log_level() {

    int result = EVENT;

    FILE *fp = fopen("log_level", "r");
    if(fp != NULL) {

        result = fgetc(fp) - '0';
        fclose(fp);

    }

    return result;
}

