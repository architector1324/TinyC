#include <stdio.h>
#include "arr.h"

SLICE(float)
ARRAY(float, 32)

int main() {
    arr(float, 32) v = arr_init(float, 32)();
    arr_set(v, 0, 3.14);
    arr_set(v, 1, 2.71);

    printf("%f %f\n", arr_at(v, 0), arr_at(v, 1));

    return 0;
}
