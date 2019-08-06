#ifndef I_PELION_STDLIB
#define I_PELION_STDLIB

#include <stdarg.h>


void
pelion_varargs(char *out, const char *pcString, va_list vaArgP);

void
pelion_sprintf(char *out, const char *format, ...);

void
pelion_convert_numeric_to_float(long num, unsigned short base,
                                char *dest, int max_dest_size);

#endif


