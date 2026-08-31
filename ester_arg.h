#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define ARG(x)                                            \
    _Generic((x),                                         \
        signed char:        arg_from_int,                 \
        short:              arg_from_int,                 \
        int:                arg_from_int,                 \
        long:               arg_from_int,                 \
        long long:          arg_from_int,                 \
        unsigned char:      arg_from_uint,                \
        unsigned short:     arg_from_uint,                \
        unsigned int:       arg_from_uint,                \
        unsigned long:      arg_from_uint,                \
        unsigned long long: arg_from_uint,                \
        _Bool:              arg_from_bool,                \
        float:              arg_from_float,               \
        double:             arg_from_double,              \
        long double:        arg_from_ldouble,             \
        char:               arg_from_char,                \
        char *:             arg_from_string,              \
        const char *:       arg_from_string,              \
        void *:             arg_from_pointer,             \
        const void *:       arg_from_pointer,             \
        default:            arg_from_pointer              \
    )(x)

#define ARG_1(a) \
    ARG(a)

#define ARG_2(a, b) \
    ARG(a), ARG(b)

#define ARG_3(a, b, c) \
    ARG(a), ARG(b), ARG(c)

#define ARG_4(a, b, c, d) \
    ARG(a), ARG(b), ARG(c), ARG(d)

#define ARG_5(a, b, c, d, e) \
    ARG(a), ARG(b), ARG(c), ARG(d), ARG(e)

#define ARG_6(a, b, c, d, e, f) \
    ARG(a), ARG(b), ARG(c), ARG(d), ARG(e), ARG(f)

#define ARG_7(a, b, c, d, e, f, g) \
    ARG(a), ARG(b), ARG(c), ARG(d), ARG(e), ARG(f), ARG(g)

#define ARG_8(a, b, c, d, e, f, g, h) \
    ARG(a), ARG(b), ARG(c), ARG(d), ARG(e), ARG(f), ARG(g), ARG(h)

#define ARG_9(a, b, c, d, e, f, g, h, i) \
    ARG(a), ARG(b), ARG(c), ARG(d), ARG(e), ARG(f), ARG(g), ARG(h), ARG(i)

#define ARG_10(a, b, c, d, e, f, g, h, i, j) \
    ARG(a), ARG(b), ARG(c), ARG(d), ARG(e), ARG(f), ARG(g), ARG(h), ARG(i), \
ARG(j)

#define GET_ARG_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME

#define MAP_ARG(...) \
    GET_ARG_MACRO(__VA_ARGS__, \
                  ARG_10, ARG_9, ARG_8, ARG_7, ARG_6, \
                  ARG_5, ARG_4, ARG_3, ARG_2, ARG_1) \
    (__VA_ARGS__)

typedef enum
{
    ARG_INT,
    ARG_UINT,
    ARG_FLOAT,
    ARG_DOUBLE,
    ARG_LDOUBLE,
    ARG_CHAR,
    ARG_BOOL,
    ARG_STRING,
    ARG_POINTER
} ester_arg_type_t;

typedef struct
{
    ester_arg_type_t type;
    const char *name;

    union
    {
        int64_t i;
        uint64_t u;
        float f;
        double d;
        long double ld;
        char c;
        bool b;
        const char *s;
        const void *p;
    };
} ester_arg_t;

static inline ester_arg_t arg_from_int(int64_t x)
{
    return (ester_arg_t){ .type = ARG_INT,   .i = x };
}

static inline ester_arg_t arg_from_uint(uint64_t x)
{
    return (ester_arg_t){ .type = ARG_UINT,  .u = x };
}

static inline ester_arg_t arg_from_float(float x)
{
    return (ester_arg_t){ .type = ARG_FLOAT, .f = x };
}

static inline ester_arg_t arg_from_double(double x)
{
    return (ester_arg_t){ .type = ARG_DOUBLE,.d = x };
}

static inline ester_arg_t arg_from_ldouble(long double x)
{
    return (ester_arg_t){ .type = ARG_LDOUBLE, .ld = x };
}

static inline ester_arg_t arg_from_char(char x)
{
    return (ester_arg_t){ .type = ARG_CHAR,  .c = x };
}

static inline ester_arg_t arg_from_bool(bool x)
{
    return (ester_arg_t){ .type = ARG_BOOL,  .b = x };
}

static inline ester_arg_t arg_from_string(const char *x)
{
    return (ester_arg_t){ .type = ARG_STRING, .s = x };
}

static inline ester_arg_t arg_from_pointer(const void *x)
{
    return (ester_arg_t){ .type = ARG_POINTER, .p = x };
}
