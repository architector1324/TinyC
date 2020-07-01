#include <stdio.h>
#include "thrd.h"

MUTEX(float)
THREAD(void*, foo_t, void*, dumb);

thrd_mtx(float) shared;

void* foo() {
    for(size_t i = 0; i < 100000; i++) {
        float* val = thrd_mtx_lock(shared);
        *val *= 2.0f;
        *val /= 2.0f;
        thrd_mtx_unlock(shared);
    }
}

int main() {
    shared = thrd_mtx_init(float)(1.6f);
 
    thrd(foo_t) th0;
    thrd(foo_t) th1;

    thrd_create(foo_t, th0, foo);
    thrd_create(foo_t, th1, foo);

    thrd_join(th0);
    thrd_join(th1);

    printf("shared: %f\n", shared.val);

    thrd_mtx_free(shared);

    return 0;
}