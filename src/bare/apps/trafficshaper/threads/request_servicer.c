#include "pelion_thread.h"
#include "pelion_log.h"
#include "pelion_time.h"
#include "pelion_stdlib.h"
#include "pelion_system.h"

#include "app.h"
#include "traffic_queue.h"

#include <stdio.h>


/**
 * @file request_servicer.c
 */

/**
 * This is the entry-point function for thread S.\n
 * S does the following things :
 *
 * * If/when a request is available/pending from Q2, thread S:
 *
 *  * Dequeues the request from Q2.
 *  * Processes the request (taking <b>t</b> seconds, where <b>t</b> is
 *   given by command-line).
 *
 * * If no request is available, S waits for a request to be available in
 *   Q2.
 *
 * Note that no busy-waiting is involved, by using a
 * mutex-and-condition-variable paradigm for queue Q2 and
 * threads T2 (token_generator.c) and S.
 */
void *request_servicer_infinite_loop_no_busy_waiting(void *arg) {

    struct Traffic_Queue_Node *request_node = NULL;
    unsigned long long service_start_time_us = 0;

    while(1) {

        /*
         * While there are requests in Q2 that can be processed,
         * dequeue-and-execute them (one at a time of course).
         */

        /*
         * Use the awesome mutex-&-condition-variable combo to avoid
         * busy-waiting
         */
        pelion_acquire_mutex(&(Q2.mtx));

        request_node = get_oldest_node(&Q2, 0, 0, 0);

        while(request_node == NULL) {

            pelion_wait_on_condition_variable(&(Q2.cond), &(Q2.mtx));
            request_node = get_oldest_node(&Q2, 0, 0, 0);
        }

        pelion_release_mutex(&(Q2.mtx));


        /*
         * If we reach here, we have a request to process.
         */

        /*
         * Log the start of request-servicing.
         */
        pelion_log(EVENT, "r%u begins service at S, "
                          "requesting %ums of service\n",
                          request_node->request_number,
                          pelion_globals.t_time_per_request_S * 1000);

        service_start_time_us = pelion_get_current_timestamp_us();

        /*
         * Emulate servicing by sleeping.
         */
        pelion_delay_us(pelion_globals.t_time_per_request_S * 1000000ULL);

        /*
         * Log the end of request-servicing
         */
        {
            char str_time_in_us_for_servicing[20] = {0};
            char str_time_in_us_in_system[20] = {0};

            unsigned long long time_in_us_for_servicing =
                pelion_get_current_timestamp_us() - service_start_time_us;

            unsigned long long time_in_us_in_system =
                pelion_get_current_timestamp_us() -
                request_node->in_system_time_us;


            pelion_convert_numeric_to_float(
                    time_in_us_for_servicing,
                    1000,
                    str_time_in_us_for_servicing,
                    sizeof(str_time_in_us_for_servicing));

            pelion_convert_numeric_to_float(
                    time_in_us_in_system,
                    1000,
                    str_time_in_us_in_system,
                    sizeof(str_time_in_us_in_system));


            pelion_log(EVENT, "r%u departs from S, service time = %sms, "
                              "time in system = %sms\n",
                              request_node->request_number,
                              str_time_in_us_for_servicing,
                              str_time_in_us_in_system);
        }

        /*
         * Now, the request-lifecycle has completed, so free the node.
         */
        pelion_free(request_node);
    }
}

