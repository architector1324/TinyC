#include <stdio.h>
#include "vec.h"

SLICE(float)
VECTOR(float)
MICRO_VECTOR(float)
BIG_VECTOR(float)


int main() {
    slc(float) dat0 = slc_from(float)((float[]){3.14f, 2.71f, 1.0f}, 0, 3);
    slc(float) dat1 = slc_from(float)((float[]){2.0f, 3.0f}, 0, 2);

    // concat vector
    vec(float) v0 = vec_from(float)(dat0);
    vec(float) v1 = vec_from(float)(dat1);
    vec_cat(v0, v1);

    printf(
        "%f %f %f %f %f\n",
        vec_at(v0, 0), vec_at(v0, 1),
        vec_at(v0, 2), vec_at(v0, 3),
        vec_at(v0, 4)
    );
    printf("cap=%ld size=%ld\n", v0.cap, v0.size);

    // concat micro vector
    vec_micro(float) v00 = vec_micro_from(float)(dat0);
    vec_micro(float) v10 = vec_micro_from(float)(dat1);
    vec_cat(v00, v10);

    printf(
        "%f %f %f %f %f\n",
        vec_at(v00, 0), vec_at(v00, 1),
        vec_at(v00, 2), vec_at(v00, 3),
        vec_at(v00, 4)
    );

    // concat big vector
    vec_big(float) v01 = vec_big_from(float)("v0.bin", dat0);
    vec_big(float) v11 = vec_big_from(float)("v1.bin", dat1);
    vec_cat(v01, v11);

    printf(
        "%f %f %f %f %f\n",
        vec_at(v01, 0), vec_at(v01, 1),
        vec_at(v01, 2), vec_at(v01, 3),
        vec_at(v01, 4)
    );

    // free
    vec_free(v0);
    vec_free(v1);
    vec_free(v01);
    vec_free(v11);

    return 0;
}