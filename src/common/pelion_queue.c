#include "device_defines.h"

#include "pelion_queue.h"
#include "pelion_mutex.h"
#include "pelion_system.h"

void add_new_node(struct Pelion_Queue *queue, unsigned int tokens) {

    struct Pelion_Queue_Node *new_node =
        (struct Pelion_Queue_Node *) pelion_malloc(
                          sizeof(struct Pelion_Queue_Node));

    if(new_node == NULL) {
        error_log("We have run out of memory, exiting system ..\n");
        pelion_exit();
    }

    /*
     * If we reach here, we have the node, so set the payload ..
     */
    new_node->tokens = tokens;


    /*
     * Adjust the head and tail pointers, creating new when necessary.
     *
     * Note that since the queues will be used in a typical
     * producer-consumer paradigm in a multi-threaded environment,
     * so we need to protect the resource while modification.
     */
    acquire_mutex(&(queue->mtx));

    if(queue->head != NULL) {
        queue->head->next = new_node;
    }
    queue->head = new_node;

    if(queue->tail == NULL) {
        queue->tail = new_node;
    }

    release_mutex(&(queue->mtx));
}


struct Pelion_Queue_Node* get_oldest_node(struct Pelion_Queue *queue) {

    struct Pelion_Queue_Node *result = queue->tail;

    /*
     * Adjust the head and tail pointers.
     */
    acquire_mutex(&(queue->mtx));

    if(queue->tail != NULL) {
        queue->tail = queue->tail->next;
    }

    release_mutex(&(queue->mtx));
}
