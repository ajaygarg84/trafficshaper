#include "pelion_mutex.h"

void pelion_init_mutex(PELION_MUTEX *mtx) {
    pthread_mutex_init(mtx, NULL);
}


void pelion_acquire_mutex(PELION_MUTEX *mtx) {
    pthread_mutex_lock(mtx);
}


void pelion_release_mutex(PELION_MUTEX *mtx) {
    pthread_mutex_unlock(mtx);
}


