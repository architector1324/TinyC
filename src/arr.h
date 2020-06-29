#ifndef ARR
#define ARR

#include <stdio.h>
#include <stdlib.h>

// extra
#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y)

// array
#define arr(type, size) _cat(_cat(_arr_, size), _cat(_, size))
#define arr_init(type, size) _cat(arr(type, size), _init)

#define arr_set(a, i, e) a.set(&a, i, e)
#define arr_at(a, i) a.at(&a, i)

#define ARRAY(type, size)\
typedef struct _cat(_, arr(type, size)) {\
    type data[size];\
    void (*set)(struct _cat(_, arr(type, size))*, size_t, type);\
    type (*at)(const struct _cat(_, arr(type, size))*, size_t);\
} arr(type, size);\
void _cat(arr(type, size), _set)(arr(type, size)* a, size_t i, type e){\
    if(i >= size) {\
        fprintf(stderr, "arr:set: index out of bounds!\n");\
        abort();\
    }\
    a->data[i] = e;\
}\
type _cat(arr(type, size), _at)(const arr(type, size)* a, size_t i){\
    if(i >= size) {\
        fprintf(stderr, "arr:at: index out of bounds!\n");\
        abort();\
    }\
    return a->data[i];\
}\
arr(type, size) arr_init(type, size)(){\
    return (arr(type, size)) {\
        .set = _cat(arr(type, size), _set),\
        .at = _cat(arr(type, size), _at)\
    };\
}

#endif