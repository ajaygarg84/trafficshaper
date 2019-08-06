#ifndef I_PELION_SYSTEM
#define I_PELION_SYSTEM

/**
 * @file pelion_system.h
 */

void *pelion_malloc(unsigned int bytes);
void pelion_free(void *ptr);
void pelion_exit();

#endif
