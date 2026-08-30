#pragma once

#include <stddef.h>

#define ARG(x)                                                   \
    _Generic((x),                                                \
        int:          arg_from_int,                              \
        unsigned int: arg_from_uint,                             \
        float:        arg_from_float,                            \
        double:       arg_from_double,                           \
        char:         arg_from_char,                             \
        char *:       arg_from_string,                           \
        const char *: arg_from_string,                           \
        void *:       arg_from_pointer,                          \
        const void *: arg_from_pointer,                          \
        default:      arg_from_pointer                           \
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

#define TO_STRING(x) _Generic((x), \
    int: int_to_string,            \
    size_t: double_to_string,      \
    double: double_to_string,      \
    char: char_to_string,          \
    const void* : ptr_to_string,   \
    void* : ptr_to_string          \
)(x)

typedef enum
{
    ARG_INT,
    ARG_UINT,
    ARG_FLOAT,
    ARG_DOUBLE,
    ARG_CHAR,
    ARG_STRING,
    ARG_POINTER
} ester_arg_type_t;

typedef struct
{
    ester_arg_type_t type;

    union
    {
        int i;
        size_t u;
        float f;
        double d;
        char c;
        const char *s;
        const void *p;
    };
} ester_arg_t;

static inline ester_arg_t arg_from_int(int x)
{
    return (ester_arg_t)
    {
        .type = ARG_INT,
        .i = x
    };
}

static inline ester_arg_t arg_from_uint(size_t x)
{
    return (ester_arg_t)
    {
        .type = ARG_UINT,
        .u = x
    };
}

static inline ester_arg_t arg_from_float(float x)
{
    return (ester_arg_t)
    {
        .type = ARG_FLOAT,
        .f = x
    };
}

static inline ester_arg_t arg_from_double(double x)
{
    return (ester_arg_t)
    {
        .type = ARG_DOUBLE,
        .d = x
    };
}

static inline ester_arg_t arg_from_char(char x)
{
    return (ester_arg_t)
    {
        .type = ARG_CHAR,
        .c = x
    };
}

static inline ester_arg_t arg_from_string(const char *x)
{
    return (ester_arg_t)
    {
        .type = ARG_STRING,
        .s = x
    };
}

static inline ester_arg_t arg_from_pointer(const void *x)
{
    return (ester_arg_t)
    {
        .type = ARG_POINTER,
        .p = x
    };
}
