#ifndef VEC
#define VEC

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// settings
// #define VECTOR_DEF_STD
// #define MICRO_VECTOR_DEF_STD
// #define BIG_VECTOR_DEF_STD
#define MICRO_VECTOR_DEF_SIZE 100
#define VECTOR_REALLOC_FACTOR 1.6f

// extra
#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y)

// slice
#define slc(type) _cat(_slc_, type)
#define slc_mut(type) _cat(_slc_mut_, type)

#define slc_from(type) _cat(slc(type), _from)
#define slc_from_mut(type) _cat(slc_mut(type), _from)

#define to_slc(cnt) cnt.slice(&cnt)
#define to_slc_mut(cnt) cnt.slice_mut(&cnt)

#define SLICE(type)\
typedef struct _cat(_, slc(type)) {\
    const type* data;\
    size_t size;\
} slc(type);\
typedef struct _cat(_, slc_mut(type)) {\
    type* data;\
    size_t size;\
} slc_mut(type);\
slc(type) _cat(slc(type), _from)(const type* data, size_t from, size_t size) {\
    return (slc(type)){data + from, size};\
}\
slc_mut(type) _cat(slc_mut(type), _from)(type* data, size_t from, size_t size) {\
    return (slc_mut(type)){data + from, size};\
}

// vector
#define vec(type) _cat(_vec_, type)
#define vec_init(type) _cat(vec(type), _init)
#define vec_from(type) _cat(vec(type), _from)

#define vec_at(v, i) v.at(&v, i)
#define vec_push(v, e) v.push(&v, e)
#define vec_pop(v) v.pop(&v)
#define vec_cat(to, from) to.cat(&to, &from)
#define vec_reserve(v, count) v.reserve(&v, count)
#define vec_free(v) v.free(&v)

#define VECTOR(type)\
typedef struct _cat(_, vec(type)) {\
    type* data;\
    size_t size;\
    size_t cap;\
    slc(type) (*slice)(const struct _cat(_, vec(type))*);\
    slc_mut(type) (*slice_mut)(struct _cat(_, vec(type))*);\
    type (*at)(const struct _cat(_, vec(type))*, size_t);\
    void (*push)(struct _cat(_, vec(type))*, type);\
    type (*pop)(struct _cat(_, vec(type))*);\
    void (*reserve)(struct _cat(_, vec(type))*, size_t);\
    void (*cat)(struct _cat(_, vec(type))*, const struct _cat(_, vec(type))*);\
    void (*free)(struct _cat(_, vec(type))*);\
} vec(type);\
slc(type) _cat(vec(type), _slice)(const vec(type)* v) {\
    return (slc(type)){\
        .data = v->data,\
        .size = v->size,\
    };\
}\
slc_mut(type) _cat(vec(type), _slice_mut)(vec(type)* v) {\
    return (slc_mut(type)){\
        .data = v->data,\
        .size = v->size,\
    };\
}\
type _cat(vec(type), _at)(const vec(type)* v, size_t i) {\
    if(i >= v->size) {\
        fprintf(stderr, "vec:at: index out of bounds!\n");\
        abort();\
    }\
    return v->data[i];\
}\
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
void _cat(vec(type), _cat)(vec(type)* to, const vec(type)* from){\
    for(size_t i = 0; i < from->size; i++) to->push(to, from->at(from, i));\
}\
void _cat(vec(type), _free)(vec(type)* v) {\
    v->size = 0;\
    v->cap = 0;\
    free(v->data);\
    v->slice = NULL;\
    v->slice_mut = NULL;\
    v->data = NULL;\
    v->at = NULL;\
    v->push = NULL;\
    v->pop = NULL;\
    v->cat = NULL;\
    v->reserve = NULL;\
    v->free = NULL;\
}\
vec(type) _cat(vec(type), _init)() {\
    return (vec(type)){\
        .data = malloc(2 * sizeof(type)),\
        .size = 0,\
        .cap = 2,\
        .slice = _cat(vec(type), _slice),\
        .slice_mut = _cat(vec(type), _slice_mut),\
        .at = _cat(vec(type), _at),\
        .push = _cat(vec(type), _push),\
        .pop = _cat(vec(type), _pop),\
        .cat = _cat(vec(type), _cat),\
        .reserve = _cat(vec(type), _reserve),\
        .free = _cat(vec(type), _free)\
    };\
}\
vec(type) _cat(vec(type), _from)(slc(type) a) {\
    vec(type) res = vec_init(type)();\
    memcpy(res.data, a.data, sizeof(type) * a.size);\
    res.size = a.size;\
    return res;\
}

