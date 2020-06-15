#include <stdio.h>
#include "thrd.h"

CHAN(float)

thrd_chan(float) ch;

THREAD(void*, prod, float a) {
    printf("snd: %f\n", arg->a);
    thrd_chan_snd(ch, arg->a);
}

int main() {
    ch = thrd_chan_init(float)();

    thrd(prod) th;
    thrd_create(prod, th, 3.14f);

    printf("recv: %f\n", thrd_chan_recv(ch));

    thrd_chan_free(ch);

    return 0;
}