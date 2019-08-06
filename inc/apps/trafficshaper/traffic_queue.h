#ifndef I_TRAFFIC_QUEUE
#define I_TRAFFIC_QUEUE

#include "device_defines.h"

struct Traffic_Queue_Node {

    unsigned int tokens;

    unsigned int request_number;
    unsigned long time_us;

    struct Traffic_Queue_Node *next;
};


struct Traffic_Queue {

    struct Traffic_Queue_Node *head;
    struct Traffic_Queue_Node *tail;

    PELION_MUTEX mtx;

    unsigned int requests_enqueued;
};


extern struct Traffic_Queue Q1;
extern struct Traffic_Queue Q2;

void
enqueue_node_new(struct Traffic_Queue *queue, unsigned int tokens);

void
enqueue_node_existing(struct Traffic_Queue *queue,
                      struct Traffic_Queue_Node *node);

struct Traffic_Queue_Node*
get_oldest_node(struct Traffic_Queue *queue, unsigned char do_locking);

struct Traffic_Queue_Node*
get_oldest_node_if_applicable(struct Traffic_Queue *queue,
                              unsigned int tokens);
#endif
