#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "ester_arg.h"
#include "ester.h"

/* Look bro when i wrote this only god and me knew how it works
 * now only gods know
 */

static size_t get_string_lenght(const char* fmt)
{
    size_t len = 0;
    const char* p = fmt;

    while (*p != '\0')
    {
        len++;
        p++;
    }

    return len;
}

static const char* int_to_string(int x)
{
    static char buffer[32];
    char temp[32];

    unsigned int n;
    size_t i = 0;

    if (x < 0)
    {
        buffer[0] = '-';

        n = (unsigned int)(-(x + 1)) + 1;
    }
    else
    {
        n = (unsigned int)x;
    }

    do
    {
        temp[i++] = '0' + (n % 10);
        n /= 10;
    } while (n);

    size_t out = x < 0 ? 1 : 0;

    while (i)
        buffer[out++] = temp[--i];

    buffer[out] = '\0';

    return buffer;
}

static const char* double_to_string(double x)
{
    static char buffer[64];

    snprintf(buffer, sizeof(buffer), "%g", x);

    return buffer;
}

static const char* uint_to_string(unsigned int x)
{
    static char buffer[32];

    snprintf(buffer, sizeof(buffer), "%u", x);

    return buffer;
}

static const char* char_to_string(char x)
{
    static char buffer[2];

    buffer[0] = x;
    buffer[1] = '\0';

    return buffer;
}

static const char* ptr_to_string(const void* x)
{
    static char buffer[32];

    snprintf(buffer, sizeof(buffer), "%p", x);

    return buffer;
}

static size_t int_to_buffer(char *buffer, int x)
{
    char temp[32];
    size_t i = 0;
    size_t out = 0;

    unsigned int n;

    if (x < 0)
    {
        buffer[out++] = '-';
        n = (unsigned int)(-(x + 1)) + 1;
    }
    else
    {
        n = (unsigned int)x;
    }

    do
    {
        temp[i++] = (char)('0' + (n % 10));
        n /= 10;
    } while (n != 0);

    while (i > 0)
    {
        buffer[out++] = temp[--i];
    }

    return out;
}

static size_t uint_to_buffer(char *buffer, unsigned int x)
{
    char temp[32];
    size_t i = 0;
    size_t out = 0;

    do
    {
        temp[i++] = (char)('0' + (x % 10));
        x /= 10;
    } while (x != 0);

    while (i > 0)
        buffer[out++] = temp[--i];

    return out;
}

const char* get_logtag(ester_log_level_t level)
{
    const char* logtag;

    switch (level)
    {
        case ESTER_INFO: logtag = "[INFO] ";
        break;

        case ESTER_WARN: logtag = "[WARN] ";
        break;

        case ESTER_ERROR: logtag = "[ERROR] ";
        break;

        case ESTER_DEBUG: logtag = "[DEBUG] ";
        break;
    }

    return logtag;
}


int
ester_printer(const ester_logger_t* logger,
              const ester_log_level_t level,
              const ester_arg_t* args,
              const ester_stream_t stream,
              const char* function,
              const char* filename,
              const char* fmt)
{
    char buffer[8192];
    size_t out = 0;

    for (size_t i = 0, k = 0; fmt[i] != '\0'; )
    {
        if (fmt[i] == '{' && fmt[i + 1] == '}')
        {
            switch (args[k].type)
            {
                case ARG_INT:
                    out += int_to_buffer(buffer + out, args[k].i);
                    break;

                case ARG_UINT:
                {
                    const char *str = TO_STRING(args[k].u);

                    while (*str)
                        buffer[out++] = *str++;

                    break;
                }

                case ARG_FLOAT:
                case ARG_DOUBLE:
                {
                    const char *str = TO_STRING(args[k].d);

                    while (*str)
                        buffer[out++] = *str++;

                    break;
                }

                case ARG_CHAR:
                {
                    const char *str = TO_STRING(args[k].c);

                    while (*str)
                        buffer[out++] = *str++;

                    break;
                }

                case ARG_STRING:
                {
                    const char *str = args[k].s;

                    while (*str)
                        buffer[out++] = *str++;

                    break;
                }

                case ARG_POINTER:
                {
                    const char *str = TO_STRING(args[k].p);

                    while (*str)
                        buffer[out++] = *str++;

                    break;
                }

                default:
                    break;
            }

            k++;
            i += 2;
        }
        else
        {
            buffer[out++] = fmt[i++];
        }
    }

    buffer[out] = '\0';

    const char* logtag = get_logtag(level);

    switch (stream)
    {
        case ESTER_STDOUT:
        {
            write(1, logtag, strlen(logtag));
            write(1, filename, strlen(filename)) ;
            write(1, "->", 2);
            write(1, function, strlen(function)) ;
            write(1, " ", 1);
            write(1, buffer, out);
        }
        break;

        case ESTER_FILE:
        {
            int fd = open(
                logger->name,
                O_WRONLY | O_CREAT | O_APPEND,
                0644
            );

            write(fd, logtag, strlen(logtag));
            write(fd, " ", 1);
            write(fd, filename, strlen(filename)) ;
            write(fd, " ", 1);
            write(fd, function, strlen(function)) ;
            write(fd, " ", 1);
            write(fd, buffer, out);

        }
        break;

        case ESTER_ALL:
        {
            write(1, logtag, strlen(logtag));
            write(1, " ", 1);
            write(1, filename, strlen(filename)) ;
            write(1, " ", 1);
            write(1, function, strlen(function)) ;
            write(1, " ", 1);
            write(1, buffer, out);

            int fd = open(
                logger->name,
                O_WRONLY | O_CREAT | O_APPEND,
                0644
            );

            write(fd, logtag, strlen(logtag));
            write(fd, " ", 1);
            write(fd, filename, strlen(filename)) ;
            write(fd, " ", 1);
            write(fd, function, strlen(function)) ;
            write(fd, " ", 1);
            write(fd, buffer, out);
        }
        break;
    }

    return 0;
}
