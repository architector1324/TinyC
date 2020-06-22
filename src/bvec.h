#ifndef BIG_VEC
#define BIG_VEC

#include <stdlib.h>

// settings
// #define BIG_VECTOR_DEF_STD

// extra
#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y) 

// base
#define bvec(type) _cat(_bvec_, type)
#define bvec_init(type) _cat(bvec(type), _init)

#define bvec_at(v, i) v.at(&v, i)
#define bvec_push(v, e) v.push(&v, e)
#define bvec_pop(v) v.pop(&v)
#define bvec_free(v) v.free(&v)

#define BIG_VECTOR(type)\
typedef struct _cat(_, bvec(type)) {\
    FILE* _data;\
    size_t size;\
    type (*at)(struct _cat(_, bvec(type))*, size_t);\
    void (*push)(struct _cat(_, bvec(type))*, type);\
    type (*pop)(struct _cat(_, bvec(type))*);\
    void (*free)(struct _cat(_, bvec(type))*);\
} bvec(type);\
type _cat(bvec(type), _at)(bvec(type)* v, size_t i) {\
    type res;\
    if(i >= v->size) {\
        fprintf(stderr, "bvec:at: index out of bounds!\n");\
        abort();\
    }\
    long pos = ftell(v->_data);\
    if(fseek(v->_data, i * sizeof(type), SEEK_SET)) {\
        fprintf(stderr, "bvec:at: invalid read!\n");\
        abort();\
    }\
    if(fread(&res, sizeof(type), 1, v->_data) != 1) {\
        fprintf(stderr, "bvec:at: invalid read!\n");\
        abort();\
    }\
    if(fseek(v->_data, (size_t)pos, SEEK_SET)) {\
        fprintf(stderr, "bvec:at: invalid read!\n");\
        abort();\
    }\
    return res;\
}\
void _cat(bvec(type), _push)(bvec(type)* v, type e) {\
    v->size++;\
    if(fwrite(&e, sizeof(type), 1, v->_data) != 1) {\
        fprintf(stderr, "bvec:push: invalid write!\n");\
        abort();\
    }\
}\
type _cat(bvec(type), _pop)(bvec(type)* v) {\
    type res;\
    if(v->size == 0) {\
        fprintf(stderr, "bvec:pop: empty vector!\n");\
        abort();\
    }\
    v->size--;\
    if(fseek(v->_data, -sizeof(type), SEEK_CUR)) {\
        fprintf(stderr, "bvec:pop: invalid read!\n");\
        abort();\
    }\
    if(fread(&res, sizeof(type), 1, v->_data) != 1) {\
        fprintf(stderr, "bvec:pop: invalid read!\n");\
        abort();\
    }\
    if(fseek(v->_data, -sizeof(type), SEEK_CUR)) {\
        fprintf(stderr, "bvec:pop: invalid read!\n");\
        abort();\
    }\
    return res;\
}\
void _cat(bvec(type), _free)(bvec(type)* v){\
    v->size = 0;\
    fclose(v->_data);\
    v->_data = NULL;\
    v->at = NULL;\
    v->push = NULL;\
    v->pop = NULL;\
    v->free = NULL;\
}\
bvec(type) _cat(bvec(type), _init)(const char* name) {\
    FILE* f = fopen(name, "a+b");\
    if(fseek(f, 0, SEEK_END)) {\
        fprintf(stderr, "bvec:init: invalid read!\n");\
        abort();\
    }\
    long size = ftell(f);\
    if(size < 0 || size % sizeof(type) > 0) {\
        fprintf(stderr, "bvec:init: invalid size!\n");\
        abort();\
    }\
    return (bvec(type)){\
        ._data = f,\
        .size = (size_t)size/sizeof(type),\
        .at = _cat(bvec(type), _at),\
        .push = _cat(bvec(type), _push),\
        .pop = _cat(bvec(type), _pop),\
        .free = _cat(bvec(type), _free)\
    };\
}


// defined vectors for std
#ifdef BIG_VECTOR_DEF_STD

#include <stdint.h>

BIG_VECTOR(char)
BIG_VECTOR(int)
BIG_VECTOR(float)
BIG_VECTOR(double)
BIG_VECTOR(size_t)

BIG_VECTOR(int8_t)
BIG_VECTOR(int16_t)
BIG_VECTOR(int32_t)
BIG_VECTOR(int64_t)
BIG_VECTOR(uint8_t)
BIG_VECTOR(uint16_t)
BIG_VECTOR(uint32_t)
BIG_VECTOR(uint64_t)

#endif

#endif