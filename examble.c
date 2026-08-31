#include "ester.h"
#include <fcntl.h>

int main ()
{

    ester_logger_t logger;

    ester_init_logger(&logger,"logger" );

    int i = -42;
    unsigned int ui = 123456789U;
    size_t sz = 987654321ULL;
    float f = 3.14159f;
    double d = 2.718281828459045;
    char c = 'X';
    const char *str = "Ahmed";
    const void *ptr = (const void *)&i;

    // print with new line
    ESTER_LOGLN_INFO(
        logger,
        "INFO: int={} uint={} size={} float={} double={} char={} string={} ptr={}",
        i, ui, sz, f, d, c, str, ptr
    );

    // print
    ESTER_LOG_INFO(
        logger,
        "INFO: int={} uint={} size={} float={} double={} char={} string={} ptr={}",
        i, ui, sz, f, d, c, str, ptr
    );

}
