#include <stdio.h>
#include "chn.h"

SLICE(float)
MICRO_VECTOR(float)
CHAIN(float)

int main() {
    // immutable chain
    chn(float) cn = chn_init(float)();

    float a[] = {1.0f, 2.0f};

    vec_micro(float) b = vec_micro_from(float)(slc_from(float)((float[]){3.0f, 4.0f}, 2));
    vec_push(b, 5.0f);

    chn_chain(cn, slc_from(float)(a, 2));
    chn_chain(cn, to_slc(b));

    printf(
        "%f %f %f %f %f\n",
        chn_at(cn, 0), chn_at(cn, 1),
        chn_at(cn, 2), chn_at(cn, 3),
        chn_at(cn, 4)
    );
    printf("size=%ld\n", cn.size);

    // mutable chain
    chn_mut(float) cn1 = chn_init_mut(float)();

    chn_chain(cn1, slc_from_mut(float)(a, 2));
    chn_chain(cn1, to_slc_mut(b));

    chn_set(cn1, 3, -2.13f);

    printf(
        "%f %f %f %f %f\n",
        chn_at(cn1, 0), chn_at(cn1, 1),
        chn_at(cn1, 2), chn_at(cn1, 3),
        chn_at(cn1, 4)
    );
    printf("size=%ld\n", cn1.size);

    return 0;
}
