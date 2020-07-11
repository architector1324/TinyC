#include <stdio.h>
#include "cpt.h"

int main() {
    // generate keys
    tup(arr(uint8_t, 512), arr(uint8_t, 512)) keys = cpt_gen_keys();

    // encrypt and decrypt msg
    const uint8_t msg[] = "Hello, World!";
    vec_micro(uint8_t) encrypted = cpt_rsa_encrypt(slc_from(uint8_t)(msg, 13), &keys.t0);

    printf("msg=%s\nencrypted=", msg);
    for(size_t i = 0; i < encrypted.size; i++) printf("%02x", encrypted.data[i]);
    puts("");

    vec_micro(uint8_t) decrypted = cpt_rsa_decrypt(to_slc(encrypted), &keys.t1);
    printf("decrypted=%s\n", decrypted.data);

    return 0;
}
