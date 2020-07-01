#include <stdio.h>
#include "thrd.h"

RWLOCK(float)
THREAD(void*, foo_t, size_t, i);

thrd_rwlck(float) shared;

void* foo(size_t i) {
    printf("read%ld: %f\n", i, *thrd_rwlck_rlock(shared));
    sleep(i);
    thrd_rwlck_unlock(shared);
}

void* bar(size_t i) {
    float* val = thrd_rwlck_lock(shared);
    *val *= 2.0f;
    *val /= 2.0f;

    printf("write%ld: %f\n", i, *val);
    sleep(i);
    thrd_rwlck_unlock(shared);
}

int main() {
    shared = thrd_rwlck_init(float)(1.6f);
    
    thrd(foo_t) rd[2] = {thrd_init(foo_t)(), thrd_init(foo_t)()};
    thrd_create(foo_t, rd[0], foo, 1);
    thrd_create(foo_t, rd[1], foo, 2);

    thrd(foo_t) wr[2] = {thrd_init(foo_t)(), thrd_init(foo_t)()};
    thrd_create(foo_t, wr[0], bar, 1);
    thrd_create(foo_t, wr[1], bar, 2);

    thrd_join(rd[0]);
    thrd_join(rd[1]);

    thrd_join(wr[0]);
    thrd_join(wr[1]);

    thrd_rwlck_free(shared);

    return 0;
}