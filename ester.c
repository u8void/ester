#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "ester.h"
#include <sys/uio.h>

/* Look bro when i wrote this only god and me knew how it works
 * now only gods know
 */

void ester_init_logger(ester_logger_t* logger,
                 const char* name)
{
    logger->name = name;
    logger->fd = open(name,
                      O_WRONLY | O_CREAT | O_APPEND,
                      0644);
}

void ester_destroy_logger(ester_logger_t* logger)
{
    if (logger->fd >= 0)
    {
        close(logger->fd);
        logger->fd = -1;
    }}

static inline size_t
int_to_buffer(char *buffer, int x)
{
    char temp[32];
    size_t i = 0;
    size_t out = 0;

    unsigned int value;

    if (x < 0)
    {
        buffer[out++] = '-';
        value = (unsigned int)(-(x + 1)) + 1;
    }
    else
    {
        value = (unsigned int)x;
    }

    do
    {
        temp[i++] = (char)('0' + (value % 10));
        value /= 10;
    }
    while (value);

    while (i)
        buffer[out++] = temp[--i];

    return out;
}

static inline size_t
uint_to_buffer(char *buffer, size_t x)
{
    char temp[32];
    size_t i = 0;
    size_t out = 0;

    do
    {
        temp[i++] = (char)('0' + (x % 10));
        x /= 10;
    }
    while (x);

    while (i)
        buffer[out++] = temp[--i];

    return out;
}

#include <stdint.h>

static inline size_t
float_to_buffer(char *buffer, float x)
{
    size_t out = 0;

    if (x != x) {
        buffer[0] = 'n';
        buffer[1] = 'a';
        buffer[2] = 'n';
        return 3;
    }

    if (x > 3.402823466e+38f) {
        buffer[0] = 'i';
        buffer[1] = 'n';
        buffer[2] = 'f';
        return 3;
    }

    if (x < -3.402823466e+38f) {
        buffer[0] = '-';
        buffer[1] = 'i';
        buffer[2] = 'n';
        buffer[3] = 'f';
        return 4;
    }

    if (x < 0.0f) {
        buffer[out++] = '-';
        x = -x;
    }

    uint32_t integer = (uint32_t)x;
    float fractional = x - (float)integer;

    out += uint_to_buffer(buffer + out, integer);

    buffer[out++] = '.';

    for (int i = 0; i < 6; ++i) {
        fractional *= 10.0f;

        uint32_t digit = (uint32_t)fractional;

        buffer[out++] = (char)('0' + digit);

        fractional -= (float)digit;
    }

    while (out > 0 && buffer[out - 1] == '0')
        --out;

    if (out > 0 && buffer[out - 1] == '.')
        --out;

    return out;
}

static inline size_t
double_to_buffer(char *buffer, double x)
{
    size_t out = 0;

    if (x != x) {
        buffer[0] = 'n';
        buffer[1] = 'a';
        buffer[2] = 'n';
        return 3;
    }

    if (x < 0.0) {
        buffer[out++] = '-';
        x = -x;
    }

    uint64_t integer = (uint64_t)x;
    double fractional = x - (double)integer;

    out += uint_to_buffer(buffer + out, (size_t)integer);

    buffer[out++] = '.';

    for (int i = 0; i < 12; ++i) {
        fractional *= 10.0;

        uint32_t digit = (uint32_t)fractional;

        buffer[out++] = (char)('0' + digit);

        fractional -= (double)digit;
    }

    while (out > 0 && buffer[out - 1] == '0')
        --out;

    if (out > 0 && buffer[out - 1] == '.')
        --out;

    return out;
}

static inline size_t
ptr_to_buffer(char *buffer, const void *ptr)
{
    uintptr_t value = (uintptr_t)ptr;
    static const char hex[] = "0123456789abcdef";

    char temp[sizeof(uintptr_t) * 2];
    size_t i = 0;
    size_t out = 0;

    buffer[out++] = '0';
    buffer[out++] = 'x';

    do
    {
        temp[i++] = hex[value & 0xF];
        value >>= 4;
    }
    while (value);

    while (i)
        buffer[out++] = temp[--i];

    return out;
}

const char* get_logtag(ester_log_level_t level)
{
    const char* logtag;

    switch (level)
    {
        case ESTER_INFO: logtag = "[INFO]";
        break;

        case ESTER_WARN: logtag = "[WARN]";
        break;

        case ESTER_ERROR: logtag = "[ERROR]";
        break;

        case ESTER_DEBUG: logtag = "[DEBUG]";
        break;
    }

    return logtag;
}

ester_string_t
ester_format_parser(const ester_arg_t *restrict args,
                    const char *restrict fmt)
{
    static char buffer[8192];

    char *out = buffer;
    size_t k = 0;

    while (*fmt)
    {
        if (fmt[0] == '{' && fmt[1] == '}')
        {
            const ester_arg_t *arg = &args[k++];

            switch (arg->type)
            {
                case ARG_INT:
                    out += int_to_buffer(out, arg->i);
                    break;

                case ARG_UINT:
                    out += uint_to_buffer(out, arg->u);
                    break;

                case ARG_FLOAT:
                    out += float_to_buffer(out, arg->f);
                    break;

                case ARG_DOUBLE:
                    out += double_to_buffer(out, arg->d);
                    break;

                case ARG_CHAR:
                    *out++ = arg->c;
                    break;

                case ARG_STRING:
                {
                    const char *s = arg->s ? arg->s : "(null)";
                    size_t len = strlen(s);

                    memcpy(out, s, len);
                    out += len;
                    break;
                }

                case ARG_POINTER:
                    out += ptr_to_buffer(out, arg->p);
                    break;
            }

            fmt += 2;
        }
        else
        {
            *out++ = *fmt++;
        }
    }

    *out = '\0';

    return (ester_string_t){
        .data = buffer,
        .len = (size_t)(out - buffer)
    };
}

inline ester_string_t
get_metadata(const char *function,
             const char *filename,
             int line,
             ester_log_level_t level)
{
    static char buffer[1024];

    char *out = buffer;

    const char *tag = get_logtag(level);

    size_t len = strlen(tag);
    memcpy(out, tag, len);
    out += len;
    *out++ = ' ';
    len = strlen(filename);
    memcpy(out, filename, len);
    out += len;
    *out++ = '-';
    *out++ = '>';
    len = strlen(function);
    memcpy(out, function, len);
    out += len;
    *out++ = ':';
    out += int_to_buffer(out, line);
    *out++ = ' ';
    *out = '\0';

    return (ester_string_t){
        .data = buffer,
        .len = (size_t)(out - buffer)
    };
}

void ester_printer(ester_logger_t *logger,
                   ester_stream_t stream,
                   ester_string_t metadata,
                   ester_string_t msg)
{
    struct iovec iov[2];

    iov[0].iov_base = (void *)metadata.data;
    iov[0].iov_len  = metadata.len;

    iov[1].iov_base = (void *)msg.data;
    iov[1].iov_len  = msg.len;

    switch (stream)
    {
        case ESTER_STDOUT:
            writev(STDOUT_FILENO, iov, 2);
            break;

        case ESTER_FILE:
            writev(logger->fd, iov, 2);
            break;

        case ESTER_ALL:
            writev(STDOUT_FILENO, iov, 2);
            writev(logger->fd, iov, 2);
            break;
    }
}
