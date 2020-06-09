#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "img.h"
#include "mat.h"
#include "uni.h"
#include "rt.h"


int main() {
    mat_stress(1000);

    // scene

    // render
    const size_t w = 800;
    const size_t h = 600;

    uint8_t data[w * h * 4];
    for(size_t y = 0; y < h; y++) {
        for(size_t x = 0; x < w; x++){
            size_t offs = 4 * (x + w * y);
            data[offs] = 0;
            data[1 + offs] = 0;
            data[2 + offs] = 0;
            data[3 + offs] = 255;
        }
    }

    // save data to portable pixmap
    if (img_png_write("out.png", data, w, h)) abort();

    return 0;
}
