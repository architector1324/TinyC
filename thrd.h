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
#define thrd_call(name, args...) name(&(thrd_args(name)){args})

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

// sync
#define thrd_mtx(type) _cat(_thrd_mtx_, type)
#define thrd_mtx_init(type) _cat(thrd_mtx(type), _init)

#define thrd_mtx_lock(m) m.lock(&m)
#define thrd_mtx_unlock(m) m.unlock(&m)
#define thrd_mtx_free(m) m.free(&m)

#define MUTEX(type)\
typedef struct _cat(__thrd_mtx_, type) {\
    pthread_mutex_t mtx;\
    type val;\
    type* (*lock)(struct _cat(__thrd_mtx_, type)*);\
    void (*unlock)(struct _cat(__thrd_mtx_, type)*);\
    void (*free)(struct _cat(__thrd_mtx_, type)*);\
} thrd_mtx(type);\
type* _cat(thrd_mtx(type), _lock)(thrd_mtx(type)* mtx) {\
    pthread_mutex_lock(&mtx->mtx);\
    return &mtx->val;\
}\
void _cat(thrd_mtx(type), _unlock)(thrd_mtx(type)* mtx) {\
    pthread_mutex_unlock(&mtx->mtx);\
}\
void _cat(thrd_mtx(type), _free)(thrd_mtx(type)* mtx) {\
    pthread_mutex_destroy(&mtx->mtx);\
}\
thrd_mtx(type) _cat(thrd_mtx(type), _init)(type val) {\
    thrd_mtx(type) mtx = {\
        .val = val,\
        .lock = _cat(thrd_mtx(type), _lock),\
        .unlock = _cat(thrd_mtx(type), _unlock),\
        .free = _cat(thrd_mtx(type), _free)\
    };\
    pthread_mutex_init(&mtx.mtx, NULL);\
    return mtx;\
}


#define thrd_rwlck(type) _cat(_thrd_rwlck_, type)
#define thrd_rwlck_init(type) _cat(thrd_rwlck(type), _init)

#define thrd_rwlck_lock(m) m.lock(&m)
#define thrd_rwlck_rlock(m) m.rlock(&m)
#define thrd_rwlck_unlock(m) m.unlock(&m)
#define thrd_rwlck_free(m) m.free(&m)

#define RWLOCK(type)\
typedef struct _cat(__thrd_rwlck_, type) {\
    pthread_rwlock_t lck;\
    type val;\
    type* (*lock)(struct _cat(__thrd_rwlck_, type)*);\
    const type* (*rlock)(struct _cat(__thrd_rwlck_, type)*);\
    void (*unlock)(struct _cat(__thrd_rwlck_, type)*);\
    void (*free)(struct _cat(__thrd_rwlck_, type)*);\
} thrd_rwlck(type);\
type* _cat(thrd_rwlck(type), _lock)(thrd_rwlck(type)* lck){\
    pthread_rwlock_wrlock(&lck->lck);\
    return &lck->val;\
}\
const type* _cat(thrd_rwlck(type), _rlock)(thrd_rwlck(type)* lck){\
    pthread_rwlock_rdlock(&lck->lck);\
    return &lck->val;\
}\
void _cat(thrd_rwlck(type), _unlock)(thrd_rwlck(type)* lck){\
    pthread_rwlock_unlock(&lck->lck);\
}\
void _cat(thrd_rwlck(type), _free)(thrd_rwlck(type)* lck) {\
    pthread_rwlock_destroy(&lck->lck);\
}\
thrd_rwlck(type) _cat(thrd_rwlck(type), _init)(type val) {\
    thrd_rwlck(type) lck = {\
        .val = val,\
        .lock = _cat(thrd_rwlck(type), _lock),\
        .rlock = _cat(thrd_rwlck(type), _rlock),\
        .unlock = _cat(thrd_rwlck(type), _unlock),\
        .free = _cat(thrd_rwlck(type), _free)\
    };\
    pthread_rwlock_init(&lck.lck, NULL);\
    return lck;\
}

// chan

#endif