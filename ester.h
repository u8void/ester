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

void ester_log (const ester_logger_t* logger,
                const ester_log_level_t level,
                const bool stream_is_file,
                const char* filename,
                const char* function,
                const int line,
                const char* format,
                ...);

#define ESTER_LOG_WARN(logger,format,...) \
     ester_log((&logger), \
               ESTER_WARN, \
               false, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOG_INFO(logger,format,...) \
     ester_log((&logger), \
               ESTER_INFO, \
               false, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOG_ERR(logger,format,...) \
     ester_log((&logger), \
               ESTER_ERROR, \
               false, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOGF_WARN(logger,format,...) \
     ester_log((&logger), \
               ESTER_WARN, \
               true, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOGF_INFO(logger,format,...) \
     ester_log((&logger), \
               ESTER_INFO, \
               true, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)

#define ESTER_LOGF_ERR(logger,format,...) \
     ester_log((&logger), \
               ESTER_ERROR, \
               true, \
               (const char*)__FILE_NAME__, \
               (const char*)__FUNCTION__, \
               (const int)__LINE__, \
               (const char*)format, \
               ##__VA_ARGS__)
