#include <stdio.h>
#include "thrd.h"

QCHAN(float)
THREAD(void*, foo_t, void*, dumb);

thrd_qchan(float) ch;

void* foo() {
    printf("send: 1.0 2.0 3.0\n");
    thrd_qchan_snd(ch, 1.0f);
    thrd_qchan_snd(ch, 2.0f);
    thrd_qchan_snd(ch, 3.0f);
}

int main() {
    ch = thrd_qchan_init(float)();

    thrd(foo_t) th = thrd_init(foo_t)();
    thrd_create(foo_t, th, foo);

    sleep(2);

    printf("recv: %f\n", thrd_qchan_recv(ch));
    printf("recv: %f\n", thrd_qchan_recv(ch));
    printf("recv: %f\n", thrd_qchan_recv(ch));

    thrd_qchan_free(ch);
    return 0;
}
