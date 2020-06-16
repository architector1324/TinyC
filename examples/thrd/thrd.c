#include <stdio.h>
#include "thrd.h"

THREAD(float, foo, float a) {
    printf("%f\n", arg->a);
    return arg->a / 2.0f;
}

int main() {
    thrd(foo) th;
    thrd_create(foo, th, 3.14f);

    printf("%f\n", thrd_join(th));
    return 0;
}