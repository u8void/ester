#include "ester.h"
#include <stdarg.h>

void ester_log (const ester_logger_t* logger,
                const ester_log_level_t level,
                const bool stream_is_file,
                const char* filename,
                const char* function,
                const int line,
                const char* format,
                ...)
{

    const char* logtag;

    switch (level)
    {
        case ESTER_INFO: logtag = "INFO";
        break;

        case ESTER_WARN: logtag = "WARN";
        break;

        case ESTER_ERROR: logtag = "ERROR";
        break;

        case ESTER_DEBUG: logtag = "DEBUG";
        break;
    }

    FILE* stream;

    if (stream_is_file) stream = fopen(logger->name,"a+");
    else stream = stdout;

    fprintf(stream," [%s] %s->%s:%d ",logtag,filename,function,line) ;

    va_list args;
    va_start(args, format);
    vfprintf(stream,format, args);
    fprintf(stream,"\n");
    fflush(stream);
    va_end(args);
}
