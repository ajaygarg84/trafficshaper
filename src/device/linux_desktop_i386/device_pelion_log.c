#include "pelion_log.h"

#include <stdio.h>
#include <string.h>

/**
 * @file device_pelion_log.c
 */


static FILE *fp = NULL;

/**
 * <b>(device-specific)</b>
 *
 * This method initializes the log-backend for the device.
 */
void
pelion_init_log_on_device() {

    /*
     * For linux, we would write logs on a log-file.
     * At startup, re-initialize the log-file.
     */
    fp = fopen("logs", "w");
}


/**
 * <b>(device-specific)</b>
 *
 * This method writes the log on the log-backend.
 */
void
pelion_write_log_on_device(const char * const log) {

    fwrite(log, 1, strlen(log), fp);
    fflush(fp);
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

