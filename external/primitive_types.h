#ifndef TYPES_PRIMITIVE_H
#define TYPES_PRIMITIVE_H

/**
 * @file
 * @brief Primitive types.
 *
 * This file was written with the purpose of providing a final solution to C's
 * primitive type names. Between the ambiguously sized default C types and the
 * stdint.h sized types, it makes for inconsistent C code which makes it harder
 * to read than it has to. Use these types instead of the default C types and
 * or stdint.h/stddef.h types for increased C code readablity.
 *
 * To make code more consistent and to keep type names as readable as possible,
 * code written with the primitive types found in this file should use only
 * primitives found in this file and no other. They are designed such that they
 * make sense when used together and to remove all ambiguities of the default C
 * types. But to mix default C types with types in this file could possibly
 * cause even more confusion. If kept to a single style of type, the end result
 * should be increased readability of C code.
 *
 * The types in this file were heavily inspired by Zig, which also happen to be
 * very similar to Rust. I have been thinking about this problem for a while
 * and I have come to the realization that Zig (and Rust) have the best type
 * design, and so my design is also very similar to both of them.
 *
 * @see https://ziglang.org/documentation/master/#Primitive-Types
 * @see https://doc.rust-lang.org/rust-by-example/primitives.html
 *

Primitive type table (in the order that they are found in this file)
+--------------+------------------------------+-------------------------------------------+
|     Type     |         C Equivalent         |               Description                 |
+--------------+------------------------------+-------------------------------------------+
| int          | int                          | signed unspecified size integer           |
| bool         | bool                         | true or false                             |
| char         | char                         | one character in a string                 |
| cstr         | const char *                 | raw string type                           |
| isize        | intptr_t                     | signed pointer sized integer              |
| usize        | uintptr_t, size_t            | unsigned pointer sized integer            |
| f16store     | _Float16                     | 16-bit floating point (10-bit mantissa)   |
|              |                              | IEEE-754-2008 binary16 stored type        |
| f16live      | _Float16|float               | 16-bit floating point (10-bit mantissa)   |
|              |                              | IEEE-754-2008 binary16 live type          |
| f32          | float                        | 32-bit floating point (23-bit mantissa)   |
|              |                              | IEEE-754-2008 binary32                    |
| f64          | double                       | 64-bit floating point (52-bit mantissa)   |
|              |                              | IEEE-754-2008 binary64                    |
| i32          | int32_t                      | signed 32-bit integer                     |
| u32          | uint32_t                     | unsigned 32-bit integer                   |
| i64          | int64_t                      | signed 64-bit integer                     |
| u64          | uint64_t                     | unsigned 64-bit integer                   |
| i16          | int16_t                      | signed 16-bit integer                     |
| u16          | uint16_t                     | unsigned 16-bit integer                   |
| i8           | int8_t                       | signed 8-bit integer                      |
| u8           | uint8_t                      | unsigned 8-bit integer                    |
| f128         | _Float128                    | 128-bit floating point (112-bit mantissa) |
|              |                              | IEEE-754-2008 binary128                   |
| i128         | __int128                     | signed 128-bit integer                    |
| u128         | unsigned __int128            | unsigned 128-bit integer                  |
| u8bool       | uint8_t                      | 8-bit sized bool                          |
| u16bool      | uint16_t                     | 16-bit sized bool                         |
| u32bool      | uint32_t                     | 32-bit sized bool                         |
| u64bool      | uint64_t                     | 64-bit sized bool                         |
| u8slot       | struct {uint8_t}             | unsigned 8-bit slot                       |
| u16slot      | struct {uint16_t}            | unsigned 16-bit slot                      |
| u32slot      | struct {uint32_t}            | usigned 32-bit slot                       |
| u64slot      | struct {uint64_t}            | usigned 64-bit slot                       |
| f16seconds   | struct {_Float16|float}      | 16-bit floating point seconds             |
| f32seconds   | struct {float}               | 32-bit floating point seconds             |
| f64seconds   | struct {double}              | 64-bit floating point seconds             |
| f128seconds  | struct {_Float128}           | 128-bit floating point seconds            |
| f16minutes   | struct {_Float16|float}      | 16-bit floating point minutes             |
| f32minutes   | struct {float}               | 32-bit floating point minutes             |
| f64minutes   | struct {double}              | 64-bit floating point minutes             |
| f128minutes  | struct {_Float128}           | 128-bit floating point minutes            |
| f16hours     | struct {_Float16|float}      | 16-bit floating point hours               |
| f32hours     | struct {float}               | 32-bit floating point hours               |
| f64hours     | struct {double}              | 64-bit floating point hours               |
| f128hours    | struct {_Float128}           | 128-bit floating point hours              |
| f16meters    | struct {_Float16|float}      | 16-bit floating point meters              |
| f32meters    | struct {float}               | 32-bit floating point meters              |
| f64meters    | struct {double}              | 64-bit floating point meters              |
| f128meters   | struct {_Float128}           | 128-bit floating point meters             |
| f16sincos    | struct {_Float16|float,      | 16-bit floating point sincos              |
|              |         _Float16|float}      |                                           |
| f32sincos    | struct {float,float}         | 32-bit floating point sincos              |
| f64sincos    | struct {double,double}       | 64-bit floating point sincos              |
| f128sincos   | struct {_Float128,_Float128} | 128-bit floating point sincos             |
+--------------+------------------------------+-------------------------------------------+

 *
 */

