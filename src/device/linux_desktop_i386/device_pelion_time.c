#include "pelion_time.h"

#include <unistd.h>

void pelion_delay_ms(unsigned int ms) {

    usleep(ms * 1000);
}
