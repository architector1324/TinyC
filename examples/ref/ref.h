#ifndef TUP
#define TUP

#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y)

#define ref(type) _cat(_ref_, type)
#define REF(type) typedef type* ref(type);

#endif