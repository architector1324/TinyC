#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "image.h"
#include "mat.h"
#include "uni.h"
#include "rt.h"


int main() {
    // scene
    const size_t w = 800;
    const size_t h = 600;

    // create universe
    printf("create universe...\n");

    const size_t cube = 5; // 2 centimeter
    const size_t uni_count = cube * cube * cube;
    uni_vox uni[uni_count];
    for(size_t x = 0; x < cube; x++) {
        for(size_t y = 0; y < cube; y++){
            for(size_t z = 0; z < cube; z++) {
                srand(time(0));
                uni[x + cube * (y + cube * z)] = (uni_vox){
                    .pos = (mat_vec3){(w >> 1) + x, 1 + z, (h >> 1) + y},
                    .c = (uni_color){rand() % 256, 0, 0}
                };
            }
        }
    }

    // create light
    printf("create light...\n");

    rt_ray* light = (rt_ray*)malloc(w * h * sizeof(rt_ray));
    for(size_t x = 0; x < w; x++) {
        for(size_t y = 0; y < h; y++) {
            light[x + w * y] = rt_ray_new(
                (mat_vec3f){0.0f, 1.0f, 0.2f},
                (mat_vec3){x, 0, y},
                (uni_color){255, 255, 255},
                1.0f
            );
        }
    }

    // raytrace
    printf("raytrace...\n");

    uint8_t data[w * h * 4];

    for(size_t i = 0; i < uni_count; i++) {
        for(size_t x = 0; x < w; x++) {
            for(size_t y = 0; y < h; y++) {
                rt_ray* ray = light + x + w * y;
                while(rt_ray_trace(ray, uni + i));
                    // printf(
                    //     "raytraced %ld: %d %d %d\n",
                    //     x + w * y,
                    //     (uint8_t)(ray->c.r * ray->power),
                    //     (uint8_t)(ray->c.g * ray->power),
                    //     (uint8_t)(ray->c.b * ray->power)
                    // );
            }
        }

        // render
        for(size_t y = 0; y < h; y++) {
            for(size_t x = 0; x < w; x++){
                rt_ray* ray = light + x + w * y;
                if(rt_ray_collide(ray, &(mat_vec3){x, 0, y})) {
                    data[4 * (x + w * y)] = ray->c.r;
                    data[1 + 4 * (x + w * y)] = ray->c.g;
                    data[2 + 4 * (x + w * y)] = ray->c.b;
                    data[3 + 4 * (x + w * y)] = 255;
                }
            }
        }

        // save data to portable pixmap
        if (img_png_write("out.png", data, w, h)) abort();
    }

    // free
    printf("done.");
    free(light);

    return 0;
}
