#include "device_defines.h"

#include "pelion_queue.h"
#include "pelion_mutex.h"

struct Pelion_Queue Q1;
struct Pelion_Queue Q2;

PELION_MUTEX Q1_mutex;
PELION_MUTEX Q2_mutex;

void add_new_node(struct Pelion_Queue *queue, unsigned int tokens) {

    acquire_mutex(&Q1_mutex);

    release_mutex(&Q1_mutex);
}
