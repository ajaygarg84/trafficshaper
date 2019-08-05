#ifndef I_PELION_THREAD
#define I_PELION_THREAD

typedef void* (*THREAD_FUNC_PTR)(void *arg);

void start_thread(THREAD_FUNC_PTR func_ptr, void *arg);

#endif

