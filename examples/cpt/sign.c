#include <stdio.h>
#include "cpt.h"

int main() {
    // generate keys
    tup(arr(uint8_t, 512), arr(uint8_t, 512)) keys = cpt_gen_keys();

    // sign msg and verify
    vec_micro(uint8_t) msg = vec_micro_from(uint8_t)("Hello, World!", 13);
    arr(uint8_t, 256) sign = cpt_sign(&msg, &keys.t1);

    printf("msg=%s\nsign=", msg.data);
    for(size_t i = 0; i < 256; i++) printf("%02x", sign.data[i]);
    puts("");

    printf("%s\n", cpt_sign_verify(&msg, &sign, &keys.t0) ? "true" : "false");

    return 0;
}
