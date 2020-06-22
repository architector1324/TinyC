#ifndef MICRO_VEC
#define MICRO_VEC

#include <stdlib.h>

// settings
// #define MICRO_VECTOR_DEF_STD
#define MICRO_VECTOR_SIZE 100

// extra
#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y) 

// base
#define mvec(type) _cat(_mvec_, type)
#define mvec_init(type) _cat(mvec(type), _init)

#define mvec_push(v, e) v.push(&v, e)
#define mvec_pop(v) v.pop(&v)

#define MICRO_VECTOR(type)\
typedef struct _cat(__mvec_, type) {\
    type data[MICRO_VECTOR_SIZE];\
    size_t size;\
    void (*push)(struct _cat(_, mvec(type))*, type);\
    type (*pop)(struct _cat(_, mvec(type))*);\
} mvec(type);\
void _cat(mvec(type), _push)(mvec(type)* v, type e) {\
    if(v->size == MICRO_VECTOR_SIZE) {\
        fprintf(stderr, "mvec:push: full vector!\n");\
        abort();\
    }\
    v->data[v->size++] = e;\
}\
type _cat(mvec(type), _pop)(mvec(type)* v) {\
    if(v->size == 0) {\
        fprintf(stderr, "mvec:pop: empty vector!\n");\
        abort();\
    }\
    return v->data[--v->size];\
}\
mvec(type) _cat(mvec(type), _init)() {\
    return (mvec(type)) {\
        .size = 0,\
        .push = _cat(mvec(type), _push),\
        .pop = _cat(mvec(type), _pop)\
    };\
}

// defined vectors for std
#ifdef MICRO_VECTOR_DEF_STD

#include <stdint.h>

MICRO_VECTOR(char)
MICRO_VECTOR(int)
MICRO_VECTOR(float)
MICRO_VECTOR(double)
MICRO_VECTOR(size_t)

MICRO_VECTOR(int8_t)
MICRO_VECTOR(int16_t)
MICRO_VECTOR(int32_t)
MICRO_VECTOR(int64_t)
MICRO_VECTOR(uint8_t)
MICRO_VECTOR(uint16_t)
MICRO_VECTOR(uint32_t)
MICRO_VECTOR(uint64_t)

#endif

#endif