#ifndef I_PELION_SYSTEM
#define I_PELION_SYSTEM

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
void *pelion_malloc(unsigned int bytes) {

    return 0;
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
void pelion_free(void *ptr) {

}


/**
 * <b>(device-specific)</b>
 *
 * This method exits the application, and possibly reboots the system.
 */
void pelion_exit() {

}

#endif
