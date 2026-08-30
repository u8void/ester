#pragma once

#include"ester_arg.h"
#include <stdbool.h>

typedef enum
{
    ESTER_ERROR = 0 ,
    ESTER_WARN,
    ESTER_INFO,
    ESTER_DEBUG
} ester_log_level_t;

typedef struct
{
    const char* name;
    ester_log_level_t level;
} ester_logger_t;

typedef enum
{
    ESTER_STDOUT,
    ESTER_FILE,
    ESTER_ALL
}ester_stream_t;

int
ester_printer(const ester_logger_t* logger,
              const ester_log_level_t level,
              const ester_arg_t* args,
              const ester_stream_t stream,
              const char* function,
              const char* filename,
              const char* fmt) ;

#define ESTER_LOG(logger, level, stream, fmt, ...)                 \
    ester_printer(                                                 \
        &(logger),                                                 \
        (level),                                                   \
        (ester_arg_t[]){ __VA_OPT__(MAP_ARG(__VA_ARGS__)) },       \
        (stream),                                                  \
        __FUNCTION__,                                              \
        __FILE__,                                                  \
        (fmt)                                                      \
    )


#define ESTER_LOG_WARN(logger, fmt, ...) \
    ESTER_LOG(logger, ESTER_WARN, ESTER_STDOUT, fmt __VA_OPT__(,) __VA_ARGS__)

#define ESTER_LOG_INFO(logger, fmt, ...) \
    ESTER_LOG(logger, ESTER_INFO, ESTER_STDOUT, fmt __VA_OPT__(,) __VA_ARGS__)

#define ESTER_LOG_ERR(logger, fmt, ...) \
    ESTER_LOG(logger, ESTER_ERROR, ESTER_STDOUT, fmt __VA_OPT__(,) __VA_ARGS__)


#define ESTER_LOGF_WARN(logger, fmt, ...) \
    ESTER_LOG(logger, ESTER_WARN, ESTER_FILE, fmt __VA_OPT__(,) __VA_ARGS__)

#define ESTER_LOGF_INFO(logger, fmt, ...) \
    ESTER_LOG(logger, ESTER_INFO, ESTER_FILE, fmt __VA_OPT__(,) __VA_ARGS__)

#define ESTER_LOGF_ERR(logger, fmt, ...) \
    ESTER_LOG(logger, ESTER_ERROR, ESTER_FILE, fmt __VA_OPT__(,) __VA_ARGS__)


#define ESTER_LOGM_WARN(logger, fmt, ...) \
    ESTER_LOG(logger, ESTER_WARN, ESTER_ALL, fmt __VA_OPT__(,) __VA_ARGS__)

#define ESTER_LOGM_INFO(logger, fmt, ...) \
    ESTER_LOG(logger, ESTER_INFO, ESTER_ALL, fmt __VA_OPT__(,) __VA_ARGS__)

#define ESTER_LOGM_ERR(logger, fmt, ...) \
    ESTER_LOG(logger, ESTER_ERROR, ESTER_ALL, fmt __VA_OPT__(,) __VA_ARGS__)


#define ESTER_ABORT(logger, fmt, ...)                              \
    do                                                             \
    {                                                              \
        ESTER_LOG(logger, ESTER_ERROR, ESTER_ALL,                  \
                  fmt __VA_OPT__(,) __VA_ARGS__);                  \
        abort();                                                   \
    } while (0)
