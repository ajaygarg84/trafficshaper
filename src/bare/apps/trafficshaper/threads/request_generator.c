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
 * Sleep for <b>r</b> seconds (where <b>r</b> r is given by
 * command-line).
 *
 * b)\n
 * Generate a request, and enqueue it into Q1.
 *
 * c)\n
 * Go to step a).
 *
 */
void *request_generator_infinite_loop(void *arg) {

    unsigned int requests_arrived = 0;
    while(1)
    {
        pelion_delay_ms(pelion_globals.r_request_rate_T1 * 1000);

        requests_arrived++;
        pelion_log(EVENT, "r%u arrives, need %d tokens\n",
                          requests_arrived,
                          pelion_globals.R_tokens_per_request);


        /*
         * If request-tokens are in permissible limits, add the request
         * into Q1.
         */
        if(pelion_globals.R_tokens_per_request <
           pelion_globals.L_max_unused_tokens) {

            enqueue_node_new(&Q1, pelion_globals.R_tokens_per_request);
            pelion_log(EVENT, "r%u enters Q1\n", requests_arrived);

        } else {

            pelion_log(WARN, "Not enqueuing r%u in Q1, as tokens "
                             "exceeded\n", requests_arrived);
        }
    }
}

