#ifndef UNI
#define UNI

#include <stdint.h>
#include "mat.h"

typedef struct _rt_color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rt_color;


typedef struct _rt_vox {
    mat_vec3 pos;
    rt_color c;
    // physical parameters
} rt_vox;

#endif
