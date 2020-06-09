#ifndef MATH
#define MATH

#define MAT_TESTS

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

/*
Each method have a compute complexity in "mul".
Thats means a count of 64bit integer multiplications needed to compute by processor to obtain the result.

Also, methods that operate with floating point numbers have similar metric "mulf".

Experiments with stresses approve that:
mulf ~= 1.2 mul
*/

///////////////////////////
//   IMMUTABLE METHODS   //
///////////////////////////

// integer
float mat_vec3_abs(const mat_vec3* a) {
    // 3 mul
    return sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);
}

mat_vec3 mat_vec3_smul(const mat_vec3* a, int64_t k) {
    // 3 mul
    return (mat_vec3) {
        .x = k * a->x,
        .y = k * a->y,
        .z = k * a->z
    };
}

mat_vec3 mat_vec3_inv(const mat_vec3* a) {
    // 3 mul
    return mat_vec3_smul(a, -1);
}

bool mat_vec3_eq(const mat_vec3* a, const mat_vec3* b) {
    // 0 mul
    return (a->x == b->x) && (a->y == b->y) && (a->z == b->z);
}

mat_vec3 mat_vec3_add(const mat_vec3* a, const mat_vec3* b) {
    // 0 mul
    return (mat_vec3){
        .x = a->x + b->x,
        .y = a->y + b->y,
        .z = a->z + b->z
    };
}

mat_vec3 mat_vec3_sub(const mat_vec3* a, const mat_vec3* b) {
    // 0 mul
    return (mat_vec3){
        .x = a->x - b->x,
        .y = a->y - b->y,
        .z = a->z - b->z
    };
}

uint64_t mat_vec3_mul(const mat_vec3* a, const mat_vec3* b) {
    // 3 mul
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

mat_vec3 mat_vec3_vmul(const mat_vec3* a, const mat_vec3* b) {
    // 6 mul
    int64_t x = a->y * b->z - a->z * b->y;
    int64_t y = a->z * b->x - a->x * b->z;
    int64_t z = a->x * b->y - a->y * b->x;

    return (mat_vec3){x, y, z};
}

// float
float mat_vec3f_abs(const mat_vec3f* a) {
    // 3 mulf = 3.6 mul
    return sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);
}

mat_vec3f mat_vec3f_smul(const mat_vec3f* a, float k) {
    // 3 mulf = 3.6 mul
    return (mat_vec3f) {
        .x = k * a->x,
        .y = k * a->y,
        .z = k * a->z
    };
}

mat_vec3f mat_vec3f_norm(const mat_vec3f* a) {
    // 3 mulf + 3 mulf = 6 mulf = 7.2 mul
    return mat_vec3f_smul(a, 1.0 / mat_vec3f_abs(a));
}

mat_vec3f mat_vec3f_inv(const mat_vec3f* a) {
    // 3 mulf = 3.6 mul
    return mat_vec3f_smul(a, -1.0);
}

bool mat_vec3f_eq(const mat_vec3f* a, const mat_vec3f* b) {
    // 0 mul
    return (a->x == b->x) && (a->y == b->y) && (a->z == b->z);
}

mat_vec3f mat_vec3f_add(const mat_vec3f* a, const mat_vec3f* b) {
    // 0 mul
    return (mat_vec3f){
        .x = a->x + b->x,
        .y = a->y + b->y,
        .z = a->z + b->z
    };
}

mat_vec3f mat_vec3f_sub(const mat_vec3f* a, const mat_vec3f* b) {
    // 0 mul
    return (mat_vec3f){
        .x = a->x - b->x,
        .y = a->y - b->y,
        .z = a->z - b->z
    };
}

