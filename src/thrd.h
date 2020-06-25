#ifndef THRD
#define THRD

#include <stdbool.h>
#include <pthread.h>

#include "vec.h"

// extra
// ... -> count(...) [max 6]
#define _foreach_counter(_0, _1, _2, _3, _4, _5, _6, x, ...) x
#define _foreach_chooser(...) _foreach_counter(__VA_ARGS__, 6, 5, 4, 3, 2, 1, 0)


// ... -> 2 * count(...) [max 6]
#define _foreach2_counter(\
    _0_0, _0_1,\
    _1_0, _1_1,\
    _2_0, _2_1,\
    _3_0, _3_1,\
    _4_0, _4_1,\
    _5_0, _5_1,\
    _6_0, _6_1,\
    x, ...) x
#define _foreach2_chooser(...) _foreach2_counter(__VA_ARGS__, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0)

// type declarators
#define __type_decl0(x, y, ...) x y;
#define __type_decl1(x, y, ...) x y; __type_decl0(__VA_ARGS__)
#define __type_decl2(x, y, ...) x y; __type_decl1(__VA_ARGS__)
#define __type_decl3(x, y, ...) x y; __type_decl2(__VA_ARGS__)
#define __type_decl4(x, y, ...) x y; __type_decl3(__VA_ARGS__)
#define __type_decl5(x, y, ...) x y; __type_decl4(__VA_ARGS__)
#define __type_decl6(x, y, ...) x y; __type_decl5(__VA_ARGS__)

#define _type_decl(...) _cat(__type_decl, _foreach2_chooser(__VA_ARGS__))(__VA_ARGS__)

#define __type_decl_comma0(x, y, ...) x y
#define __type_decl_comma1(x, y, ...) x y, __type_decl_comma0(__VA_ARGS__)
#define __type_decl_comma2(x, y, ...) x y, __type_decl_comma1(__VA_ARGS__)
#define __type_decl_comma3(x, y, ...) x y, __type_decl_comma2(__VA_ARGS__)
#define __type_decl_comma4(x, y, ...) x y, __type_decl_comma3(__VA_ARGS__)
#define __type_decl_comma5(x, y, ...) x y, __type_decl_comma4(__VA_ARGS__)
#define __type_decl_comma6(x, y, ...) x y, __type_decl_comma5(__VA_ARGS__)

#define _type_decl_comma(...) _cat(__type_decl_comma, _foreach2_chooser(__VA_ARGS__))(__VA_ARGS__)

// argument chooser
#define __arg_chooser0(pre, x, y, ...) pre y
#define __arg_chooser1(pre, x, y, ...) pre y, __arg_chooser0(pre, __VA_ARGS__)
#define __arg_chooser2(pre, x, y, ...) pre y, __arg_chooser1(pre, __VA_ARGS__)
#define __arg_chooser3(pre, x, y, ...) pre y, __arg_chooser2(pre, __VA_ARGS__)
#define __arg_chooser4(pre, x, y, ...) pre y, __arg_chooser3(pre, __VA_ARGS__)
#define __arg_chooser5(pre, x, y, ...) pre y, __arg_chooser4(pre, __VA_ARGS__)
#define __arg_chooser6(pre, x, y, ...) pre y, __arg_chooser5(pre, __VA_ARGS__)

#define _arg_chooser(pre, ...) _cat(__arg_chooser, _foreach2_chooser(__VA_ARGS__))(pre, __VA_ARGS__)


// base
#define thrd(name) _cat(_thrd_, name)
#define thrd_args(name) _cat(_thrd_args_, name)
#define thrd_init(name) _cat(thrd(name), _init)
#define thrd_create(name, th, f, args...) _cat(thrd(name), _create)(&th, f, (thrd_args(name)){args})
#define thrd_call(name, args...) name(&(thrd_args(name)){args})

#define thrd_join(th) th.join(&th)

#define THREAD(type, name, args...)\
typedef struct _cat(__thrd_args_, name) {\
    _type_decl(args)\
} thrd_args(name);\
typedef struct _cat(__thrd_, name) {\
    pthread_t th;\
    thrd_args(name) arg;\
    type res;\
    bool run;\
    type (*f)(_type_decl_comma(args));\
    type (*join)(struct _cat(__thrd_, name)*);\
} thrd(name);\
void* _cat(thrd(name), _bootstrap)(void* raw) {\
    thrd(name)* th = (thrd(name)*)(raw);\
    th->res = th->f(_arg_chooser(th->arg., args));\
    th->run = false;\
    return th;\
}\
type _cat(thrd(name), _join)(thrd(name)* th){\
    pthread_join(th->th, NULL);\
    return th->res;\
}\
bool _cat(thrd(name), _create)(thrd(name)* th, type (*f)(_type_decl_comma(args)), thrd_args(name) arg){\
    if(!th->run) {\
        th->run = true;\
        th->arg = arg;\
        th->join = _cat(thrd(name), _join);\
        th->f = f;\
        pthread_create(&th->th, NULL, _cat(thrd(name), _bootstrap), th);\
        return true;\
    }\
    return false;\
}


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
#define thrd_chan(type) _cat(_thrd_chan_, type)
#define thrd_chan_init(type) _cat(thrd_chan(type), _init)

