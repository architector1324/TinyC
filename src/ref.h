#ifndef REF
#define REF

#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y)

#define ref(type) _cat(_ref_, type)
#define ref_new(type) (ref(type))malloc(sizeof(type))

#define REFERENCE(type) typedef type* ref(type);

#endif