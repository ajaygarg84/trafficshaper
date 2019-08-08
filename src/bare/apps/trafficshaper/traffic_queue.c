#include "device_defines.h"

#include "pelion_thread.h"
#include "pelion_system.h"
#include "pelion_log.h"
#include "pelion_time.h"
#include "pelion_stdlib.h"

#include "traffic_queue.h"

#include <stdio.h>

/**
 * @file traffic_queue.c
 */

/**
 * <b>(bare-metal)</b>
 *
 * @param queue
 * Pointer to the queue in which node is to be inserted.
 *
 * @param node
 * Node to be inserted.
 *
 * @param do_locking
 * Determines whether we need to acquire mutex on the queue
 * (0: No, 1: Yes)
 *
 *
 * This method enqueues a node in the queue.
 *
 */
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


/**
 * <b>(bare-metal)</b>
 *
 * @param queue
 * Queue in which request-node is to be inserted.
 *
 * @param request_number
 * Request-number to be assigned to the newly created request-node.
 *
 * @param tokens
 * Tokens to be assigned to the newly created request-node.
 *
 *
 * This method allocates a new node for the request, and then passes
 * onto <b>enqueue_node</b> method to enqueue the node in queue.
 */
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


/**
 * <b>(bare-metal)</b>
 *
 * @param queue
 * Queue in which the passed request-node needs to be enqueued.
 *
 * @param node
 * Request-node to be inserted into the queue.
 *
 *
 * This method adds an already existing node to the queue (i.e. no new
 * memory allocation is done).
 */
void
enqueue_node_existing(struct Traffic_Queue *queue,
                      struct Traffic_Queue_Node *node) {

    enqueue_node(queue, node, 1);
}


/**
 * <b>(bare-metal)</b>
 *
 * @param queue
 * Queue from which the oldest node is to be dequeued.
 *
 * @param do_locking
 * Specifies whether we need to lock the queue for operations
 * (0:No, 1:Yes).
 *
 * @param remaining_tokens
 * Number of remaining tokens from the thread, that is calling this
 * function.
 *
 * @param do_log_remaining_tokens
 * Specified whether we need to log the information about
 * <b>remaining_tokens</b>
 *
 * This method returns the oldest node in the queue.
 * If queue is empty, NULL is returned.
 *
 */
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


/**
 * <b>(bare-metal)</b>
 *
 * @param queue
 * Pointer to queue
 *
 * @param tokens
 * Number of tokens currently possessed by the calling thread.
 *
 *
 * This method removes and returns the oldest node conditionally.
 */
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
