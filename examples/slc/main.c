#include <stdio.h>
#include "arr.h"
#include "vec.h"

SLICE(float)
VECTOR(float)
MICRO_VECTOR(float)
ARRAY(float, 3)

void foo(slc(float) a) {
    for(size_t i = 0; i < a.size; i++) printf("%f ", a.data[i]);
    puts("");
}

void boo(slc_mut(float) a) {
    for(size_t i = 0; i < a.size; i++) a.data[i] = 1.0f;
}

int main() {
    // get slice from vector
    vec(float) a = vec_init(float)();
    vec_push(a, 3.14f);
    vec_push(a, 2.71f);
    vec_push(a, 1.0f);

    foo(to_slc(a));
    boo(to_slc_mut(a));
    foo(to_slc(a));

    // get slice from micro vector
    vec_micro(float) b = vec_micro_init(float)();
    vec_push(b, 3.14f);
    vec_push(b, 2.71f);
    vec_push(b, 1.0f);

    foo(to_slc(b));
    boo(to_slc_mut(b));
    foo(to_slc(b));

    // get slice from array
    arr(float, 3) c = arr_init(float, 3)();
    arr_set(c, 0, 3.14f);
    arr_set(c, 1, 2.71f);
    arr_set(c, 2, 1.0f);

    foo(to_slc(c));
    boo(to_slc_mut(c));
    foo(to_slc(c));

    vec_free(a);
    return 0;
}
