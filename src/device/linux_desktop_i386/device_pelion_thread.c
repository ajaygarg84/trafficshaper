#include "pelion_thread.h"

#include <pthread.h>

void
pelion_start_thread(THREAD_FUNC_PTR func_ptr, void *arg) {

    pthread_t tid;
    pthread_create(&tid, NULL, func_ptr, arg);
}


void
pelion_init_mutex(PELION_MUTEX *mtx) {

    pthread_mutex_init(mtx, NULL);
}


void
pelion_acquire_mutex(PELION_MUTEX *mtx) {

    pthread_mutex_lock(mtx);
}


void
pelion_release_mutex(PELION_MUTEX *mtx) {

    pthread_mutex_unlock(mtx);
}


void
pelion_init_condition_variable(PELION_CONDITION_VARIABLE *cond) {

    pthread_cond_init(cond, NULL);
}


void
pelion_wait_on_condition_variable(PELION_CONDITION_VARIABLE *cond,
                                  PELION_MUTEX *mtx) {

    pthread_cond_wait(cond, mtx);
}


void
pelion_wake_one_thread_on_condition_variable(
        PELION_CONDITION_VARIABLE *cond) {

    pthread_cond_signal(cond);
}

