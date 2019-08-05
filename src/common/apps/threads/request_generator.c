#include "pelion_thread.h"
#include "pelion_log.h"
#include "pelion_queue.h"
#include "pelion_cmd_args.h"
#include "pelion_time.h"

void *request_generator_infinite_loop(void *arg) {

    while(1)
    {
        pelion_delay_ms(pelion_globals.r_request_rate_T1 * 1000);

        Q1.requests_enqueued++;

        pelion_log(EVENT, "r%u arrives, need %d tokens\n",
                          Q1.requests_enqueued,
                          pelion_globals.R_tokens_per_request);


        if(pelion_globals.R_tokens_per_request <
           pelion_globals.L_max_unused_tokens) {

            add_new_node(&Q1, pelion_globals.R_tokens_per_request);
            pelion_log(EVENT, "r%u enters Q1\n", Q1.requests_enqueued);

        } else {

            pelion_log(WARN, "Not enqueuing r%u, as tokens exceeded\n\n");
        }

    }
}
