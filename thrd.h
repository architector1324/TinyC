#ifndef THRD
#define THRD

#include <pthread.h>
#include <stdlib.h>

// extra
#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y)

#define thrd(name) _cat(_thrd_, name)
#define thrd_args(name) _cat(_thrd_args_, name)
#define thrd_init(name) _cat(thrd(name), _init)

#define thrd_create(name, th, args...) _cat(thrd(name), _create)(&th, (thrd_args(name)){args})
#define thrd_join(th) th.join(&th)

#define THREAD(type, name, args...)\
typedef struct _cat(__thrd_args_, name) {\
    args;\
} thrd_args(name);\
typedef struct _cat(__thrd_, name) {\
    pthread_t th;\
    thrd_args(name) arg;\
    type res;\
    type (*join)(struct _cat(__thrd_, name)*);\
} thrd(name);\
type name(const thrd_args(name)* arg);\
void* _cat(thrd(name), _bootstrap)(void* raw) {\
    thrd(name)* th = (thrd(name)*)(raw);\
    th->res = name(&th->arg);\
    return th;\
}\
type _cat(thrd(name), _join)(thrd(name)* th){\
    pthread_join(th->th, NULL);\
    return th->res;\
}\
void _cat(thrd(name), _create)(thrd(name)* th, thrd_args(name) arg){\
    th->arg = arg;\
    th->join = _cat(thrd(name), _join);\
    pthread_create(&th->th, NULL, _cat(thrd(name), _bootstrap), th);\
}\
type name(const thrd_args(name)* arg)

#endif