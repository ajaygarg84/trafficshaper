#ifndef I_PELION_THREAD
#define I_PELION_THREAD

#include "device_defines.h"

typedef void* (*THREAD_FUNC_PTR)(void *arg);

void start_thread(THREAD_FUNC_PTR func_ptr, void *arg);

void pelion_init_mutex(PELION_MUTEX *mtx);
void pelion_acquire_mutex(PELION_MUTEX *mtx);
void pelion_release_mutex(PELION_MUTEX *mtx);


#endif

