#include "device_defines.h"

#include "traffic_queue.h"
#include "pelion_mutex.h"
#include "pelion_system.h"
#include "pelion_log.h"
#include "pelion_cmd_args.h"
#include "pelion_time.h"

void
add_new_node(struct Traffic_Queue *queue, unsigned int tokens) {

    struct Traffic_Queue_Node *new_node =
        (struct Traffic_Queue_Node *) pelion_malloc(
                          sizeof(struct Traffic_Queue_Node));

    if(new_node == NULL) {
        pelion_log(ERROR, "We have run out of memory, exiting system ..\n");
        pelion_exit();
    }

    /*
     * If we reach here, we have the node, so set the payload ..
     */
    new_node->tokens = tokens;
    new_node->time_us = get_current_time_us();


    /*
     * Adjust the head and tail pointers, creating new when necessary.
     *
     * Note that since the queues will be used in a typical
     * producer-consumer paradigm in a multi-threaded environment,
     * so we need to protect the resource while modification.
     */
    pelion_acquire_mutex(&(queue->mtx));

    if(queue->head != NULL) {
        queue->head->next = new_node;
    }
    queue->head = new_node;

    if(queue->tail == NULL) {
        queue->tail = new_node;
    }

    pelion_release_mutex(&(queue->mtx));
}


struct Traffic_Queue_Node*
get_oldest_node(struct Traffic_Queue *queue, unsigned char do_locking) {

    struct Traffic_Queue_Node *result = NULL;

    /*
     * Adjust the head and tail pointers.
     */
    if(do_locking == 1) {
        pelion_acquire_mutex(&(queue->mtx));
    }

    result = queue->tail;

    if(queue->tail != NULL) {
        queue->tail = queue->tail->next;
    }

    if(do_locking == 1) {
        pelion_release_mutex(&(queue->mtx));
    }

    return result;
}


struct Traffic_Queue_Node*
get_oldest_node_if_applicable(struct Traffic_Queue *queue,
                              unsigned int tokens) {

    struct Traffic_Queue_Node *result = NULL;

    pelion_acquire_mutex(&(queue->mtx));

    if(queue->tail != NULL) {
        if(queue->tail->tokens <= tokens) {
            result = get_oldest_node(queue, 0);
        }
    }

    pelion_release_mutex(&(queue->mtx));

    return result;
}
