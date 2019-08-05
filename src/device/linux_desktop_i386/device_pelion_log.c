#include "pelion_log.h"

#include <stdio.h>

void init_log_on_device() {
}

void write_log_to_device(const char * const log) {
    printf("%s", log);
}
