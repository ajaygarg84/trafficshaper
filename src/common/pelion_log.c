#include "pelion_log.h"
#include "pelion_mutex.h"
#include "pelion_stdlib.h"

#include <stdarg.h>
#include <string.h>

#define LOG_LEVEL   EVENT

static char LOG_GLOBAL_BUFFER[1024];
PELION_MUTEX log_mtx;

void
pelion_log(int level, const char *format, ...) {

    if(level <= LOG_LEVEL) {

        memset(LOG_GLOBAL_BUFFER, 0, sizeof(LOG_GLOBAL_BUFFER));

        pelion_acquire_mutex(&log_mtx);

        va_list argptr;
        va_start(argptr, format);
        pelion_varargs(LOG_GLOBAL_BUFFER, format, argptr);
        va_end(argptr);

        write_log_to_device(LOG_GLOBAL_BUFFER);

        pelion_release_mutex(&log_mtx);
    }
}
