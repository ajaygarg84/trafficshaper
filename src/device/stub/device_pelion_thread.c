#include "pelion_thread.h"

/**
 * @file device_pelion_thread.c
 */

/**
 * <b>(device-specific)</b>
 *
 * @param func_ptr
 * Function-pointer for entry-point-function for thread.
 *
 * @param arg
 * Argument to be passed to <b>func_ptr</b>
 *
 *
 * This method spawns a new thread/task-context.
 */
void
pelion_start_thread(THREAD_FUNC_PTR func_ptr, void *arg) {

}


/**
 * <b>(device-specific)</b>
 *
 * @param mtx
 * Mutex.
 *
 *
 * This method initializes a mutex.
 */
void
pelion_init_mutex(PELION_MUTEX *mtx) {

}


/**
 * <b>(device-specific)</b>
 *
 * @param mtx
 * Mutex.
 *
 *
 * This method causes the current thread to acquire a mutex.
 */
void
pelion_acquire_mutex(PELION_MUTEX *mtx) {

}


/**
 * <b>(device-specific)</b>
 *
 * @param mtx
 * Mutex.
 *
 *
 * This method causes the current thread to release a mutex.
 */
void
pelion_release_mutex(PELION_MUTEX *mtx) {

}


/**
 * <b>(device-specific)</b>
 *
 * @param cond
 * Condition Variable.
 *
 *
 * This method initializes a condition-variable.
 */
void
pelion_init_condition_variable(PELION_CONDITION_VARIABLE *cond) {

}


/**
 * <b>(device-specific)</b>
 *
 * @param cond
 * Condition-Variable.
 *
 * @param mtx
 * Mutex.
 *
 * This method does the following things atomically:
 *
 * * Releases the mutex <b>mtx</b>.
 * * Starts waiting on the condition-variable <b>cond</b>.
 */
void
pelion_wait_on_condition_variable(PELION_CONDITION_VARIABLE *cond,
                                  PELION_MUTEX *mtx) {

}


/**
 * <b>(device-specific)</b>
 *
 * @param cond
 * Condition-Variable
 *
 * This method does the following things atomically:
 *
 * * Wakes exactly one thread waiting on the condition-variable
 *   <b>cond</b>.
 * * Have the waking-thread get back its mutex (which it had
 *   relinquished before going on wait).
 */
void
pelion_wake_one_thread_on_condition_variable(
        PELION_CONDITION_VARIABLE *cond) {

}