#define thrd_chan_snd(ch, val) ch.snd(&ch, val)
#define thrd_chan_recv(ch) ch.recv(&ch)
#define thrd_chan_free(ch) ch.free(&ch)

#define CHAN(type)\
MUTEX(type)\
typedef struct _cat(__thrd_chan_, type) {\
    thrd_mtx(type) mtx;\
    bool receiving;\
    bool sent;\
    pthread_cond_t _cond;\
    void (*snd)(struct _cat(__thrd_chan_, type)*, type);\
    type (*recv)(struct _cat(__thrd_chan_, type)*);\
    void (*free)(struct _cat(__thrd_chan_, type)*);\
} thrd_chan(type);\
void _cat(thrd_chan(type), _snd)(thrd_chan(type)* ch, type val) {\
    type* v = thrd_mtx_lock(ch->mtx);\
    while(!ch->receiving) pthread_cond_wait(&ch->_cond, &ch->mtx.mtx);\
    *v = val;\
    ch->sent = true;\
    ch->receiving = false;\
    pthread_cond_signal(&ch->_cond);\
    thrd_mtx_unlock(ch->mtx);\
}\
type _cat(thrd_chan(type), _recv)(thrd_chan(type)* ch) {\
    type* val = thrd_mtx_lock(ch->mtx);\
    ch->receiving = true;\
    pthread_cond_signal(&ch->_cond);\
    while(!ch->sent) pthread_cond_wait(&ch->_cond, &ch->mtx.mtx);\
    ch->sent = false;\
    thrd_mtx_unlock(ch->mtx);\
    return *val;\
}\
void _cat(thrd_chan(type), _free)(thrd_chan(type)* ch) {\
    pthread_cond_destroy(&ch->_cond);\
}\
thrd_chan(type) _cat(thrd_chan(type), _init)() {\
    thrd_chan(type) ch = {\
        .mtx = thrd_mtx_init(type)(0),\
        .snd = _cat(thrd_chan(type), _snd),\
        .recv = _cat(thrd_chan(type), _recv),\
        .free = _cat(thrd_chan(type), _free)\
    };\
    pthread_cond_init(&ch._cond, NULL);\
    return ch;\
}

// queue chan
#define thrd_qchan(type) _cat(_thrd_qchan_, type)
#define thrd_qchan_init(type) _cat(thrd_qchan(type), _init)

#define thrd_qchan_snd(ch, val) ch.snd(&ch, val)
#define thrd_qchan_recv(ch) ch.recv(&ch)
#define thrd_qchan_free(ch) ch.free(&ch)

#define QCHAN(type)\
VECTOR(type)\
MUTEX(vec(type))\
typedef struct _cat(__thrd_qchan_, type) {\
    thrd_mtx(vec(type)) mtx;\
    pthread_cond_t _cond;\
    bool receiving;\
    bool sent;\
    void (*snd)(struct _cat(__thrd_qchan_, type)*, type);\
    type (*recv)(struct _cat(__thrd_qchan_, type)*);\
    void (*free)(struct _cat(__thrd_qchan_, type)*);\
} thrd_qchan(type);\
void _cat(thrd_qchan(type), _snd)(thrd_qchan(type)* ch, type val) {\
    vec(type)* v = thrd_mtx_lock(ch->mtx);\
    v->push(v, val);\
    pthread_cond_signal(&ch->_cond);\
    thrd_mtx_unlock(ch->mtx);\
}\
type _cat(thrd_qchan(type), _recv)(thrd_qchan(type)* ch) {\
    vec(type)* v = thrd_mtx_lock(ch->mtx);\
    while(v->size == 0) pthread_cond_wait(&ch->_cond, &ch->mtx.mtx);\
    type res = v->pop(v);\
    thrd_mtx_unlock(ch->mtx);\
    return res;\
}\
void _cat(thrd_qchan(type), _free)(thrd_qchan(type)* ch) {\
    pthread_cond_destroy(&ch->_cond);\
    vec_free(ch->mtx.val);\
}\
thrd_qchan(type) _cat(thrd_qchan(type), _init)() {\
    thrd_qchan(type) ch = {\
        .mtx = thrd_mtx_init(vec(type))(vec_init(type)()),\
        .snd = _cat(thrd_qchan(type), _snd),\
        .recv = _cat(thrd_qchan(type), _recv),\
        .free = _cat(thrd_qchan(type), _free)\
    };\
    pthread_cond_init(&ch._cond, NULL);\
    return ch;\
}

#endif