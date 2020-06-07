#ifndef RT
#define RT

#include <stdint.h>
#include "mat.h"
#include "uni.h"

#define RT_PWR_LESS 0.35

typedef struct _rt_ray {
    mat_vec3f dir; // should be normalized!
    mat_vec3 pos;
    uni_color c;
    float power; // intensity
} rt_ray;

rt_ray rt_ray_new(mat_vec3f dir, mat_vec3 pos, uni_color c, float power) {
    return (rt_ray) {
        .dir = mat_vec3f_norm(&dir),
        .pos = pos,
        .c = c,
        .power = power
    };
}

bool rt_ray_collide(const rt_ray* ray, const mat_vec3* p) {
    mat_vec3 delta = mat_vec3_sub(&ray->pos, p);

    float a = mat_vec3f_mul(&ray->dir, &ray->dir);
    float b = 2.0 * mat_vec3_mulf(&delta, &ray->dir);
    float c = mat_vec3_mul(&delta, &delta) - 1;
    float D = b * b - 4 * a * c;

    if(D >= 0) return true;
    return false;
}

bool rt_ray_trace(rt_ray* ray, const uni_vox* vox) {
    if(rt_ray_collide(ray, &vox->pos)) {
        ray->pos = vox->pos;
        ray->dir = mat_vec3f_inv(&ray->dir);
        ray->c = uni_color_blend(&ray->c, &vox->c);
        ray->power /= RT_PWR_LESS;

        return true;
    }
    return false;
}

#endif
