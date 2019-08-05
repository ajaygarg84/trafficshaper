#ifndef I_PELION_SYSTEM
#define I_PELION_SYSTEM

#include <stdlib.h>

void *pelion_malloc(unsigned int bytes) {
    return malloc(bytes);
}

void *pelion_free(void *ptr) {
    free(ptr);
}

void pelion_exit() {
    exit(1);
}

#endif
