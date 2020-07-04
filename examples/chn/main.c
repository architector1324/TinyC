#include <stdio.h>
#include "chn.h"

SLICE(float)
CHAIN(float)

int main() {
    chn(float) cn = chn_init(float)();

    float a[] = {3.14f, 2.71f};
    float b[] = {1.0f, 2.0f};
    float c = 3.0f;

    chn_chain(cn, slc_from(float)(a, 2));
    chn_chain(cn, slc_from(float)(b, 2));
    chn_chain(cn, slc_from(float)(&c, 1));

    printf(
        "%f %f %f %f %f\n",
        chn_at(cn, 0), chn_at(cn, 1),
        chn_at(cn, 2), chn_at(cn, 3),
        chn_at(cn, 4)
    );
    printf("size=%ld\n", cn.size);

    return 0;
}
