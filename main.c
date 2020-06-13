#include <stdio.h>
#include "thrd.h"

THREAD(float, sum, float a, float b) {
    return arg->a + arg->b;
}

int main() {
    printf("%f\n", thrd_call(sum, 3.14, 2.71));

    return 0;
}
