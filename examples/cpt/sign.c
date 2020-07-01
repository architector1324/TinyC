#include <stdio.h>
#include "cpt.h"

int main() {
    // generate keys
    tup(arr(uint8_t, 512), arr(uint8_t, 512)) keys = cpt_gen_keys();

    // sign msg and verify
    const uint8_t* msg = "Hello, World!";
    arr(uint8_t, 256) sign = cpt_sign(slc_from(uint8_t)(msg, 13), &keys.t1);

    printf("msg=%s\nsign=", msg);
    for(size_t i = 0; i < 256; i++) printf("%02x", sign.data[i]);
    puts("");

    printf("%s\n", cpt_sign_verify(slc_from(uint8_t)(msg, 13), &sign, &keys.t0) ? "true" : "false");

    return 0;
}
