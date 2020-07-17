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

    // cmp string and chars array
    printf("%s\n", str_cmp_from(str_from("Hello!"), "Hello!") ? "true" : "false");
    printf("%s\n", str_cmp_from(str_from("Hello!"), "Hello!1") ? "true" : "false");

    // cmp string and another string
    printf("%s\n", str_cmp(str_from("Hello!"), str_from("Hello!")) ? "true" : "false");
    printf("%s\n", str_cmp(str_from("Hello!"), str_from("Hello!1")) ? "true" : "false");

    // regular expression match
    s = str_from("`Hello, world!`");
    vec_micro(str) m = str_re_match("^`([^`]+)`|(\\w+)", 2, to_slc(s));
    puts(m.data[1].data);

    s = str_from("text");
    m = str_re_match("^`([^`]+)`|(\\w+)", 2, to_slc(s));
    puts(m.data[1].data);

    return 0;
}
