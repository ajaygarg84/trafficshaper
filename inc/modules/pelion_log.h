#ifndef I_PELION_LOG
#define I_PELION_LOG

#include "device_defines.h"

/**
 * @file pelion_log.h
 */

enum LOG_LEVEL {

    ERROR = 0,
    EVENT,
    WARN,
    INFO,
    DEBUG
};

extern PELION_MUTEX log_mtx;
extern int current_log_level;

void
pelion_log(int level, const char *format, ...);

void
pelion_init_log_on_device();

void
pelion_write_log_on_device(const char * const log);

int
pelion_get_current_log_level();

#endif
