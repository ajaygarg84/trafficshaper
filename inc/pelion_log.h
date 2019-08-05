#ifndef I_PELION_LOG
#define I_PELION_LOG

#include "device_defines.h"

#define EVENT   0
#define ERROR   1
#define WARN    2
#define INFO    3
#define DEBUG   4


extern PELION_MUTEX log_mtx;
void pelion_log(int level, const char *format, ...);

void init_log_on_device();
void write_log_to_device(const char * const log);

#endif
