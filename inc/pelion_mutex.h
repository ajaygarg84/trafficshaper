#ifndef I_PELION_MUTEX
#define I_PELION_MUTEX

#include "device_defines.h"

void pelion_init_mutex(PELION_MUTEX *mtx);
void pelion_acquire_mutex(PELION_MUTEX *mtx);
void pelion_release_mutex(PELION_MUTEX *mtx);

#endif


