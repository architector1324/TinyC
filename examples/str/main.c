#include <stdio.h>
#include "str.h"

int main() {
    // create string from chars array
    str s = str_from("Hello!");
    printf("%s\n", s.data);

    // concat string and chars array
    s = str_cat_from(str_from("Hello, "), "World!");
    printf("%s\n", s.data);

    // concat string from another string
    s = str_cat(str_from("Hello, "), str_from("World!"));
    printf("%s\n", s.data);

    // create repeated string from chars array
    s = str_repeat_from("Abc", 3);
    printf("%s\n", s.data);

    // create repeated string from another string
    s = str_repeat(str_from("Def"), 2);
    printf("%s\n", s.data);

    return 0;
}
