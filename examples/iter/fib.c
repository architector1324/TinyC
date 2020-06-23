#include <stdio.h>
#include "iter.h"

typedef struct _fib {
    size_t prev;
    size_t curr;
} fib;

ITERATOR(fib) {
    size_t tmp = it->last.prev + it->last.curr;
    it->last.prev = it->last.curr;
    it->last.curr = tmp;
    return some(fib, it->last);
}

int main() {
    iter(fib) it = iter_init(fib)((fib){1, 1});

    printf("%ld\n", iter_next(it).t0.curr);
    printf("%ld\n", iter_next(it).t0.curr);
    printf("%ld\n", iter_next(it).t0.curr);
    printf("%ld\n", iter_next(it).t0.curr);

    return 0;
}
