#include "pelion_queue.h"
#include "pelion_cmd_args.h"
#include "pelion_log.h"
#include "pelion_mutex.h"

struct Pelion_Queue Q1;
struct Pelion_Queue Q2;


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

    return 0;
}
