#include <stdio.h>
#include "thrd.h"

CHAN(float)

thrd_chan(float) ch;

THREAD(void*, prod, float a) {
    printf("snd: %f\n", arg->a);
    thrd_chan_snd(ch, arg->a);
}

THREAD(void*, cons) {
    printf("recv: %f\n", thrd_chan_recv(ch));
}

int main() {
    ch = thrd_chan_init(float)();

    thrd(prod) th0;
    thrd(cons) th1;

    thrd_create(prod, th0, 3.14f);
    thrd_create(cons, th1);

    thrd_join(th0);
    thrd_join(th1);

    thrd_chan_free(ch);

    return 0;
}
