#include "pelion_log.h"
#include "pelion_system.h"

#include <stdlib.h>
#include <signal.h>

/**
 * @file device_pelion_system.c
 */


/**
 * <b>(device-specific)</b>
 *
 * @param bytes
 * Number of bytes to be allocated.
 *
 *
 * This method allocates memory from the system.
 */
void*
pelion_malloc(unsigned int bytes) {

    return malloc(bytes);
}


/**
 * <b>(device-specific)</b>
 *
 * @param ptr
 * Pointer to memory-block that needs to be freed.
 *
 *
 * This method returns memory to the system.
 */
void
pelion_free(void *ptr) {

    free(ptr);
}


void ctrl_c_handler(int sig_num) {

    pelion_log(EVENT, "emulation ends\n");
    pelion_exit();
}


/**
 * <b>(device-specific)</b>
 *
 * This method does device-specific initializations..
 */
void
pelion_device_specific_init() {

    signal(SIGINT, ctrl_c_handler);
}


/**
 * <b>(device-specific)</b>
 *
 * This method exits the application, and possibly reboots the system.
 */
void
pelion_exit() {

    exit(1);
}
