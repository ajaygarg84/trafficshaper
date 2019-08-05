#ifndef I_PELION_QUEUE
#define I_PELION_QUEUE

#include "device_defines.h"

struct Pelion_Queue_Node {

    unsigned int tokens;
    unsigned long time_us;

    struct Pelion_Queue_Node *next;
};


struct Pelion_Queue {

    struct Pelion_Queue_Node *head;
    struct Pelion_Queue_Node *tail;

    PELION_MUTEX mtx;

    unsigned int requests_arrived;
    unsigned int requests_dequeued;
};


extern struct Pelion_Queue Q1;
extern struct Pelion_Queue Q2;

void
add_new_node(struct Pelion_Queue *queue, unsigned int tokens);

struct Pelion_Queue_Node*
get_oldest_node(struct Pelion_Queue *queue, unsigned char do_locking);

struct Pelion_Queue_Node*
get_oldest_node_if_applicable(struct Pelion_Queue *queue,
                              unsigned int tokens);
#endif
