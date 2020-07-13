#include <stdio.h>
#include "thrd.h"

THREAD(void*, foo_t, void*, dump);

void* foo() {
    return NULL;
}

int main() {
    thrd(foo_t) th = thrd_init(foo_t)(0);

    // create thread with 8Kb stack
    printf("stack size=%ld\n", th.stack);

    thrd_create(foo_t, th, foo);
    thrd_join(th);

    // create thread with 8Mb stack
    th = thrd_init(foo_t)(8 * 1024 * 1024);
    printf("stack size=%ld\n", th.stack);

    thrd_create(foo_t, th, foo);
    thrd_join(th);

    return 0;
}
