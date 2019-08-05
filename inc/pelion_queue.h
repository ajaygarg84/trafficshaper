#ifndef I_PELION_QUEUE
#define I_PELION_QUEUE

struct Pelion_Queue_Node {
    unsigned int tokens;
    struct Pelion_Queue_Node *next;
};


struct Pelion_Queue {
    struct Pelion_Queue_Node *head;
    struct Pelion_Queue_Node *tail;
};


extern struct Pelion_Queue Q1;
extern struct Pelion_Queue Q2;

void add_new_node(struct Pelion_Queue *queue, unsigned int tokens);

#endif
