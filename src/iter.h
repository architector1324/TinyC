#ifndef ITER
#define ITER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tup.h"

// extra
#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y)


// option
#define some(type, e) (tup(type, bool)){e, true}
#define none(type) (tup(type, bool)){.t1 = false} 


//iterator
#define iter(type) _cat(_iter_, type)
#define iter_init(type) _cat(iter(type), _init)

#define iter_next(it) it.next(&it)

#define ITERATOR(type)\
TUPLE(type, bool)\
typedef struct _cat(_, iter(type)) {\
    type last;\
    bool end;\
    tup(type, bool) (*next)(struct _cat(_, iter(type))*);\
} iter(type);\
tup(type, bool) _cat(iter(type), _next)(iter(type)* it);\
tup(type, bool) _cat(iter(type), _next_wrapper)(iter(type)* it) {\
    if(it->end) {\
        fprintf(stderr, "iter:%s:next: out of bounds!\n", #type);\
        abort();\
    }\
    tup(type, bool) res = _cat(iter(type), _next)(it);\
    if(!res.t1) it->end = true;\
    return res;\
}\
iter(type) iter_init(type)(type e) {\
    return (iter(type)){\
        .last = e,\
        .next = _cat(iter(type), _next_wrapper)\
    };\
}\
tup(type, bool) _cat(iter(type), _next)(iter(type)* it)

#define iter_foreach(type, it, v, body) {\
    tup(type, bool) tmp;\
    type v;\
    while(!it.end) {\
        v = it.last;\
        body;\
        tmp = iter_next(it);\
    }\
}

#endif