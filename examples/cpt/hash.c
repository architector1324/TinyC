#include <stdio.h>
#include "cpt.h"

int main() {
    const uint8_t* msg = "Hello, World!";

    arr(uint8_t, 16) md5 = cpt_md5(slc_from(uint8_t)(msg, 13));
    arr(uint8_t, 32) sha256 = cpt_sha256(slc_from(uint8_t)(msg, 13));

    // print
    printf("msg=%s\n", msg);

    printf("md5=");
    for(size_t i = 0; i < 16; i++)
        printf("%02x", md5.data[i]);
    puts("");

    printf("sha256=");
    for(size_t i = 0; i < 32; i++) 
        printf("%02x", sha256.data[i]);
    puts("");

    return 0;
}
