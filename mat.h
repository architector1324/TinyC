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


// single vector
size_t mat_vec3_abs(const mat_vec3* a) {
    return a->x * a->x + a->y * a->y + a->z * a->z;
}

mat_vec3 mat_vec3_smul(const mat_vec3* a, int64_t k) {
    return (mat_vec3) {
        .x = k * a->x,
        .y = k * a->y,
        .z = k * a->z
    };
}

#define CEIL_I64(x, y) (x % y) ? x / y + 1 : x / y

mat_vec3 mat_vec3_sdiv(const mat_vec3* a, int64_t k) {
    return (mat_vec3) {
        .x = CEIL_I64(a->x, k),
        .y = CEIL_I64(a->y, k),
        .z = CEIL_I64(a->z, k)
    };
}

mat_vec3 mat_vec3_inv(const mat_vec3* a) {
    return mat_vec3_smul(a, -1);
}

mat_vec3 mat_vec3_norm(const mat_vec3* a) {
    return mat_vec3_sdiv(a, (int64_t)mat_vec3_abs(a));
}

// two vectors
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

uint64_t mat_vec3_mul(const mat_vec3* a, const mat_vec3* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

mat_vec3 mat_vec3_vmul(const mat_vec3* a, const mat_vec3* b) {
    int64_t x = a->y * b->z - a->z * b->y;
    int64_t y = a->z * b->x - a->x * b->z;
    int64_t z = a->x * b->y - a->y * b->x;

    return (mat_vec3){x, y, z};
}

#endif
