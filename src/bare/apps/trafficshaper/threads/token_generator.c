#include "pelion_thread.h"
#include "pelion_log.h"
#include "pelion_time.h"
#include "pelion_stdlib.h"

#include "app.h"
#include "traffic_queue.h"

void *token_generator_infinite_loop(void *arg) {

    unsigned long remaining_tokens = 0;

    while(1)
    {
        pelion_delay_ms(pelion_globals.x_tokens_rate_T2 * 1000);

        remaining_tokens++;

        while(1) {
            struct Traffic_Queue_Node *result =
                get_oldest_node_if_applicable(&Q1, remaining_tokens);

            if(result != NULL) {

                /*
                 * We have a node ready to be moved from Q1 to Q2.
                 */

                /*
                 * Update remaining tokens.
                 */
                remaining_tokens = remaining_tokens - result->tokens;

                /*
                 * Log removal from Q1.
                 */
                {
                    char str_time_in_us_in_Q1[20] = {0};

                    unsigned long time_in_us_in_Q1 =
                        get_current_timestamp_us() - result->time_us;

                    pelion_convert_numeric_to_float(
                            time_in_us_in_Q1,
                            1000,
                            str_time_in_us_in_Q1,
                            sizeof(str_time_in_us_in_Q1));

                    pelion_log(EVENT, "r%u leaves Q1, time in Q1 = %sms, "
                                      "remaining_token = %u\n",
                                      result->request_number,
                                      str_time_in_us_in_Q1,
                                      remaining_tokens);

                }

                /*
                 * Insert the node into Q2, and log.
                 */
                enqueue_node_existing(&Q2, result);

                pelion_log(EVENT, "r%u enters Q2\n",
                                  result->request_number);

            } else {
                break;
            }
        }
    }
}
