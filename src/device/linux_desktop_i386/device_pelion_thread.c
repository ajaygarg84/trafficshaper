#include "pelion_thread.h"

#include <pthread.h>

void start_thread(THREAD_FUNC_PTR func_ptr, void *arg) {

    pthread_t tid;
    pthread_create(&tid, NULL, func_ptr, arg);
}
