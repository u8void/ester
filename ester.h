#pragma once

#include"ester_arg.h"
#include <stdbool.h>

typedef struct
{
    const char *data;
    size_t len;
} ester_string_t;

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
    int fd ;
} ester_logger_t;

typedef enum
{
    ESTER_STDOUT,
    ESTER_FILE,
    ESTER_ALL
}ester_stream_t;

ester_string_t
ester_format_parser(const ester_arg_t* args,
                    const char* fmt);
ester_string_t
get_metadata(const char* function,
             const char* filename,
             const int line,
             ester_log_level_t level);

void ester_printer(ester_logger_t *logger,
                   ester_stream_t stream,
                   ester_string_t metadata,
                   ester_string_t msg);


void ester_init_logger(ester_logger_t* logger,
                 const char* name);
void ester_destroy_logger(ester_logger_t* logger);

#define ESTER_LOG_INFO(logger,fmt, ...)                                 \
    ester_printer(&logger,                                              \
                  ESTER_STDOUT,                                         \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_INFO),  \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt                                               \
                )                                                       \
    )

#define ESTER_LOG_WARN(logger,fmt, ...)                                 \
    ester_printer(&logger,                                              \
                  ESTER_STDOUT,                                         \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_WARN),  \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt                                               \
                )                                                       \
    )

#define ESTER_LOG_ERROR(logger,fmt, ...)                                \
    ester_printer(&logger,                                              \
                  ESTER_STDOUT,                                         \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_ERROR), \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt                                               \
                )                                                       \
    )

#define ESTER_LOG_DEBUG(logger,fmt, ...)                                \
    ester_printer(&logger,                                              \
                  ESTER_STDOUT,                                         \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_DEBUG), \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt                                               \
                )                                                       \
    )

#define ESTER_LOGF_INFO(logger,fmt, ...)                                \
    ester_printer(&logger,                                              \
                  ESTER_FILE,                                           \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_INFO),  \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt                                               \
                )                                                       \
    )

#define ESTER_LOGF_WARN(logger,fmt, ...)                                \
    ester_printer(&logger,                                              \
                  ESTER_FILE,                                           \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_WARN),  \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt                                               \
                )                                                       \
    )

#define ESTER_LOGF_ERROR(logger,fmt, ...)                               \
    ester_printer(&logger,                                              \
                  ESTER_FILE,                                           \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_ERROR), \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt                                               \
                )                                                       \
    )

#define ESTER_LOGF_DEBUG(logger,fmt, ...)                               \
    ester_printer(&logger,                                              \
                  ESTER_FILE,                                           \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_DEBUG), \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt                                               \
                )                                                       \
    )

#define ESTER_LOGM_INFO(logger,fmt, ...)                                \
    ester_printer(&logger,                                              \
                  ESTER_ALL,                                            \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_INFO),  \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt                                               \
                )                                                       \
    )

#define ESTER_LOGM_WARN(logger,fmt, ...)                                \
    ester_printer(&logger,                                              \
                  ESTER_ALL,                                            \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_WARN),  \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt                                               \
                )                                                       \
    )

#define ESTER_LOGM_ERROR(logger,fmt, ...)                               \
    ester_printer(&logger,                                              \
                  ESTER_ALL,                                            \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_ERROR), \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt                                               \
                )                                                       \
    )

#define ESTER_LOGM_DEBUG(logger,fmt, ...)                               \
    ester_printer(&logger,                                              \
                  ESTER_ALL,                                            \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_DEBUG), \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt                                               \
                )                                                       \
    )

#define ESTER_LOGLN_INFO(logger,fmt, ...)                               \
    ester_printer(&logger,                                              \
                  ESTER_STDOUT,                                         \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_INFO),  \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt "\n"                                          \
                )                                                       \
    )

#define ESTER_LOGLN_WARN(logger,fmt, ...)                               \
    ester_printer(&logger,                                              \
                  ESTER_STDOUT,                                         \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_WARN),  \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt "\n"                                          \
                )                                                       \
    )

#define ESTER_LOGLN_ERROR(logger,fmt, ...)                              \
    ester_printer(&logger,                                              \
                  ESTER_STDOUT,                                         \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_ERROR), \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt "\n"                                          \
                )                                                       \
    )

#define ESTER_LOGLN_DEBUG(logger,fmt, ...)                              \
    ester_printer(&logger,                                              \
                  ESTER_STDOUT,                                         \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_DEBUG), \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt "\n"                                          \
                )                                                       \
    )

#define ESTER_LOGFLN_INFO(logger,fmt, ...)                              \
    ester_printer(&logger,                                              \
                  ESTER_FILE,                                           \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_INFO),  \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt "\n"                                          \
                )                                                       \
    )

#define ESTER_LOGFLN_WARN(logger,fmt, ...)                              \
    ester_printer(&logger,                                              \
                  ESTER_FILE,                                           \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_WARN),  \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt "\n"                                          \
                )                                                       \
    )

#define ESTER_LOGFLN_ERROR(logger,fmt, ...)                             \
    ester_printer(&logger,                                              \
                  ESTER_FILE,                                           \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_ERROR), \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt "\n"                                          \
                )                                                       \
    )

#define ESTER_LOGFLN_DEBUG(logger,fmt, ...)                             \
    ester_printer(&logger,                                              \
                  ESTER_FILE,                                           \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_DEBUG), \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt "\n"                                          \
                )                                                       \
    )

#define ESTER_LOGMLN_INFO(logger,fmt, ...)                              \
    ester_printer(&logger,                                              \
                  ESTER_ALL,                                            \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_INFO),  \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt "\n"                                          \
                )                                                       \
    )

#define ESTER_LOGMLN_WARN(logger,fmt, ...)                              \
    ester_printer(&logger,                                              \
                  ESTER_ALL,                                            \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_WARN),  \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt "\n"                                          \
                )                                                       \
    )

#define ESTER_LOGMLN_ERROR(logger,fmt, ...)                             \
    ester_printer(&logger,                                              \
                  ESTER_ALL,                                            \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_ERROR), \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt "\n"                                          \
                )                                                       \
    )

#define ESTER_LOGMLN_DEBUG(logger,fmt, ...)                             \
    ester_printer(&logger,                                              \
                  ESTER_ALL,                                            \
                  get_metadata(__func__,__FILE__,__LINE__,ESTER_DEBUG), \
                  ester_format_parser(                                  \
                      (ester_arg_t[]){__VA_OPT__(MAP_ARG(__VA_ARGS__))},\
                      fmt "\n"                                          \
                )                                                       \
    )

#define ESTER_ABORT(logger, fmt, ...)                              \
    do                                                             \
    {                                                              \
        ESTER_LOGM_ERROR(logger,                                   \
                  fmt ,__VA_ARGS__);                               \
        abort();                                                   \
    } while (0)
