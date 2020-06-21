#ifndef VEC
#define VEC

#include <stdlib.h>

// settings
// #define VECTOR_DEF_STD
#define VECTOR_REALLOC_FACTOR 1.6f

// extra
#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y) 

// base
#define vec(type) _cat(_vec_, type)
#define vec_init(type) _cat(vec(type), _init)

#define vec_push(v, e) v.push(&v, e)
#define vec_pop(v) v.pop(&v)
#define vec_reserve(v, count) v.reserve(&v, count)
#define vec_free(v) v.free(&v)

#define VECTOR(type)\
typedef struct _cat(_, vec(type)) {\
    type* data;\
    size_t size;\
    size_t cap;\
    void (*push)(struct _cat(_, vec(type))*, type);\
    type (*pop)(struct _cat(_, vec(type))*);\
    void (*reserve)(struct _cat(_, vec(type))*, size_t);\
    void (*free)(struct _cat(_, vec(type))*);\
} vec(type);\
void _cat(vec(type), _push)(vec(type)* v, type e) {\
    if(v->size == v->cap) {\
        v->cap *= VECTOR_REALLOC_FACTOR;\
        v->data = (type*)realloc(v->data, v->cap * sizeof(type));\
    }\
    v->data[v->size++] = e;\
}\
type _cat(vec(type), _pop)(vec(type)* v) {\
    if(v->size == 0) {\
        fprintf(stderr, "vec:pop: empty vector!\n");\
        abort();\
    }\
    if(v->size * VECTOR_REALLOC_FACTOR < v->cap + 1) {\
        v->cap = v->size;\
        v->data = (type*)realloc(v->data, v->cap * sizeof(type));\
    }\
    return v->data[--v->size];\
}\
void _cat(vec(type), _reserve)(vec(type)* v, size_t count) {\
    if(count < v->size) v->cap = v->size;\
    else if(count != v->cap) {\
        v->cap = count;\
        v->data = (type*)realloc(v->data, v->cap * sizeof(type));\
    }\
}\
void _cat(vec(type), _free)(vec(type)* v) {\
    v->size = 0;\
    v->cap = 0;\
    free(v->data);\
    v->data = NULL;\
    v->push = NULL;\
    v->pop = NULL;\
    v->reserve = NULL;\
    v->free = NULL;\
}\
vec(type) _cat(vec(type), _init)() {\
    return (vec(type)){\
        .data = malloc(2 * sizeof(type)),\
        .size = 0,\
        .cap = 2,\
        .push = _cat(vec(type), _push),\
        .pop = _cat(vec(type), _pop),\
        .reserve = _cat(vec(type), _reserve),\
        .free = _cat(vec(type), _free)\
    };\
}

// defined vectors for std
#ifdef VECTOR_DEF_STD

#include <stdint.h>

VECTOR(char)
VECTOR(int)
VECTOR(float)
VECTOR(double)
VECTOR(size_t)

VECTOR(int8_t)
VECTOR(int16_t)
VECTOR(int32_t)
VECTOR(int64_t)
VECTOR(uint8_t)
VECTOR(uint16_t)
VECTOR(uint32_t)
VECTOR(uint64_t)

#endif


#endif