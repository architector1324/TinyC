#include <stdio.h>
#include "thrd.h"

QCHAN(float)

thrd_qchan(float) ch;

THREAD(void*, A) {
    printf("send: 1.0 2.0 3.0\n");
    thrd_qchan_snd(ch, 1.0f);
    thrd_qchan_snd(ch, 2.0f);
    thrd_qchan_snd(ch, 3.0f);
}

int main() {
    ch = thrd_qchan_init(float)();

    thrd(A) th;
    thrd_create(A, th);

    sleep(2);

    printf("recv: %f\n", thrd_qchan_recv(ch));
    printf("recv: %f\n", thrd_qchan_recv(ch));
    printf("recv: %f\n", thrd_qchan_recv(ch));

    thrd_qchan_free(ch);
    return 0;
}
