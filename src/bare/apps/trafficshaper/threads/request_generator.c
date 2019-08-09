#include "pelion_thread.h"
#include "pelion_log.h"
#include "pelion_time.h"

#include "app.h"
#include "traffic_queue.h"

/**
 * @file request_generator.c
 */

/**
 * This is the entry-point function for thread T1.\n
 * T1 does the following things :
 *
 * a)\n
 * Sleep for <b>r</b> seconds (where <b>r</b> is given by
 * command-line).
 *
 * b)\n
 * Generate a request, and enqueue it into Q1.
 *
 * c)\n
 * Go to step a).
 */
void *request_generator_infinite_loop(void *arg) {

    unsigned int requests_arrived = 0;

    while(1)
    {
        pelion_delay_us(
                pelion_globals.r_request_generation_interval_T1 * 1000000ULL);

        requests_arrived++;
        pelion_log(EVENT, "r%u arrives, need %d tokens\n",
                          requests_arrived,
                          pelion_globals.R_tokens_per_request);

        enqueue_node_new(&Q1,
                         requests_arrived,
                         pelion_globals.R_tokens_per_request);

    }
}

