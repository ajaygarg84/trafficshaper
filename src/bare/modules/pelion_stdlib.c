#include "pelion_stdlib.h"
#include "pelion_system.h"
#include "pelion_log.h"

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

/**
  * @file pelion_stdlib.c
  */


/**
 * <b>(bare-metal)</b>
 *
 * @param num
 * Number which needs to be converted to float.
 *
 * @param base
 * <b>num</b> will be divided by this <b>base</b>, and resultant float will be
 * generated.
 *
 * @param dest
 * Destination-buffer, into which the float-result will be written as
 * string.
 *
 * @param max_dest_size
 * maximum buffer-size for <b>dest</b>.
 *
 * There is no universal/easy solution for a bare-metal version for supporting
 * format-specifier for float. So, this utility-function partially
 * fulfills the requirement, as per examples below :
 *
 *  num = 1234, base = 1\n
 *  dest will be written with 1234.0
 *
 *  num = 1234, base = 10\n
 *  dest will be written with 123.4
 *
 *  num = 1234, base = 100\n
 *  dest will be written with 12.34

 *  num = 1234, base = 1000\n
 *  dest will be written with 1.234
 */
void
pelion_convert_numeric_to_float(long num, unsigned short base,
                                char *dest, int max_dest_size) {

    char *prefix = "";
    memset((void*) dest, 0, max_dest_size);

    if(num < 0) {
        num = num * -1;
        prefix = "-";
    }

    pelion_sprintf(dest, "%s%lu.%lu", prefix, num / base, num % base);
}


/**
 * Pointer to
 *
 *      struct Arg_Type arg_types_defs[]
 *
 * in src/bare/apps/trafficshaper/main.c
 */
extern struct Arg_Type *arg_types;


/**
 * <b>(bare-metal)</b>
 *
 * @param argc
 * Number of command-line arguments.
 *
 * @param argv
 * Command-line arguments.
 *
 * This method parses the command-line arguments, and fills in the
 * variables holding the values during runtime.
 *
 * The mapping for command-line switches and the corresponding
 * variables is given as per definition of
 *
 *      struct Arg_Type arg_types_defs[]
 *
 * in src/bare/apps/trafficshaper/main.c
 */
void
parse_cmd_line_args(int argc, char *argv[]) {

    int i = 0, j = 0;

    for(i = 0; i < argc; i++) {

        if(argv[i][0] == '-') {

            j = 0;
            while(1) {

                if(arg_types[j].value == NULL) {
                    break;

                } else {
                    if( (strlen(argv[i]) == 2) &&
                        (argv[i][1] == arg_types[j].id) &&
                        (i < (argc - 1))
                      ) {

                        *(arg_types[j].value) = atoi(argv[i + 1]);

                        /*
                         * Check if stringified-numeric-argument is
                         * really numeric or not.
                         */
                        {
                            char small[10] = {0};

                            pelion_sprintf(
                                    small, "%d", *(arg_types[j].value));

                            if(strlen(small) != strlen(argv[i + 1])) {
                                *(arg_types[j].value) = 0;
                            }
                        }

                        pelion_log(DEBUG, "[-%c] [%s] ==> [%d]\n",
                                  arg_types[j].id,
                                  arg_types[j].user_friendly_name,
                                  *(arg_types[j].value));

                        break;
                    }
                }

                j++;
            }
        }
    }

    /*
     * Now check whether any field could not be filled up.
     */
    j = 0;
    while(1) {

        if(arg_types[j].value == NULL) {
            break;

        } else {
            if(*(arg_types[j].value) <= 0)
            {
                pelion_log(ERROR, "Invalid/Unknown value for [-%c] [%s], "
                          "exiting\n",
                          arg_types[j].id,
                          arg_types[j].user_friendly_name);

                pelion_exit();
            }
        }

        j++;
    }
}


