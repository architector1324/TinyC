#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "image.h"
#include "mat.h"
#include "uni.h"
#include "rt.h"

int main() {
    // scene
    uni_vox vox = (uni_vox){
        .pos = (mat_vec3){0, 5, 0},
        .c = (uni_color){255, 0, 0}
    };

    rt_ray ray = rt_ray_new(
        (mat_vec3f){0.0f, 1.0f, 0.0f},
        (mat_vec3){0, 0, 0},
        (uni_color){255, 255, 255},
        1.0f
    );

    // render
    while(rt_ray_trace(&ray, &vox));
    if(rt_ray_collide(&ray, &(mat_vec3){0, 0, 0}))
        printf(
            "RAYTRACED: %d %d %d\n",
            (uint8_t)(ray.c.r * ray.power),
            (uint8_t)(ray.c.g * ray.power),
            (uint8_t)(ray.c.b * ray.power)
        );

    // render
    // const size_t w = 640;
    // const size_t h = 480;

    // uint8_t data[w * h * 4];

    // srand(time(0));

    // for(size_t y = 0; y < h; y++) {
    //     for(size_t x = 0; x < w; x++){
    //         for(size_t k = 0; k < 4; k++)
    //             data[k + 4 * (x + w * y)] = (uint8_t)(rand() % 256);
    //     }
    // }

    // // save data to portable pixmap
    // if (img_png_write("out.png", data, w, h)) abort();

    return 0;
}
