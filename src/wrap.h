#ifndef WRAP
#define WRAP

#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y)

#define ref(type) _cat(_ref_, type)
#define ref_new(type) (ref(type))malloc(sizeof(type))

#define REFERENCE(type) typedef type* ref(type);

#define strct(type) _cat(_struct_, type)
#define STRUCTURE(type) typedef struct type strct(type);

#define uni(type) _cat(_union_, type)
#define UNION(type) typedef union type uni(type);

#endif
