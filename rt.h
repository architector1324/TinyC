#ifndef RT
#define RT

#include <stdint.h>
#include "mat.h"
#include "uni.h"

// raytracing
typedef struct _rt_ray {
    mat_vec3 dir; // should be normalized!
    mat_vec3 pos;
    float power; // intensity
} rt_ray;

void rt_ray_collide(rt_ray* ray, const rt_vox* uni, size_t uni_count) {
    for(size_t i = 0; i < uni_count; i++) {
        if (mat_vec3_eq(&ray->pos, &uni[i].pos)) {
           ray->pos = mat_vec3_inv(&ray->pos);
           ray->power /= 2;
           return; 
        }
    }

}

void rt_ray_forward(rt_ray* ray) {
    ray->pos = mat_vec3_add(&ray->pos, &ray->dir);
}

#endif
