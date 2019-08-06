#include "pelion_thread.h"

#include <pthread.h>

void start_thread(THREAD_FUNC_PTR func_ptr, void *arg) {

    pthread_t tid;
    pthread_create(&tid, NULL, func_ptr, arg);
}


void pelion_init_mutex(PELION_MUTEX *mtx) {
    pthread_mutex_init(mtx, NULL);
}


void pelion_acquire_mutex(PELION_MUTEX *mtx) {
    pthread_mutex_lock(mtx);
}


void pelion_release_mutex(PELION_MUTEX *mtx) {
    pthread_mutex_unlock(mtx);
}

