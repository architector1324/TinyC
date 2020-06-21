#include <stdio.h>
#include "tup.h"

TUPLE(float, size_t)

int main() {
    tup(float, size_t) a = {3.14, 123};
    printf("(%f %ld)\n", a.t0, a.t1);

    return 0;
}
