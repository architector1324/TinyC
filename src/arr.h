#ifndef ARR
#define ARR

#include <stdio.h>
#include <stdlib.h>

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
slc(type) _cat(slc(type), _from)(const type* data, size_t size) {\
    return (slc(type)){data, size};\
}\
slc_mut(type) _cat(slc_mut(type), _from)(type* data, size_t size) {\
    return (slc_mut(type)){data, size};\
}

// array
#define arr(type, size) _cat(_cat(_arr_, type), _cat(_, size))
#define arr_init(type, size) _cat(arr(type, size), _init)

#define arr_set(a, i, e) a.set(&a, i, e)
#define arr_at(a, i) a.at(&a, i)

#define ARRAY(type, _size)\
typedef struct _cat(_, arr(type, _size)) {\
    type data[_size];\
    slc(type) (*slice)(const struct _cat(_, arr(type, _size))*);\
    slc_mut(type) (*slice_mut)(struct _cat(_, arr(type, _size))*);\
    void (*set)(struct _cat(_, arr(type, _size))*, size_t, type);\
    type (*at)(const struct _cat(_, arr(type, _size))*, size_t);\
} arr(type, _size);\
slc(type) _cat(arr(type, _size), _slice)(const arr(type, _size)* a) {\
    return (slc(type)){\
        .data = a->data,\
        .size = _size,\
    };\
}\
slc_mut(type) _cat(arr(type, _size), _slice_mut)(arr(type, _size)* a) {\
    return (slc_mut(type)){\
        .data = a->data,\
        .size = _size,\
    };\
}\
void _cat(arr(type, _size), _set)(arr(type, _size)* a, size_t i, type e){\
    if(i >= _size) {\
        fprintf(stderr, "arr:set: index out of bounds!\n");\
        abort();\
    }\
    a->data[i] = e;\
}\
type _cat(arr(type, _size), _at)(const arr(type, _size)* a, size_t i){\
    if(i >= _size) {\
        fprintf(stderr, "arr:at: index out of bounds!\n");\
        abort();\
    }\
    return a->data[i];\
}\
arr(type, _size) arr_init(type, _size)(){\
    return (arr(type, _size)) {\
        .slice = _cat(arr(type, _size), _slice),\
        .slice_mut = _cat(arr(type, _size), _slice_mut),\
        .set = _cat(arr(type, _size), _set),\
        .at = _cat(arr(type, _size), _at)\
    };\
}

#endif