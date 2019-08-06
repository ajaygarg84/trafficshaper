#include "pelion_stdlib.h"
#include "pelion_system.h"
#include "pelion_log.h"

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

static const char * const g_pcHex = "0123456789abcdef";

void
pelion_varargs(char *out, const char *pcString, va_list vaArgP)
{
    unsigned long ulIdx, ulValue, ulPos, ulCount, ulBase, ulNeg, temp;
    char *pcStr, pcBuf[16], cFill;

    /*
     * Loop while there are more characters in the string.
     */
    while(*pcString)
    {
        /*
         * Find the first non-% character, or the end of the string.
         */
        for(ulIdx = 0; (pcString[ulIdx] != '%') && (pcString[ulIdx] != '\0');
            ulIdx++) {
        }

        /*
         * Write this portion of the string.
         */
        for(temp = 0; temp < ulIdx; temp++) {
            *out = pcString[temp];
            out++;
        }

        /*
         * Skip the portion of the string that was written.
         */
        pcString += ulIdx;

        /*
         * See if the next character is a %.
         */
        if(*pcString == '%') {
            /*
             * Skip the %.
             */
            pcString++;

            /*
             * Set the digit count to zero, and the fill character to space
             * (i.e. to the defaults).
             */
            ulCount = 0;
            cFill = ' ';

            /*
             * It may be necessary to get back here to process more
             * characters. Goto's aren't pretty, but effective.  I feel
             * extremely dirty for
             * using not one but two of the beasts.
             */
again:

            /*
             * Determine how to handle the next character.
             */
            switch(*pcString++) {
                /*
                 * Handle the digit characters.
                 */
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    /*
                     * If this is a zero, and it is the first digit, then the
                     * fill character is a zero instead of a space.
                     */
                    if((pcString[-1] == '0') && (ulCount == 0)) {
                        cFill = '0';
                    }

                    /*
                     * Update the digit count.
                     */
                    ulCount *= 10;
                    ulCount += pcString[-1] - '0';

                    /*
                     * Get the next character.
                     */
                    goto again;
                }

                /*
                 * Handle the %c command.
                 */
                case 'c': {
                    /*
                     * Get the value from the varargs.
                     */
                    ulValue = va_arg(vaArgP, unsigned long);

                    /*
                     * Print out the character.
                     */
                    *out = (char)ulValue;
                    out++;

                    /*
                     * This command has been handled.
                     */
                    break;
                }

                /*
                 * Handle the %d and %i commands.
                 */
                case 'd':
                case 'i': {
                    /*
                     * Get the value from the varargs.
                     */
                    ulValue = va_arg(vaArgP, unsigned long);

                    /*
                     * Reset the buffer position.
                     */
                    ulPos = 0;

                    /*
                     * If the value is negative, make it positive and indicate
                     * that a minus sign is needed.
                     */
                    if((long)ulValue < 0)
                    {
                        /*
                         * Make the value positive.
                         */
                        ulValue = -(long)ulValue;

                        /*
                         * Indicate that the value is negative.
                         */
                        ulNeg = 1;
                    }
                    else
                    {
                        /*
                         * Indicate that the value is positive so that a minus
                         * sign isn't inserted.
                         */
                        ulNeg = 0;
                    }

                    /*
                     * Set the base to 10.
                     */
                    ulBase = 10;

                    /*
                     * Convert the value to ASCII.
                     */
                    goto convert;
                }

                /*
                 * Handle the %s command.
                 */
                case 's':
                {
                    /*
                     * Get the string pointer from the varargs.
                     */
                    pcStr = va_arg(vaArgP, char *);

                    /*
                     * Determine the length of the string.
                     */
                    for(ulIdx = 0; pcStr[ulIdx] != '\0'; ulIdx++)
                    {
                    }

                    /*
                     * Write the string.
                     */
                    for(temp = 0; temp < ulIdx; temp++)
                    {
                        *out = pcStr[temp];
                        out++;
                    }

                    /*
                     * Write any required padding spaces
                     */
                    if(ulCount > ulIdx)
                    {
                        ulCount -= ulIdx;
                        while(ulCount--)
                        {
                            *out = ' ';
                            out++;
                        }
                    }

                    /*
                     * This command has been handled.
                     */
                    break;
                }

                /*
                 * Handle the %u command.
                 */
                case 'u': {
                    /*
                     * Get the value from the varargs.
                     */
                    ulValue = va_arg(vaArgP, unsigned long);

                    /*
                     * Reset the buffer position.
                     */
                    ulPos = 0;

                    /*
                     * Set the base to 10.
                     */
                    ulBase = 10;

                    /*
                     * Indicate that the value is positive so that a minus sign
                     * isn't inserted.
                     */
                    ulNeg = 0;

                    /*
                     * Convert the value to ASCII.
                     */
                    goto convert;
                }

                /*
                 * Handle the %x and %X commands.  Note that they are treated
                 * identically; i.e. %X will use lower case letters for a-f
                 * instead of the upper case letters is should use.  We also
                 * alias %p to %x.
                 */
                case 'x':
                case 'X':
                case 'p': {
                    /*
                     * Get the value from the varargs.
                     */
                    ulValue = va_arg(vaArgP, unsigned long);

                    /*
                     * Reset the buffer position.
                     */
                    ulPos = 0;

                    /*
                     * Set the base to 16.
                     */
                    ulBase = 16;

                    /*
                     * Indicate that the value is positive so that a minus sign
                     * isn't inserted.
                     */
                    ulNeg = 0;

                    /*
                     * Determine the number of digits in the string version of
                     * the value.
                     */
convert:
                    for(ulIdx = 1;
                        (((ulIdx * ulBase) <= ulValue) &&
                         (((ulIdx * ulBase) / ulBase) == ulIdx));
                        ulIdx *= ulBase, ulCount--)
                    {
                    }

                    /*
                     * If the value is negative, reduce the count of padding
                     * characters needed.
                     */
                    if(ulNeg) {
                        ulCount--;
                    }

                    /*
                     * If the value is negative and the value is padded with
                     * zeros, then place the minus sign before the padding.
                     */
                    if(ulNeg && (cFill == '0')) {
                        /*
                         * Place the minus sign in the output buffer.
                         */
                        pcBuf[ulPos++] = '-';

                        /*
                         * The minus sign has been placed, so turn off the
                         * negative flag.
                         */
                        ulNeg = 0;
                    }

                    /*
                     * Provide additional padding at the beginning of the
                     * string conversion if needed.
                     */
                    if((ulCount > 1) && (ulCount < 16)) {
                        for(ulCount--; ulCount; ulCount--) {
                            pcBuf[ulPos++] = cFill;
                        }
                    }

                    /*
                     * If the value is negative, then place the minus sign
                     * before the number.
                     */
                    if(ulNeg) {
                        /*
                         * Place the minus sign in the output buffer.
                         */
                        pcBuf[ulPos++] = '-';
                    }

                    /*
                     * Convert the value into a string.
                     */
                    for(; ulIdx; ulIdx /= ulBase) {
                        pcBuf[ulPos++] = g_pcHex[(ulValue / ulIdx) % ulBase];
                    }

                    /*
                     * Write the string.
                     */
                    for(temp = 0; temp < ulPos; temp++) {
                        *out = pcBuf[temp];
                        out++;
                    }

                    /*
                     * This command has been handled.
                     */
                    break;
                }

                /*
                 * Handle the %% command.
                 */
                case '%': {
                    /*
                     * Simply write a single %.
                     */
                    *out = '%';
                    out++;

                    /*
                     * This command has been handled.
                     */
                    break;
                }

                /*
                 * Handle all other commands.
                 */
                default: {
                    /*
                     * Indicate an error.
                     */

                    /*
                     * This command has been handled.
                     */
                    break;
                }
            }
        }
    }
}


void
pelion_sprintf(char *out, const char *format, ...) {

    va_list argptr;
    va_start(argptr, format);
    pelion_varargs(out, format, argptr);
    va_end(argptr);
}


void
pelion_convert_numeric_to_float(long num, unsigned short base,
                                char *dest, int max_dest_size) {

    char *prefix = "";
    memset((void*) dest, 0, max_dest_size);

    if(num < 0) {
        num = num * -1;
        prefix = "-";
    }

    pelion_sprintf(dest, "%s%u.%u", prefix, num / base, num % base);
}


extern struct Arg_Type *arg_types;

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
                        (argv[i][1]) == arg_types[j].id) {
                        *(arg_types[j].value) = atoi(argv[i + 1]);

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


