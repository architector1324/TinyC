#include <stdio.h>
#include "iter.h"

typedef size_t counter;

ITERATOR(counter) {
    if(it->last >= 10)
        return none(counter);
    return some(counter, it->last++);
}

int main() {
    iter(counter) c = iter_init(counter)((counter)6);
    iter_foreach(counter, c, my, printf("%ld\n", my));

    return 0;
}