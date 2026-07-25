#ifndef ESTER_LOGGING_H
#define ESTER_LOGGING_H

#include <stdio.h>
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
    const char* function;
    const char* filename;
    int line ;
} ester_log_metadata_t ;

typedef struct
{
    const char* msg;
    ester_log_metadata_t metadata;
} ester_log_msg;

typedef struct
{
    const char* name;
    ester_log_msg  msg;
    ester_log_level_t level;
} ester_logger_t;

typedef enum
{
    ESTER_STDOUT,
    ESTER_FILE,
    ESTER_ALL
}ester_stream_t;

void ester_printer(FILE* log_stream,
                const char* logtag,
                const char* filename,
                const char* function,
                const int line,
                const char* format,
                ...);

void ester_log (const ester_logger_t* logger,
                const ester_log_level_t level,
                const ester_stream_t stream_is_file,
                const char* filename,
                const char* function,
                const int line,
                const char* format,
                ...);

#define ESTER_LOG_WARN(logger,format,...) \
     ester_log((&logger), \
               ESTER_WARN, \
               ESTER_STDOUT, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOG_INFO(logger,format,...) \
     ester_log((&logger), \
               ESTER_INFO, \
               ESTER_STDOUT, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOG_ERR(logger,format,...) \
     ester_log((&logger), \
               ESTER_ERROR, \
               ESTER_STDOUT, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOGF_WARN(logger,format,...) \
     ester_log((&logger), \
               ESTER_WARN, \
               ESTER_FILE, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOGF_INFO(logger,format,...) \
     ester_log((&logger), \
               ESTER_INFO, \
               ESTER_FILE, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOGF_ERR(logger,format,...) \
     ester_log((&logger), \
               ESTER_ERROR, \
               ESTER_FILE, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOGM_WARN(logger,format,...) \
     ester_log((&logger), \
               ESTER_WARN, \
               ESTER_ALL, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOGM_INFO(logger,format,...) \
     ester_log((&logger), \
               ESTER_INFO, \
               ESTER_ALL, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOGM_ERR(logger,format,...) \
     ester_log((&logger), \
               ESTER_ERROR, \
               ESTER_ALL, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_ABORT(logger,format,...) \
     do \
     { \
         ester_log((&logger), \
               ESTER_ERROR, \
               ESTER_ALL, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__); \
        abort(); \
     }while(0)

#endif
