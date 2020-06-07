#ifndef MATH
#define MATH

#include <math.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct _mat_vec3 {
    int64_t x;
    int64_t y;
    int64_t z;
} mat_vec3;

typedef struct _mat_vec3f {
    float x;
    float y;
    float z;
} mat_vec3f;


// integer vector
float mat_vec3_abs(const mat_vec3* a) {
    return sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);
}

mat_vec3 mat_vec3_smul(const mat_vec3* a, int64_t k) {
    return (mat_vec3) {
        .x = k * a->x,
        .y = k * a->y,
        .z = k * a->z
    };
}

mat_vec3 mat_vec3_inv(const mat_vec3* a) {
    return mat_vec3_smul(a, -1);
}

bool mat_vec3_eq(const mat_vec3* a, const mat_vec3* b) {
    return (a->x == b->x) && (a->y == b->y) && (a->z == b->z);
}

mat_vec3 mat_vec3_add(const mat_vec3* a, const mat_vec3* b) {
    return (mat_vec3){
        .x = a->x + b->x,
        .y = a->y + b->y,
        .z = a->z + b->z
    };
}

mat_vec3 mat_vec3_sub(const mat_vec3* a, const mat_vec3* b) {
    return (mat_vec3){
        .x = a->x - b->x,
        .y = a->y - b->y,
        .z = a->z - b->z
    };
}

uint64_t mat_vec3_mul(const mat_vec3* a, const mat_vec3* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

mat_vec3 mat_vec3_vmul(const mat_vec3* a, const mat_vec3* b) {
    int64_t x = a->y * b->z - a->z * b->y;
    int64_t y = a->z * b->x - a->x * b->z;
    int64_t z = a->x * b->y - a->y * b->x;

    return (mat_vec3){x, y, z};
}

// float vector
float mat_vec3f_abs(const mat_vec3f* a) {
    return sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);
}

mat_vec3f mat_vec3f_smul(const mat_vec3f* a, float k) {
    return (mat_vec3f) {
        .x = k * a->x,
        .y = k * a->y,
        .z = k * a->z
    };
}

mat_vec3f mat_vec3f_norm(const mat_vec3f* a) {
    return mat_vec3f_smul(a, 1.0 / mat_vec3f_abs(a));
}

mat_vec3f mat_vec3f_inv(const mat_vec3f* a) {
    return mat_vec3f_smul(a, -1.0);
}

bool mat_vec3f_eq(const mat_vec3f* a, const mat_vec3f* b) {
    return (a->x == b->x) && (a->y == b->y) && (a->z == b->z);
}

mat_vec3f mat_vec3f_add(const mat_vec3f* a, const mat_vec3f* b) {
    return (mat_vec3f){
        .x = a->x + b->x,
        .y = a->y + b->y,
        .z = a->z + b->z
    };
}

mat_vec3f mat_vec3f_sub(const mat_vec3f* a, const mat_vec3f* b) {
    return (mat_vec3f){
        .x = a->x - b->x,
        .y = a->y - b->y,
        .z = a->z - b->z
    };
}

float mat_vec3f_mul(const mat_vec3f* a, const mat_vec3f* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

mat_vec3f mat_vec3f_vmul(const mat_vec3f* a, const mat_vec3f* b) {
    float x = a->y * b->z - a->z * b->y;
    float y = a->z * b->x - a->x * b->z;
    float z = a->x * b->y - a->y * b->x;

    return (mat_vec3f){x, y, z};
}

// mixed vector
float mat_vec3_mulf(const mat_vec3* a, const mat_vec3f* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

#endif
