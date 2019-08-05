#ifndef I_PELION_MUTEX
#define I_PELION_MUTEX

#include "device_defines.h"

void acquire_mutex(PELION_MUTEX *mtx);
void release_mutex(PELION_MUTEX *mtx);

#endif


