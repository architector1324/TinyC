#ifndef TUP
#define TUP

// extra
#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y)

#define _inc0(x) 1
#define _inc1(x) 2
#define _inc2(x) 3
#define _inc3(x) 4
#define _inc4(x) 5
#define _inc5(x) 6
#define _inc6(x) 7

#define _inc(x) _cat(_inc, x)(x)

// ... -> count(...) [max 6]
#define _foreach_counter(_0, _1, _2, _3, _4, _5, _6, x, ...) x
#define _foreach_chooser(...) _foreach_counter(__VA_ARGS__, 6, 5, 4, 3, 2, 1, 0)

// tuple declaration
#define __tuple_decl0(count, x, ...) x _cat(t, count);
#define __tuple_decl1(count, x, ...) x _cat(t, count); __tuple_decl0(_inc(count), __VA_ARGS__)
#define __tuple_decl2(count, x, ...) x _cat(t, count); __tuple_decl1(_inc(count), __VA_ARGS__)
#define __tuple_decl3(count, x, ...) x _cat(t, count); __tuple_decl2(_inc(count), __VA_ARGS__)
#define __tuple_decl4(count, x, ...) x _cat(t, count); __tuple_decl3(_inc(count), __VA_ARGS__)
#define __tuple_decl5(count, x, ...) x _cat(t, count); __tuple_decl4(_inc(count), __VA_ARGS__)
#define __tuple_decl6(count, x, ...) x _cat(t, count); __tuple_decl5(_inc(count), __VA_ARGS__)

#define _tuple_decl(...) _cat(__tuple_decl, _foreach_chooser(__VA_ARGS__))(0, __VA_ARGS__)


#define __tuple_name0(x, ...) x
#define __tuple_name1(x, ...) _cat(_cat(x, _), __tuple_name0(__VA_ARGS__))
#define __tuple_name2(x, ...) _cat(_cat(x, _), __tuple_name1(__VA_ARGS__))
#define __tuple_name3(x, ...) _cat(_cat(x, _), __tuple_name2(__VA_ARGS__))
#define __tuple_name4(x, ...) _cat(_cat(x, _), __tuple_name3(__VA_ARGS__))
#define __tuple_name5(x, ...) _cat(_cat(x, _), __tuple_name4(__VA_ARGS__))
#define __tuple_name6(x, ...) _cat(_cat(x, _), __tuple_name5(__VA_ARGS__))

#define tup(...) _cat(_tup_, _cat(__tuple_name, _foreach_chooser(__VA_ARGS__))(__VA_ARGS__))

#define TUPLE(args...)\
typedef struct _cat(_, tup(args)) {\
    _tuple_decl(args)\
} tup(args);

#endif