float mat_vec3f_mul(const mat_vec3f* a, const mat_vec3f* b) {
    // 3 mulf = 3.6 mul
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

mat_vec3f mat_vec3f_vmul(const mat_vec3f* a, const mat_vec3f* b) {
    // 6 mulf = 7.2 mul
    float x = a->y * b->z - a->z * b->y;
    float y = a->z * b->x - a->x * b->z;
    float z = a->x * b->y - a->y * b->x;

    return (mat_vec3f){x, y, z};
}

// mixed
float mat_vec3_mulf(const mat_vec3* a, const mat_vec3f* b) {
    // unknow
    return a->x * b->x + a->y * b->y + a->z * b->z;
}


///////////////////////////
//    MUTABLE METHODS    //
///////////////////////////

// integer
void mat_fast_vec3_smul(const mat_vec3* a, int64_t k, mat_vec3* res) {
    // 3 mulf = 3.6 mul
    res->x = k * a->x;
    res->y = k * a->y;
    res->z = k * a->z;
}

void mat_fast_vec3_inv(const mat_vec3* a, mat_vec3* res) {
    // 3 mulf = 3.6 mul
    mat_fast_vec3_smul(a, -1, res);
}

void mat_fast_vec3_add(const mat_vec3* a, const mat_vec3* b, mat_vec3* res) {
    // 0 mul
    res->x = a->x + b->x;
    res->y = a->y + b->y;
    res->z = a->z + b->z;
}

void mat_fast_vec3_sub(const mat_vec3* a, const mat_vec3* b, mat_vec3* res) {
    // 0 mul
    res->x = a->x - b->x;
    res->y = a->y - b->y;
    res->z = a->z - b->z;
}

void mat_fast_vec3_vmul(const mat_vec3* a, const mat_vec3* b, mat_vec3* res) {
    // 6 mulf = 7.2 mul
    res->x = a->y * b->z - a->z * b->y;
    res->y = a->z * b->x - a->x * b->z;
    res->z = a->x * b->y - a->y * b->x;
}

// float
void mat_fast_vec3f_smul(const mat_vec3f* a, float k, mat_vec3f* res) {
    // 3 mulf = 3.6 mul
    res->x = k * a->x;
    res->y = k * a->y;
    res->z = k * a->z;
}

void mat_fast_vec3f_norm(const mat_vec3f* a, mat_vec3f* res) {
    // 6 mulf = 7.2 mul
    mat_fast_vec3f_smul(a, 1.0 / mat_vec3f_abs(a), res);
}

void mat_fast_vec3f_inv(const mat_vec3f* a, mat_vec3f* res) {
    // 3 mulf = 3.6 mul
    mat_fast_vec3f_smul(a, -1.0, res);
}

void mat_fast_vec3f_add(const mat_vec3f* a, const mat_vec3f* b, mat_vec3f* res) {
    // 0 mul
    res->x = a->x + b->x;
    res->y = a->y + b->y;
    res->z = a->z + b->z;
}

void mat_fast_vec3f_sub(const mat_vec3f* a, const mat_vec3f* b, mat_vec3f* res) {
    // 0 mul
    res->x = a->x - b->x;
    res->y = a->y - b->y;
    res->z = a->z - b->z;
}

void mat_fast_vec3f_vmul(const mat_vec3f* a, const mat_vec3f* b, mat_vec3f* res) {
    // 6 mulf = 7.2 mul
    res->x = a->y * b->z - a->z * b->y;
    res->y = a->z * b->x - a->x * b->z;
    res->z = a->x * b->y - a->y * b->x;
}


///////////////////////////
//     STRESS TESTS      //
///////////////////////////
#ifdef MAT_TESTS

#include <time.h>
#include <stdio.h>
#include <omp.h>

void mat_stress(size_t million) {
    const size_t count = 1000000 * million;

    printf("vec3 mul: %ld, single thread\n------------------------------------\n", count);

    mat_vec3 a = {2, 3, 4};
    mat_vec3 b = {5, 7, 8};

    // immutable int
    float start = omp_get_wtime();
    for(size_t i = 0; i < count; i++) {
        mat_vec3 c = mat_vec3_vmul(&a, &b);
    }
    float end = omp_get_wtime();
    printf("immut int: %fs.\n", end - start);

    // mutalbe int
    mat_vec3 c;

    start = omp_get_wtime();
    for(size_t i = 0; i < count; i++) {
        mat_fast_vec3_vmul(&a, &b, &c);
    }
    end = omp_get_wtime();
    printf("mut int: %fs.\n", end - start);

    // immutable float
    mat_vec3f d = {2.0, 3.0, 4.0};
    mat_vec3f e = {5.0, 7.0, 8.0};

    start = omp_get_wtime();
    for(size_t i = 0; i < count; i++) {
        mat_vec3f c = mat_vec3f_vmul(&d, &e);
    }
    end = omp_get_wtime();
    printf("immut float: %fs\n", end - start);

    // mutable float
    mat_vec3f f;

    start = omp_get_wtime();
    for(size_t i = 0; i < count; i++) {
        mat_fast_vec3f_vmul(&d, &e, &f);
    }
    end = omp_get_wtime();
    printf("mut float: %fs\n------------------------------------\n", end - start);

    // immutable mixed
}

void mat_stress_multi(size_t million) {
    const size_t count = 1000000 * million;

    printf("vec3 mul: %ld, %d threads\n------------------------------------\n", count, omp_get_max_threads());

    mat_vec3 a = {2, 3, 4};
    mat_vec3 b = {5, 7, 8};

    // immutable int
    float start = omp_get_wtime();
    #pragma omp parallel for
    for(size_t i = 0; i < count; i++) {
        mat_vec3 c = mat_vec3_vmul(&a, &b);
    }
    float end = omp_get_wtime();
    printf("immut int: %fs\n", end - start);

    // mutalbe int
    mat_vec3 c;

    start = omp_get_wtime();
    #pragma omp parallel for private(c)
    for(size_t i = 0; i < count; i++) {
        mat_fast_vec3_vmul(&a, &b, &c);
    }
    end = omp_get_wtime();
    printf("mut int: %fs\n", end - start);

    // immutable float
    mat_vec3f d = {2.0, 3.0, 4.0};
    mat_vec3f e = {5.0, 7.0, 8.0};

    start = omp_get_wtime();
    #pragma omp parallel for
    for(size_t i = 0; i < count; i++) {
        mat_vec3f c = mat_vec3f_vmul(&d, &e);
    }
    end = omp_get_wtime();
    printf("immut float: %fs\n", end - start);

    // mutable float
    mat_vec3f f;

    start = omp_get_wtime();
    #pragma omp parallel for private(c)
    for(size_t i = 0; i < count; i++) {
        mat_fast_vec3f_vmul(&d, &e, &f);
    }
    end = omp_get_wtime();
    printf("mut float: %fs\n------------------------------------\n", end - start);
}

#endif

#endif
