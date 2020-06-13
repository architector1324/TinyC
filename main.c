#include <stdio.h>
#include "thrd.h"

RWLOCK(float)

thrd_rwlck(float) shared;

THREAD(void*, foo, size_t i) {
    printf("read%ld: %f\n", arg->i, *thrd_rwlck_rlock(shared));
    sleep(arg->i);
    thrd_rwlck_unlock(shared);
}

THREAD(void*, bar, size_t i) {
    float* val = thrd_rwlck_lock(shared);
    *val *= 2.0f;
    *val /= 2.0f;

    printf("write%ld: %f\n", arg->i, *val);
    sleep(arg->i);
    thrd_rwlck_unlock(shared);
}

int main() {
    shared = thrd_rwlck_init(float)(1.6f);
    
    thrd(foo) rd[2];
    thrd_create(foo, rd[0], 1);
    thrd_create(foo, rd[1], 2);

    thrd(bar) wr[2];
    thrd_create(bar, wr[0], 1);
    thrd_create(bar, wr[1], 2);

    thrd_join(rd[0]);
    thrd_join(rd[1]);

    thrd_join(wr[0]);
    thrd_join(wr[1]);

    thrd_rwlck_free(shared);

    return 0;
}