// micro vector
#define vec_micro(type) _cat(_vec_micro_, type)
#define vec_micro_init(type) _cat(vec_micro(type), _init)
#define vec_micro_from(type) _cat(vec_micro(type), _from)

#define MICRO_VECTOR_CUSTOM(type, _size)\
typedef struct _cat(__vec_micro_, type) {\
    type data[_size];\
    size_t size;\
    slc(type) (*slice)(const struct _cat(_, vec_micro(type))*);\
    slc_mut(type) (*slice_mut)(struct _cat(_, vec_micro(type))*);\
    type (*at)(const struct _cat(_, vec_micro(type))*, size_t);\
    void (*push)(struct _cat(_, vec_micro(type))*, type);\
    type (*pop)(struct _cat(_, vec_micro(type))*);\
    void (*cat)(struct _cat(_, vec_micro(type))*, const struct _cat(_, vec_micro(type))*);\
} vec_micro(type);\
slc(type) _cat(vec_micro(type), _slice)(const vec_micro(type)* v) {\
    return (slc(type)){\
        .data = v->data,\
        .size = v->size,\
    };\
}\
slc_mut(type) _cat(vec_micro(type), _slice_mut)(vec_micro(type)* v) {\
    return (slc_mut(type)){\
        .data = v->data,\
        .size = v->size,\
    };\
}\
type _cat(vec_micro(type), _at)(const vec_micro(type)* v, size_t i) {\
    if(i >= v->size) {\
        fprintf(stderr, "vec_micro:at: index out of bounds!\n");\
        abort();\
    }\
    return v->data[i];\
}\
void _cat(vec_micro(type), _push)(vec_micro(type)* v, type e) {\
    if(v->size == _size) {\
        fprintf(stderr, "vec_micro:push: full vector!\n");\
        abort();\
    }\
    v->data[v->size++] = e;\
}\
type _cat(vec_micro(type), _pop)(vec_micro(type)* v) {\
    if(v->size == 0) {\
        fprintf(stderr, "vec_micro:pop: empty vector!\n");\
        abort();\
    }\
    return v->data[--v->size];\
}\
void _cat(vec_micro(type), _cat)(vec_micro(type)* to, const vec_micro(type)* from){\
    for(size_t i = 0; i < from->size; i++) to->push(to, from->at(from, i));\
}\
vec_micro(type) _cat(vec_micro(type), _init)() {\
    return (vec_micro(type)) {\
        .size = 0,\
        .slice = _cat(vec_micro(type), _slice),\
        .slice_mut = _cat(vec_micro(type), _slice_mut),\
        .at = _cat(vec_micro(type), _at),\
        .push = _cat(vec_micro(type), _push),\
        .pop = _cat(vec_micro(type), _pop),\
        .cat = _cat(vec_micro(type), _cat),\
    };\
}\
vec_micro(type) _cat(vec_micro(type), _from)(slc(type) a) {\
    vec_micro(type) res = vec_micro_init(type)();\
    memcpy(res.data, a.data, sizeof(type) * a.size);\
    res.size = a.size;\
    return res;\
}

#define MICRO_VECTOR(type) MICRO_VECTOR_CUSTOM(type, MICRO_VECTOR_DEF_SIZE)

// big vector
#define vec_big(type) _cat(_vec_big_, type)
#define vec_big_init(type) _cat(vec_big(type), _init)
#define vec_big_from(type) _cat(vec_big(type), _from)

