#ifndef RT
#define RT

#include <stdint.h>
#include "mat.h"
#include "uni.h"

#define RT_PWR_LESS 0.35

typedef struct _rt_ray {
    mat_vec3 dir; // should be normalized!
    mat_vec3 pos;
    uni_color c;
    float power; // intensity
} rt_ray;

rt_ray rt_ray_new(mat_vec3 dir, mat_vec3 pos, uni_color c, float power) {
    return (rt_ray) {
        .dir = mat_vec3_norm(&dir),
        .pos = pos,
        .c = c,
        .power = power
    };
}

bool rt_ray_collide(rt_ray* ray, const uni_vox* uni, size_t uni_count) {
    for(size_t i = 0; i < uni_count; i++) {
        if (mat_vec3_eq(&ray->pos, &uni[i].pos)) {
           ray->dir = mat_vec3_inv(&ray->dir);
           ray->c = uni_color_blend(&ray->c, &uni[i].c);
           ray->power /= RT_PWR_LESS;
           return true; 
        }
    }
    return false;
}

void rt_ray_forward(rt_ray* ray) {
    ray->pos = mat_vec3_add(&ray->pos, &ray->dir);
}

// void rt_ray_raytrace(rt_ray* ray, const uni_vox* uni, size_t uni_count) {
//     rt_ray_collide(ray, uni, uni_count);
//     rt_ray_forward(ray);
// }

#endif
