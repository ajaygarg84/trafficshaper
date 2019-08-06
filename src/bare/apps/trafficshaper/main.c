#include "pelion_cmd_args.h"
#include "pelion_log.h"
#include "pelion_mutex.h"
#include "pelion_thread.h"
#include "pelion_time.h"

#include "traffic_queue.h"

struct Pelion_Queue Q1;
struct Pelion_Queue Q2;

void* request_generator_infinite_loop(void *arg);
void* token_generator_infinite_loop(void *arg);

int main(int argc, char *argv[]) {

    /*
     * Initialize the mutexes used in the system.
     */
    pelion_init_mutex(&log_mtx);
    pelion_init_mutex(&(Q1.mtx));
    pelion_init_mutex(&(Q2.mtx));

    /*
     * Initialize the backend logger.
     */
    init_log_on_device();

    /*
     * Fetch the configurable parameters passed via command line.
     */
    parse_cmd_line_args(argc, argv);

    /*
     * Start the threads.
     */
    start_thread(request_generator_infinite_loop, NULL);
    start_thread(token_generator_infinite_loop, NULL);

    while(1) {
        pelion_delay_ms(1000);
    }

    return 0;
}
