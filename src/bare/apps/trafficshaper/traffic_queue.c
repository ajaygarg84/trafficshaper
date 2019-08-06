#include "device_defines.h"

#include "pelion_thread.h"
#include "pelion_system.h"
#include "pelion_log.h"
#include "pelion_time.h"
#include "pelion_stdlib.h"

#include "traffic_queue.h"


static void
enqueue_node(struct Traffic_Queue *queue,
             struct Traffic_Queue_Node *node,
             unsigned char do_locking) {

    if(node == NULL) {
        return;
    }

    /*
     * Adjust the head and tail pointers, creating new when necessary.
     *
     * Note that since the queues will be used in a typical
     * producer-consumer paradigm in a multi-threaded environment,
     * so we need to protect the resource while modification.
     */
    if(do_locking == 1) {
        pelion_acquire_mutex(&(queue->mtx));
    }

    node->time_us = pelion_get_current_timestamp_us();
    node->next = NULL;

    if(queue->head != NULL) {
        queue->head->next = node;
    }
    queue->head = node;

    if(queue->tail == NULL) {
        queue->tail = node;
    }

    pelion_log(EVENT, "r%u enters %s\n", node->request_number,
                                         queue->id);

    if(do_locking == 1) {
        pelion_release_mutex(&(queue->mtx));
    }
}

void
enqueue_node_new(struct Traffic_Queue *queue,
                 unsigned int request_number,
                 unsigned int tokens) {

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
    new_node->request_number = request_number;
    new_node->tokens = tokens;
    new_node->in_system_time_us = pelion_get_current_timestamp_us();

    /*
     * Finally, add the node to queue.
     */
    enqueue_node(queue, new_node, 1);
}


void
enqueue_node_existing(struct Traffic_Queue *queue,
                      struct Traffic_Queue_Node *node) {

    enqueue_node(queue, node, 1);
}


struct Traffic_Queue_Node*
get_oldest_node(struct Traffic_Queue *queue,
                unsigned char do_locking,
                unsigned char remaining_tokens,
                unsigned char do_log_remaining_tokens) {

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
        if(queue->tail == NULL) {
            queue->head = NULL;
        }
    }

    /*
     * Log removal from queue.
     */
    if(result != NULL) {

        char str_time_in_us_in_Q[20] = {0};

        unsigned long time_in_us_in_Q =
            pelion_get_current_timestamp_us() - result->time_us;

        pelion_convert_numeric_to_float(time_in_us_in_Q,
                                        1000,
                                        str_time_in_us_in_Q,
                                        sizeof(str_time_in_us_in_Q));

        if(do_log_remaining_tokens == 1) {

            pelion_log(EVENT, "r%u leaves %s, time in %s = %sms, "
                              "remaining_token = %u\n",
                              result->request_number,
                              queue->id,
                              queue->id,
                              str_time_in_us_in_Q,
                              remaining_tokens);

        } else {

            pelion_log(EVENT, "r%u leaves %s, time in %s = %sms\n",
                              result->request_number,
                              queue->id,
                              queue->id,
                              str_time_in_us_in_Q);
        }
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
            result = get_oldest_node(queue,
                                     0,
                                     tokens - queue->tail->tokens,
                                     1);
        }
    }

    pelion_release_mutex(&(queue->mtx));

    return result;
}
