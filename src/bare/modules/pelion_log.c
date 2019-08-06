#include "pelion_log.h"
#include "pelion_thread.h"
#include "pelion_stdlib.h"

#include <stdarg.h>
#include <string.h>

/**
 * @file pelion_log.c
 */

static char LOG_GLOBAL_BUFFER[1024];

PELION_MUTEX log_mtx;
int current_log_level = EVENT;

/**
 * <b>(bare-metal)</b>
 *
 * @param level
 * Log-level intended for this log.
 *
 * @param format
 * Format-specifier string for variable-arguments.
 *
 * @param ...
 * Variable-argument list.
 *
 *
 * This function receives a log-request, and does the logging
 * according to the level-of-this-log-request, and the global-log-level
 * set up.
 */
void
pelion_log(int level, const char *format, ...) {

    if(level <= current_log_level) {

        memset(LOG_GLOBAL_BUFFER, 0, sizeof(LOG_GLOBAL_BUFFER));

        pelion_acquire_mutex(&log_mtx);

        va_list argptr;
        va_start(argptr, format);
        pelion_varargs(LOG_GLOBAL_BUFFER, format, argptr);
        va_end(argptr);

        pelion_write_log_on_device(LOG_GLOBAL_BUFFER);

        pelion_release_mutex(&log_mtx);
    }
}
