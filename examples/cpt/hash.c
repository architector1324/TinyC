#include <stdio.h>
#include "cpt.h"

int main() {
    const char msg[] = "Hello, World!";
    arr(uint8_t, 32) sha256 = cpt_sha256(slc_from(uint8_t)(msg, sizeof(msg) - 1));

    // print
    printf("msg=%s\n", msg);

    printf("sha256=");
    for(size_t i = 0; i < 32; i++) 
        printf("%02x", sha256.data[i]);
    puts("");

    return 0;
}
