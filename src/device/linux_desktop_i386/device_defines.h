#ifndef I_DEVICE_DEFINES
#define I_DEVICE_DEFINES

#include <pthread.h>

/**
 * @file device_defines.h
 */

#define PELION_MUTEX                pthread_mutex_t
#define PELION_CONDITION_VARIABLE   pthread_cond_t


#include <stdio.h>

#define pelion_sprintf              sprintf
#define pelion_vsprintf             vsprintf


#endif