#include <stdbool.h> /* bool */
#include <stddef.h>  /* size_t, intptr_t */
#include <stdint.h>  /* int32_t and family */

#ifdef __cplusplus
extern "C" {
#endif

/* Integer types with unspecified size. For when you need an integer and you
 * really don't care what size it is. No need to redefine it because it is a
 * standard keyword. If you need an unsigned integer, use one of the fixed size
 * ones such as u32. */

// typedef int int; /!< signed unspecified size integer */

/* Boolean type. For when you just need a generic boolean type, no need to
 * redefine it because stdbool.h already defines it perfectly. When you need
 * for the size of your bool to be explicit, use u8bool and family. */

// typedef bool bool; /!< generic boolean type */

/* Char type. One character in a string. No need to redefine it. Use this type
 * to extract each individual character from a string. */

// typedef char char; /!< character type */

/* C string type. 'const char *' looks out of place alongside the new primitive
 * names, so give it a name as well. It also makes working with this type
 * easier, especially when you need pointers to ponters of C strings. It keeps
 * the code lean and readable when it would otherwise be very hard to read. */

typedef const char *cstr;

/* Pointer size types. Other than being the pointer size types, these types are
 * the golden goose of loop indexing. If you would use a C 'int' as an index
 * type, this could go wrong in many ways because the int type is very ambiguous.
 * Its only spec is that it has to be greater or equal than short, and less or
 * equal than long. A proper generic for loop indexing type should be able to
 * handle any index possibly imaginable on the current system: usize it is.
 * Only use isize if you need your index to go in the negative, otherwise
 * always use usize. */

typedef size_t   usize;	/*!< unsigned pointer sized integer */
typedef intptr_t isize; /*!< signed pointer sized integer */

/* Primitive types with fixed sizes that have SIMD hardware support. You may
 * notice that these are not ordered in ascending order of the type size.
 * Instead, they are ordered in ascending order of SIMD hardware support on
 * x86-64. From very good support (32-bit floating point) to very poor (8-bit
 * integers).
 *
 * Using long long / unsigned long long for i64/u64 because lua-cdecl generates
 * a single 'long' with int64_t/uint64_t, which would be wrong on windows.. */

typedef uint16_t  f16store; /*!< 16-bit floating point (10-bit mantissa) IEEE-754-2008 binary16 stored type */
typedef float     f16live;  /*!< 16-bit floating point (10-bit mantissa) IEEE-754-2008 binary16 live stype */
typedef float     f32;      /*!< 32-bit floating point (23-bit mantissa) IEEE-754-2008 binary32 */
typedef double    f64;      /*!< 64-bit floating point (52-bit mantissa) IEEE-754-2008 binary64 */
typedef int32_t   i32;      /*!< signed 32-bit integer */
typedef uint32_t  u32;      /*!< unsigned 32-bit integer */
typedef int64_t   i64;      /*!< signed 64-bit integer */ // for lua-cdecl
typedef uint64_t  u64;      /*!< unsigned 64-bit integer */ // for lua-cdecl
typedef int16_t   i16;      /*!< signed 16-bit integer */
typedef uint16_t  u16;      /*!< unsigned 16-bit integer */
typedef int8_t    i8;       /*!< signed 8-bit integer */
typedef uint8_t   u8;       /*!< unsigned 8-bit integer */

/* Primitive types that have no SIMD support. Probably shouldn't use these, but
 * if you do need them, they are here. */

typedef long double       f128; /*!< 128-bit floating point (112-bit mantissa) IEEE-754-2008 binary128 */
#ifdef __SIZEOF_INT128__
typedef __int128          i128; /*!< signed 128-bit integer, nonstandard extension */
typedef unsigned __int128 u128; /*!< signed 128-bit integer, nonstandard extension */
#endif

/* Boolean types with fixed sizes. These are just integer primitives with
 * 'bool' appended to them. They have no real technical differences from the
 * primitive types. Use to communicate the intent of holding a boolean value.
 * These are not sorted by SIMD hardware support, but by size. You probably
 * want to favor smaller boolean types to save on memory even if the hardware
 * has better support for bigger types. */

typedef u8  u8bool;  /*!< unsigned 8-bit boolean */
typedef u16 u16bool; /*!< unsigned 16-bit boolean */
typedef u32 u32bool; /*!< unsigned 32-bit boolean */
typedef u64 u64bool; /*!< unsigned 64-bit boolean */

/* Index slot types. Instead of redefining slot types everywhere where needed,
 * reuse these. Put in a struct for extra type safety because this should never
 * be mixed up with the other primitives. Keep in mind that SIMD gathers work
 * with signed indices, therefore, a u32slot index value must remain within
 * INT32_MAX and a u64slot index value must remain within INT64_MAX to work
 * correctly with a SIMD gather, because larger values than that will overflow
 * in the negatives. You should probably have a way in your code to limit the
 * number of used indices to these maximum values if those indices are to be
 * used in gathers. */

typedef struct u8slot  { u8  idx; } u8slot;  /*!< unsigned 8-bit slotted index */
typedef struct u16slot { u16 idx; } u16slot; /*!< unsigned 16-bit slotted index */
typedef struct u32slot { u32 idx; } u32slot; /*!< unsigned 32-bit slotted index */
typedef struct u64slot { u64 idx; } u64slot; /*!< unsigned 64-bit slotted index */

/* Time types. Instead of redefining time types everywhere where needed, reuse
 * these. Keep in mind that the number of time units combined with all the
 * different types could lead to a massive amount of combinations. Just define
 * the most commonly used ones, add new ones if needed. */

typedef struct f16seconds  { f16live seconds; } f16seconds;  /*!< 16-bit floating point seconds */
typedef struct f32seconds  { f32     seconds; } f32seconds;  /*!< 32-bit floating point seconds */
typedef struct f64seconds  { f64     seconds; } f64seconds;  /*!< 64-bit floating point seconds */
typedef struct f128seconds { f128    seconds; } f128seconds; /*!< 128-bit floating point seconds */
typedef struct f16minutes  { f16live minutes; } f16minutes;  /*!< 16-bit floating point minutes */
typedef struct f32minutes  { f32     minutes; } f32minutes;  /*!< 32-bit floating point minutes */
typedef struct f64minutes  { f64     minutes; } f64minutes;  /*!< 64-bit floating point minutes */
typedef struct f128minutes { f128    minutes; } f128minutes; /*!< 128-bit floating point minutes */
typedef struct f16hours    { f16live hours;   } f16hours;    /*!< 16-bit floating point hours */
typedef struct f32hours    { f32     hours;   } f32hours;    /*!< 32-bit floating point hours */
typedef struct f64hours    { f64     hours;   } f64hours;    /*!< 64-bit floating point hours */
typedef struct f128hours   { f128    hours;   } f128hours;   /*!< 128-bit floating point hours */

/* Distance types. Instead of redefining distance types everywhere where
 * needed, reuse these. Keep in mind that the number of distance units combined
 * with all the different types could lead to a massive amount of combinations.
 * Just define the most commonly used ones, add new ones if needed. */

typedef struct f16meters  { f16live meters; } f16meters;  /*!< 16-bit floating point meters */
typedef struct f32meters  { f32     meters; } f32meters;  /*!< 32-bit floating point meters */
typedef struct f64meters  { f64     meters; } f64meters;  /*!< 64-bit floating point meters */
typedef struct f128meters { f128    meters; } f128meters; /*!< 128-bit floating point meters */

/* Miscellaneous math types. Instead of redefining common math types in every
 * single math library, reuse these. Do not shy away from adding more if
 * needed. These are handy because C does not easily let a function return an
 * anonymous struct in versions prior to C23. And I'd rather not depend on C23
 * when its support is so poor and probably will remain so for a very long
 * time. */

typedef struct f16sincos  { f16live sin, cos; } f16sincos;  /*!< 16-bit floating point sincos */
typedef struct f32sincos  { f32     sin, cos; } f32sincos;  /*!< 32-bit floating point sincos */
typedef struct f64sincos  { f64     sin, cos; } f64sincos;  /*!< 64-bit floating point sincos */
typedef struct f128sincos { f128    sin, cos; } f128sincos; /*!< 128-bit floating point sincos */

/* Bundle types. */

typedef union f32v2 {
	struct { f32 x, y; };
	struct { f32 w, h; };
	struct { f32 min, max; };
} f32v2;

typedef union i32v2 {
	struct { i32 x, y; };
	struct { i32 w, h; };
	struct { i32 min, max; };
} i32v2;

typedef struct f32rect {
	f32 x, y, w, h;
} f32rect;

typedef struct i32rect {
	i32 x, y, w, h;
} i32rect;

#ifdef __cplusplus
}
#endif

#endif // TYPES_PRIMITIVE_H
