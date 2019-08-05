#include "pelion_mutex.h"

void acquire_mutex(PELION_MUTEX *mtx) {
    pthread_mutex_lock(mtx);
}

void release_mutex(PELION_MUTEX *mtx) {
    pthread_mutex_unlock(mtx);
}


