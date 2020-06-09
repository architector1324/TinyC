#ifndef UNI
#define UNI

#include <stdint.h>
#include "mat.h"

// universe resolution = matter voxels / meter
#define UNI_RES 10000

#define UNI_METER UNI_RES
#define UNI_CENTIMETER UNI_METER / 100
#define UNI_MILLIMETRE UNI_METER / 1000

typedef struct _uni_color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} uni_color;

uni_color uni_color_blend(const uni_color* a, const uni_color* b) {
    return (uni_color){
        .r = (uint8_t)fmin((float)a->r * (float)b->r, 255),
        .g = (uint8_t)fmin((float)a->g * (float)b->g, 255),
        .b = (uint8_t)fmin((float)a->b * (float)b->b, 255),
    };
}


typedef struct _uni_vox {
    mat_vec3 pos;
    uni_color c;
    // physical parameters
} uni_vox;

#endif
