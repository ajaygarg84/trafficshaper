#ifndef I_PELION_STDLIB
#define I_PELION_STDLIB

#include <stdarg.h>



void
pelion_varargs(char *dest, const char *fmt, va_list var_args_params);

void
pelion_sprintf(char *dest, const char *format, ...);

void
pelion_convert_numeric_to_float(long num, unsigned short base,
                                char *dest, int max_dest_size);

void
parse_cmd_line_args(int argc, char *argv[]);

struct Arg_Type {

    char id;
    char *user_friendly_name;
    int *value;
};

#endif


