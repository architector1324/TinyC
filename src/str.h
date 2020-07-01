#ifndef STR
#define STR

#include <stdbool.h>

#include "vec.h"
#include "string.h"

#define STR_MAX_LEN 1024
SLICE(char)
MICRO_VECTOR_CUSTOM(char, STR_MAX_LEN)

#define str_init vec_micro_init(char)

typedef vec_micro(char) str;

str str_cat(str s0, const str s1) {
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

bool str_cmp_from(const str s0, const char* s1) {
    size_t len = strnlen(s1, STR_MAX_LEN - s0.size);
    return !strncmp(s0.data, s1, STR_MAX_LEN - (s0.size < len ? len : s0.size));
}

bool str_cmp(const str s0, const str s1) {
    return !strncmp(s0.data, s1.data, STR_MAX_LEN - (s0.size < s1.size ? s1.size : s0.size));
}

#endif