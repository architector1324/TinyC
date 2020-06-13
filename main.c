#include <stdio.h>
#include "thrd.h"

MUTEX(float)

thrd_mtx(float) shared;

THREAD(void*, foo) {
    for(size_t i = 0; i < 100000; i++) {
        float* val = thrd_mtx_lock(shared);
        *val *= 2.0f;
        *val /= 2.0f;
        thrd_mtx_unlock(shared);
    }
}

int main() {
    shared = thrd_mtx_init(float)(1.6f);
 
    thrd(foo) th0;
    thrd(foo) th1;

    thrd_create(foo, th0);
    thrd_create(foo, th1);

    thrd_join(th0);
    thrd_join(th1);

    printf("shared: %f\n", shared.val);

    thrd_mtx_free(shared);

    return 0;
}
