#ifndef SLC
#define SLC

#include <stddef.h>

// settings
// #define SLICE_DEF_STD

// extra
#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y)

// base
#define slc(type) _cat(_slc_, type)
#define slc_mut(type) _cat(_slc_mut_, type)

#define slc_from(type) _cat(slc(type), _from)
#define slc_from_mut(type) _cat(slc_mut(type), _from)

#define to_slc(cnt) cnt.slice(&cnt)
#define to_slc_mut(cnt) cnt.slice_mut(&cnt)

#define SLICE(type)\
typedef struct _cat(_, slc(type)) {\
    const type* data;\
    size_t size;\
} slc(type);\
typedef struct _cat(_, slc_mut(type)) {\
    type* data;\
    size_t size;\
} slc_mut(type);\
slc(type) _cat(slc(type), _from)(const type* data, size_t size) {\
    return (slc(type)){data, size};\
}\
slc_mut(type) _cat(slc_mut(type), _from)(type* data, size_t size) {\
    return (slc_mut(type)){data, size};\
}

// defined slices for std
#ifdef SLICE_DEF_STD

#include <stdint.h>

SLICE(char)
SLICE(int)
SLICE(float)
SLICE(double)
SLICE(size_t)

SLICE(int8_t)
SLICE(int16_t)
SLICE(int32_t)
SLICE(int64_t)
SLICE(uint8_t)
SLICE(uint16_t)
SLICE(uint32_t)
SLICE(uint64_t)

#endif


#endif
