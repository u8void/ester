#include "ester.h"
#include <stdarg.h>

void ester_log (const ester_logger_t* logger,
                const ester_log_level_t level,
                const ester_stream_t stream,
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


    switch (stream)
    {
        case ESTER_STDOUT: ester_printer(stdout,
                                      logtag,
                                      filename,
                                      function,
                                      line,
                                      format);
        break;

        case ESTER_FILE: ester_printer(fopen(logger->name,"a+"),
                                    logtag,
                                    filename,
                                    function,
                                    line,
                                    format);
        break;

        case ESTER_ALL:
        {
            ester_printer(stdout,
                       logtag,
                       filename,
                       function,
                       line,
                       format);

            ester_printer(fopen(logger->name,"a+"),
                       logtag,
                       filename,
                       function,
                       line,
                       format);
        }
        break;
    }

}

void ester_printer(FILE* log_stream,
                const char* logtag,
                const char* filename,
                const char* function,
                const int line,
                const char* format,
                ...)
{
    fprintf(log_stream,"[%s] %s->%s:%d ",logtag,filename,function,line) ;
    va_list args;
    va_start(args, format);
    vfprintf(log_stream,format, args);
    fprintf(log_stream,"\n");
    fflush(log_stream);
    va_end(args);
}
