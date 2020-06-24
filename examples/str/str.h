#ifndef STR
#define STR

#include "vec.h"
#include "string.h"

#define STR_MAX_LEN 1024

#define MICRO_VECTOR_SIZE STR_MAX_LEN
MICRO_VECTOR(char)
#define MICRO_VECTOR_SIZE 100

#define str_init vec_micro_init(char)

typedef vec_micro(char) str;

str str_cat(str s0, str s1) {
    strncpy(s0.data + s0.size, s1.data, STR_MAX_LEN - (s0.size + s1.size));
    s0.size += s1.size;
    return s0;
}

str str_cat_from(str s0, const char* s1) {
    strncpy(s0.data + s0.size, s1, STR_MAX_LEN - s0.size);
    s0.size += strnlen(s1, STR_MAX_LEN - s0.size);
    return s0;
}

str str_from(const char* s) {
    str res = str_init();
    return str_cat_from(res, s);
}

str str_repeat(str s, size_t count) {
    str res = str_init();
    for(size_t i = 0; i < count; i++) res = str_cat(res, s);
    return res;
}

str str_repeat_from(const char* s, size_t count) {
    str res = str_init();
    for(size_t i = 0; i < count; i++) res = str_cat_from(res, s);
    return res;
}

#endif