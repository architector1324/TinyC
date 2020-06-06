#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "image.h"
#include "rt.h"

int main() {
   // generate data
    const size_t w = 640;
    const size_t h = 480;

    uint8_t data[w * h * 4];

    srand(time(0));

    for(size_t y = 0; y < h; y++) {
        for(size_t x = 0; x < w; x++){
            for(size_t k = 0; k < 4; k++)
                data[k + 4 * (x + w * y)] = (uint8_t)(rand() % 256);
        }
    }

    // save data to portable pixmap
    if (img_png_write("out.png", data, w, h)) abort();

    return 0;
}
