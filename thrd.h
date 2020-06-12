#ifndef THRD
#define THRD

#include <pthread.h>
#include <stdlib.h>

// extra
#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y)

#define _foreach1(x) x;
#define _foreach2(x, ...) x; _foreach1(__VA_ARGS__)
#define _foreach3(x, ...) x; _foreach2(__VA_ARGS__)
#define _foreach4(x, ...) x; _foreach3(__VA_ARGS__)
#define _foreach5(x, ...) x; _foreach4(__VA_ARGS__)
#define _foreach6(x, ...) x; _foreach5(__VA_ARGS__)
#define _foreach7(x, ...) x; _foreach6(__VA_ARGS__)
#define _foreach8(x, ...) x; _foreach7(__VA_ARGS__)

#define _foreach_counter(_1, _2, _3, _4, _5, _6, _7, _8, x, ...) x
#define _foreach(...) _foreach_counter(__VA_ARGS__, _foreach8, _foreach7, _foreach6, _foreach5, _foreach4, _foreach3, _foreach2, _foreach1)(__VA_ARGS__)

// base

#define thrd(name) _cat(_thrd_, name)
#define thrd_args(name) _cat(_thrd_args_, name)
#define thrd_init(name) _cat(thrd(name), _init)

#define thrd_create(name, th, args...) _cat(thrd(name), _create)(&th, (thrd_args(name)){args})
#define thrd_join(th) th.join(&th)

#define THREAD(type, name, args...)\
typedef struct _cat(__thrd_args_, name) {\
    _foreach(args)\
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