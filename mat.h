#ifndef MATH
#define MATH

#include <math.h>
#include <stdbool.h>


typedef struct _mat_vec3 {
    float x;
    float y;
    float z;
} mat_vec3;


// single vector
float mat_vec3_abs(const mat_vec3* a) {
    return fabs(a->x * a->x + a->y * a->y + a->z * a->z);
}

mat_vec3 mat_vec3_smul(const mat_vec3* a, float k) {
    mat_vec3 res = {
        .x = k * a->x,
        .y = k * a->y,
        .z = k * a->z
    };
    return res;
}

mat_vec3 mat_vec3_inv(const mat_vec3 *a) {
    return mat_vec3_smul(a, -1.0);
}

// two vectors
bool mat_vec3_eq(const mat_vec3* a, const mat_vec3* b) {
    return (a->x == b->x) && (a->y == b->y) && (a->z == b->z);
}

mat_vec3 mat_vec3_add(const mat_vec3* a, const mat_vec3* b) {
    mat_vec3 res = {
        .x = a->x + b->x,
        .y = a->y + b->y,
        .z = a->z + b->z
    };
    return res;
}

#endif