#define BIG_VECTOR(type)\
typedef struct _cat(_, vec_big(type)) {\
    FILE* _data;\
    size_t size;\
    type (*at)(const struct _cat(_, vec_big(type))*, size_t);\
    void (*push)(struct _cat(_, vec_big(type))*, type);\
    type (*pop)(struct _cat(_, vec_big(type))*);\
    void (*cat)(struct _cat(_, vec_big(type))*, const struct _cat(_, vec_big(type))*);\
    void (*free)(struct _cat(_, vec_big(type))*);\
} vec_big(type);\
type _cat(vec_big(type), _at)(const vec_big(type)* v, size_t i) {\
    type res;\
    if(i >= v->size) {\
        fprintf(stderr, "vec_big:at: index out of bounds!\n");\
        abort();\
    }\
    long pos = ftell(v->_data);\
    if(fseek(v->_data, i * sizeof(type), SEEK_SET)) {\
        fprintf(stderr, "vec_big:at: invalid read!\n");\
        abort();\
    }\
    if(fread(&res, sizeof(type), 1, v->_data) != 1) {\
        fprintf(stderr, "vec_big:at: invalid read!\n");\
        abort();\
    }\
    if(fseek(v->_data, (size_t)pos, SEEK_SET)) {\
        fprintf(stderr, "vec_big:at: invalid read!\n");\
        abort();\
    }\
    return res;\
}\
void _cat(vec_big(type), _push)(vec_big(type)* v, type e) {\
    v->size++;\
    if(fwrite(&e, sizeof(type), 1, v->_data) != 1) {\
        fprintf(stderr, "vec_big:push: invalid write!\n");\
        abort();\
    }\
}\
type _cat(vec_big(type), _pop)(vec_big(type)* v) {\
    type res;\
    if(v->size == 0) {\
        fprintf(stderr, "vec_big:pop: empty vector!\n");\
        abort();\
    }\
    v->size--;\
    if(fseek(v->_data, -sizeof(type), SEEK_CUR)) {\
        fprintf(stderr, "vec_big:pop: invalid read!\n");\
        abort();\
    }\
    if(fread(&res, sizeof(type), 1, v->_data) != 1) {\
        fprintf(stderr, "vec_big:pop: invalid read!\n");\
        abort();\
    }\
    if(fseek(v->_data, -sizeof(type), SEEK_CUR)) {\
        fprintf(stderr, "vec_big:pop: invalid read!\n");\
        abort();\
    }\
    return res;\
}\
void _cat(vec_big(type), _cat)(vec_big(type)* to, const vec_big(type)* from){\
    for(size_t i = 0; i < from->size; i++) to->push(to, from->at(from, i));\
}\
void _cat(vec_big(type), _free)(vec_big(type)* v){\
    v->size = 0;\
    fclose(v->_data);\
    v->_data = NULL;\
    v->at = NULL;\
    v->push = NULL;\
    v->pop = NULL;\
    v->cat = NULL;\
    v->free = NULL;\
}\
vec_big(type) _cat(vec_big(type), _init)(const char* name) {\
    FILE* f = fopen(name, "a+b");\
    if(fseek(f, 0, SEEK_END)) {\
        fprintf(stderr, "vec_big:init: invalid read!\n");\
        abort();\
    }\
    long size = ftell(f);\
    if(size < 0 || size % sizeof(type) > 0) {\
        fprintf(stderr, "vec_big:init: invalid size!\n");\
        abort();\
    }\
    return (vec_big(type)){\
        ._data = f,\
        .size = (size_t)size/sizeof(type),\
        .at = _cat(vec_big(type), _at),\
        .push = _cat(vec_big(type), _push),\
        .pop = _cat(vec_big(type), _pop),\
        .cat = _cat(vec_big(type), _cat),\
        .free = _cat(vec_big(type), _free)\
    };\
}\
vec_big(type) _cat(vec_big(type), _from)(const char* name, slc(type) a) {\
    vec_big(type) res = vec_big_init(type)(name);\
    for(size_t i = 0; i < a.size; i++) vec_push(res, a.data[i]);\
    return res;\
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