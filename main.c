#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "img.h"
#include "mat.h"
#include "uni.h"
#include "rt.h"


int main() {
    mat_stress(1000);
    mat_stress_multi(1000);
    // scene

    // render (one fullhd frame = 2073600 rays)
    const size_t w = 1920;
    const size_t h = 1080;

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
