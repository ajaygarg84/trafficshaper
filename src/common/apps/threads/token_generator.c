#include "pelion_thread.h"
#include "pelion_log.h"
#include "pelion_cmd_args.h"
#include "pelion_time.h"
#include "pelion_stdlib.h"

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

                remaining_tokens = remaining_tokens - result->tokens;
                Q1.requests_dequeued++;

                {
                    char str_time_in_us_in_Q1[20] = {0};

                    unsigned long time_in_us_in_Q1 =
                        get_current_time_us() - result->time_us;

                    pelion_convert_numeric_to_float(
                            time_in_us_in_Q1,
                            1000,
                            str_time_in_us_in_Q1,
                            sizeof(str_time_in_us_in_Q1));

                    pelion_log(EVENT, "r%u leaves Q1, time in Q1 = %sms, "
                                      "remaining_token = %u\n",
                                      Q1.requests_dequeued,
                                      str_time_in_us_in_Q1,
                                      remaining_tokens);

                }

            } else {
                break;
            }
        }
    }
}

