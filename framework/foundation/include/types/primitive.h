#pragma once

/**
 * @file
 * @brief Primitive types.
 *
 * To avoid a dependency on this file in other headers,
 * copy paste the parts that you need with this comment:
 * @primitives (grep tag): copy-pasted from types/primitives.h
 * Remember to update all the sites if I have to update the original.
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
+-----------------+------------------------------+------------------------------------------------+
|      Type       |         C Equivalent         |                  Description                   |
+-----------------+------------------------------+------------------------------------------------+
| int             | int                          | signed unspecified size integer                |
| bool            | bool                         | true or false                                  |
| char            | char                         | one character in a string                      |
| cstr            | const char *                 | raw string type                                |
| isize           | intptr_t                     | signed pointer sized integer                   |
| usize           | uintptr_t, size_t            | unsigned pointer sized integer                 |
| f16             | _Float16                     | 16-bit floating-point (10-bit mantissa)        |
|                 |                              | IEEE-754-2008 binary16, storage type           |
| h16             | _Float16|float               | 16-bit floating-point (10-bit mantissa)        |
|                 |                              | IEEE-754-2008 binary16, working type           |
| f32             | float                        | 32-bit floating-point (23-bit mantissa)        |
|                 |                              | IEEE-754-2008 binary32                         |
| f64             | double                       | 64-bit floating-point (52-bit mantissa)        |
|                 |                              | IEEE-754-2008 binary64                         |
| i32             | int32_t                      | signed 32-bit integer                          |
| u32             | uint32_t                     | unsigned 32-bit integer                        |
| i64             | int64_t                      | signed 64-bit integer                          |
| u64             | uint64_t                     | unsigned 64-bit integer                        |
| i16             | int16_t                      | signed 16-bit integer                          |
| u16             | uint16_t                     | unsigned 16-bit integer                        |
| i8              | int8_t                       | signed 8-bit integer                           |
| u8              | uint8_t                      | unsigned 8-bit integer                         |
| f128            | _Float128                    | 128-bit floating-point (112-bit mantissa)      |
|                 |                              | IEEE-754-2008 binary128                        |
| i128            | __int128                     | signed 128-bit integer                         |
| u128            | unsigned __int128            | unsigned 128-bit integer                       |
+-----------------+------------------------------+------------------------------------------------+
| u8bool          | uint8_t                      | 8-bit sized bool                               |
| u16bool         | uint16_t                     | 16-bit sized bool                              |
| u32bool         | uint32_t                     | 32-bit sized bool                              |
| u64bool         | uint64_t                     | 64-bit sized bool                              |
| u8slot          | struct {uint8_t}             | unsigned 8-bit slot                            |
| u16slot         | struct {uint16_t}            | unsigned 16-bit slot                           |
| u32slot         | struct {uint32_t}            | usigned 32-bit slot                            |
| u64slot         | struct {uint64_t}            | usigned 64-bit slot                            |
| h16seconds      | struct {_Float16|float}      | 16-bit floating-point seconds                  |
| f32seconds      | struct {float}               | 32-bit floating-point seconds                  |
| f64seconds      | struct {double}              | 64-bit floating-point seconds                  |
| f128seconds     | struct {_Float128}           | 128-bit floating-point seconds                 |
| h16minutes      | struct {_Float16|float}      | 16-bit floating-point minutes                  |
| f32minutes      | struct {float}               | 32-bit floating-point minutes                  |
| f64minutes      | struct {double}              | 64-bit floating-point minutes                  |
| f128minutes     | struct {_Float128}           | 128-bit floating-point minutes                 |
| h16hours        | struct {_Float16|float}      | 16-bit floating-point hours                    |
| f32hours        | struct {float}               | 32-bit floating-point hours                    |
| f64hours        | struct {double}              | 64-bit floating-point hours                    |
| f128hours       | struct {_Float128}           | 128-bit floating-point hours                   |
| h16millimeters  | struct {_Float16|float}      | 16-bit floating-point millimeters              |
| f32millimeters  | struct {float}               | 32-bit floating-point millimeters              |
| f64millimeters  | struct {double}              | 64-bit floating-point millimeters              |
| f128millimeters | struct {_Float128}           | 128-bit floating-point millimeters             |
| h16meters       | struct {_Float16|float}      | 16-bit floating-point meters                   |
| f32meters       | struct {float}               | 32-bit floating-point meters                   |
| f64meters       | struct {double}              | 64-bit floating-point meters                   |
| f128meters      | struct {_Float128}           | 128-bit floating-point meters                  |
| h16kilometers   | struct {_Float16|float}      | 16-bit floating-point kilometers               |
| f32kilometers   | struct {float}               | 32-bit floating-point kilometers               |
| f64kilometers   | struct {double}              | 64-bit floating-point kilometers               |
| f128kilometers  | struct {_Float128}           | 128-bit floating-point kilometers              |
| h16sincos       | struct {_Float16|float,      | 16-bit floating-point sincos                   |
|                 |         _Float16|float}      |                                                |
| f32sincos       | struct {float,float}         | 32-bit floating-point sincos                   |
| f64sincos       | struct {double,double}       | 64-bit floating-point sincos                   |
| f128sincos      | struct {_Float128,_Float128} | 128-bit floating-point sincos                  |
+-----------------+------------------------------+------------------------------------------------+

 *
 */

/**
 * Explanation for 16-bit floating-point, also known as 'half':
 *
 * Rationale: use 16-bit floating-point instead of 32-bit to save half the
 * memory bandwidth where 16-bit floating-point precision is sufficient.
 * 16-bit float has 1mm precision up to 1 meter, negative and position for a
 * total range of 2 meters. 1cm precision up to 20 meters. 1dm precision up to
 * 200 meters.  It's enough precision for many use cases out there. For
 * example, in BF3, they use a f32 position mixed with a f16 local transform.
 * The local transform (relative to the position) does not need a massive
 * amount of precision, and 1dm precision up to 200 meters is plenty. The
 * secret is to use f16s relative to another higher precision value, and f16
 * ends up being sufficiently precise for a lot of things.
 *
 * The 16-bit floating-point is special in that it does not have a single type,
 * but two: a 'storage' and a 'working' type called f16 and h16, respectively.
 * f16 stands for 16-bit floating-point and h16 stands for hybrid 16-bit
 * floating-point. The storage type is always 16-bit big, or 2 bytes. It is a
 * floating-point half. The working type is a typedef for whatever the current
 * hardware supports best.  Usually a 32-bit floating-point, or float. For
 * performance reasons, the working type will only be a 16-bit floating-point
 * if the target platform supports hardware accelerated fp16 (such as
 * AVX512-FP16).
 *
 * To use f16 types: use 'f16' when you need to store a 16-bit floating-point
 * in memory. Use 'h16' when you need to do calculations with it.  What this
 * means is you also have to convert from 'f16' to 'h16' when you need to do
 * work with it, and convert back from 'h16' to 'f16' when you want to store it
 * back in memory. See your friendly neighborhood math library to provide these
 * utilities.
 *
 * Note on determinism: because the f16 working type can be either a 32-bit
 * floating-point or a 16-bit floating-point depending on hardware support,
 * this type has no cross-platform determinism. Only use f16 type if fp16
 * precision is sufficient and determinism is not required. Or, if determinism
 * is required, then you could decide to always map h16 to f32 so that the
 * computation results of f16 is always the same everywhere, paying 2x the
 * computation cost on systems that support hardware fp16 at the benefit of
 * cross-platform determinism. I will have to add this functionality later if
 * needed. Right now I don't support any fp16 targets so it doesn't matter and
 * the implementation is incomplete and untested.
 *
 * Storage switch: f16 can also be switched to f32, use it for testing and
 * debugging if needed. If you want to switch f16 storage type to f32, define
 * F16_IS_F32 globally from your compiler.
 */

#ifndef TYPES_PRIMITIVE_H
#define TYPES_PRIMITIVE_H

#include <stdbool.h> /* bool */
#include <stddef.h>  /* size_t, intptr_t */
#include <stdint.h>  /* int32_t and family */
#include <warning.h> /* ENABLE_PADDED */

#ifdef __cplusplus
extern "C" {
#endif

ENABLE_PADDED

/* Integer types with unspecified size. For when you need an integer and you
 * really don't care what size it is. No need to redefine it because it is a
 * standard keyword. If you need an unsigned integer, use one of the fixed size
 * ones such as u32. */

// typedef int int; /*!< signed unspecified size integer */

/* Boolean type. For when you just need a generic boolean type, no need to
 * redefine it because stdbool.h already defines it perfectly. When you need
 * for the size of your bool to be explicit, use u8bool and family. */

// typedef bool bool; /*!< generic boolean type */

/* Char type. One character in a string. No need to redefine it. Use this type
 * to extract each individual character from a string. */

// typedef char char; /*!< character type */

/* C string type. 'const char *' looks out of place alongside the new primitive
 * names, so give it a name as well. It also makes working with this type
 * easier, especially when you need pointers to ponters of C strings. It keeps
 * the code lean and readable when it would otherwise be very hard to read. */

typedef const char *cstr; /*!< string type */

/* Pointer size types. Other than being the pointer size types, these types are
 * the golden goose of loop indexing. If you would use a C 'int' as an index
 * type, this could go wrong in many ways because the int type is ambiguous.
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
 * x86-64. From very good support (32-bit floating-point) to very poor (8-bit
 * integers). 16-bit floating-point does not generally have good hardware
 * support, but it will be mapped to a type that does: 32-bit floating-point if
 * 16-bit is not available, and 16-bit if it is available so that its
 * performance is always best on the given hardware.
 *
 * Define TYPES_PRIMITIVE_LUA to define i64/u64 to long long / unsigned long
 * long for for lua-cdecl because it otherwise generates a single 'long' with
 * int64_t/uint64_t, which is the wrong size on windows. */

#ifndef TYPES_PRIMITIVE_F16
#define TYPES_PRIMITIVE_F16
#ifndef F16_IS_F32
typedef uint16_t _f16raw;
#else
typedef float _f16raw;
#endif
typedef struct f16 { _f16raw _; } f16;
#endif
struct            f16;      /*!< 16-bit floating-point (10-bit mantissa) IEEE-754-2008 binary16, storage type */
typedef float     h16;      /*!< 16-bit floating-point (10-bit mantissa) IEEE-754-2008 binary16, working type */
typedef float     f32;      /*!< 32-bit floating-point (23-bit mantissa) IEEE-754-2008 binary32 */
typedef double    f64;      /*!< 64-bit floating-point (52-bit mantissa) IEEE-754-2008 binary64 */
typedef int32_t   i32;      /*!< signed 32-bit integer */
typedef uint32_t  u32;      /*!< unsigned 32-bit integer */
#ifndef TYPES_PRIMITIVE_LUA
typedef int64_t   i64;      /*!< signed 64-bit integer */
typedef uint64_t  u64;      /*!< unsigned 64-bit integer */
#else
typedef long long i64;      /*!< signed 64-bit integer */
typedef unsigned long long u64; /*!< unsigned 64-bit integer */
#endif
typedef int16_t   i16;      /*!< signed 16-bit integer */
typedef uint16_t  u16;      /*!< unsigned 16-bit integer */
typedef int8_t    i8;       /*!< signed 8-bit integer */
typedef uint8_t   u8;       /*!< unsigned 8-bit integer */

/* Primitive types that have no SIMD support. Probably shouldn't use these, but
 * if you do need them, they are here. */

typedef long double       f128; /*!< 128-bit floating-point (112-bit mantissa) IEEE-754-2008 binary128 */
#ifdef __SIZEOF_INT128__
typedef __int128          i128; /*!< signed 128-bit integer, nonstandard extension */
typedef unsigned __int128 u128; /*!< signed 128-bit integer, nonstandard extension */
#endif

/* Boolean types with fixed sizes. These are just integer primitives with
 * 'bool' appended to them. They have no real technical differences from the
 * primitive types. Use to communicate the intent of holding a boolean value.
 * You probably want to favor smaller boolean types to save on memory even if
 * the hardware has better support for bigger types. */

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
 * different primitives could lead to a massive amount of combinations. Just define
 * the most commonly used ones, add new ones if needed. */

typedef struct f16seconds  { f16  seconds; } f16seconds;  /*!< 16-bit floating-point seconds, storage type */
typedef struct h16seconds  { h16  seconds; } h16seconds;  /*!< 16-bit floating-point seconds, working type */
typedef struct f32seconds  { f32  seconds; } f32seconds;  /*!< 32-bit floating-point seconds */
typedef struct f64seconds  { f64  seconds; } f64seconds;  /*!< 64-bit floating-point seconds */
typedef struct f128seconds { f128 seconds; } f128seconds; /*!< 128-bit floating-point seconds */
typedef struct f16minutes  { f16  minutes; } f16minutes;  /*!< 16-bit floating-point minutes, storage type */
typedef struct h16minutes  { h16  minutes; } h16minutes;  /*!< 16-bit floating-point minutes, working type */
typedef struct f32minutes  { f32  minutes; } f32minutes;  /*!< 32-bit floating-point minutes */
typedef struct f64minutes  { f64  minutes; } f64minutes;  /*!< 64-bit floating-point minutes */
typedef struct f128minutes { f128 minutes; } f128minutes; /*!< 128-bit floating-point minutes */
typedef struct f16hours    { f16  hours;   } f16hours;    /*!< 16-bit floating-point hours, storage type */
typedef struct h16hours    { h16  hours;   } h16hours;    /*!< 16-bit floating-point hours, working type */
typedef struct f32hours    { f32  hours;   } f32hours;    /*!< 32-bit floating-point hours */
typedef struct f64hours    { f64  hours;   } f64hours;    /*!< 64-bit floating-point hours */
typedef struct f128hours   { f128 hours;   } f128hours;   /*!< 128-bit floating-point hours */

/* Distance types. Instead of redefining distance types everywhere where
 * needed, reuse these. Keep in mind that the number of distance units combined
 * with all the different primitives could lead to a massive amount of combinations.
 * Just define the most commonly used ones, add new ones if needed. */

typedef struct f16millimeters  { f16  millimeters; } f16millimeters;  /*!< 16-bit floating-point millimeters, storage type */
typedef struct h16millimeters  { h16  millimeters; } h16millimeters;  /*!< 16-bit floating-point millimeters, working type */
typedef struct f32millimeters  { f32  millimeters; } f32millimeters;  /*!< 32-bit floating-point millimeters */
typedef struct f64millimeters  { f64  millimeters; } f64millimeters;  /*!< 64-bit floating-point millimeters */
typedef struct f128millimeters { f128 millimeters; } f128millimeters; /*!< 128-bit floating-point millimeters */
typedef struct f16meters       { f16  meters;      } f16meters;       /*!< 16-bit floating-point meters, storage type */
typedef struct h16meters       { h16  meters;      } h16meters;       /*!< 16-bit floating-point meters, working type */
typedef struct f32meters       { f32  meters;      } f32meters;       /*!< 32-bit floating-point meters */
typedef struct f64meters       { f64  meters;      } f64meters;       /*!< 64-bit floating-point meters */
typedef struct f128meters      { f128 meters;      } f128meters;      /*!< 128-bit floating-point meters */
typedef struct f16kilometers   { f16  kilometers;  } f16kilometers;   /*!< 16-bit floating-point kilometers, storage type */
typedef struct h16kilometers   { h16  kilometers;  } h16kilometers;   /*!< 16-bit floating-point kilometers, working type */
typedef struct f32kilometers   { f32  kilometers;  } f32kilometers;   /*!< 32-bit floating-point kilometers */
typedef struct f64kilometers   { f64  kilometers;  } f64kilometers;   /*!< 64-bit floating-point kilometers */
typedef struct f128kilometers  { f128 kilometers;  } f128kilometers;  /*!< 128-bit floating-point kilometers */

/* Weight types. Instead of redefining weight types everywhere where
 * needed, reuse these. Keep in mind that the number of weight units combined
 * with all the different primitives could lead to a massive amount of combinations.
 * Just define the most commonly used ones, add new ones if needed. */

typedef struct f16milligrams  { f16  milligrams; } f16milligrams;  /*!< 16-bit floating-point milligrams, storage type */
typedef struct h16milligrams  { h16  milligrams; } h16milligrams;  /*!< 16-bit floating-point milligrams, working type */
typedef struct f32milligrams  { f32  milligrams; } f32milligrams;  /*!< 32-bit floating-point milligrams */
typedef struct f64milligrams  { f64  milligrams; } f64milligrams;  /*!< 64-bit floating-point milligrams */
typedef struct f128milligrams { f128 milligrams; } f128milligrams; /*!< 128-bit floating-point milligrams */
typedef struct f16grams       { f16  grams;      } f16grams;       /*!< 16-bit floating-point grams, storage type */
typedef struct h16grams       { h16  grams;      } h16grams;       /*!< 16-bit floating-point grams, working type */
typedef struct f32grams       { f32  grams;      } f32grams;       /*!< 32-bit floating-point grams */
typedef struct f64grams       { f64  grams;      } f64grams;       /*!< 64-bit floating-point grams */
typedef struct f128grams      { f128 grams;      } f128grams;      /*!< 128-bit floating-point grams */
typedef struct f16kilograms   { f16  kilograms;  } f16kilograms;   /*!< 16-bit floating-point kilograms, storage type */
typedef struct h16kilograms   { h16  kilograms;  } h16kilograms;   /*!< 16-bit floating-point kilograms, working type */
typedef struct f32kilograms   { f32  kilograms;  } f32kilograms;   /*!< 32-bit floating-point kilograms */
typedef struct f64kilograms   { f64  kilograms;  } f64kilograms;   /*!< 64-bit floating-point kilograms */
typedef struct f128kilograms  { f128 kilograms;  } f128kilograms;  /*!< 128-bit floating-point kilograms */

/* Miscellaneous math types. Instead of redefining common math types in every
 * single math library, reuse these. Do not shy away from adding more if
 * needed. These are handy because C does not easily let a function return an
 * anonymous struct in versions prior to C23. And I'd rather not depend on C23
 * when its support is so poor and probably will remain so for a long time. */

typedef struct f16divmod { f16 div; f16 quot; f16 rem; } f16divmod; /*!< 16-bit floating-point division-modulo, storage type */
typedef struct h16divmod { h16 div; h16 quot; h16 rem; } h16divmod; /*!< 16-bit floating-point division-modulo, working type */
typedef struct f32divmod { f32 div; f32 quot; f32 rem; } f32divmod; /*!< 32-bit floating-point division-modulo */
typedef struct f64divmod { f64 div; f64 quot; f64 rem; } f64divmod; /*!< 64-bit floating-point division-modulo */
typedef struct i8divmod  { i8  div; i8  quot; i8  rem; } i8divmod;  /*!< signed 8-bit division-modulo */
typedef struct i16divmod { i16 div; i16 quot; i16 rem; } i16divmod; /*!< signed 16-bit division-modulo */
typedef struct i32divmod { i32 div; i32 quot; i32 rem; } i32divmod; /*!< signed 32-bit division-modulo */
typedef struct i64divmod { i64 div; i64 quot; i64 rem; } i64divmod; /*!< signed 64-bit division-modulo */
typedef struct u8divmod  { u8  div; u8  quot; u8  rem; } u8divmod;  /*!< unsigned 8-but division-modulo */
typedef struct u16divmod { u16 div; u16 quot; u16 rem; } u16divmod; /*!< unsigned 16-but division-modulo */
typedef struct u32divmod { u32 div; u32 quot; u32 rem; } u32divmod; /*!< unsigned 32-but division-modulo */
typedef struct u64divmod { u64 div; u64 quot; u64 rem; } u64divmod; /*!< unsigned 64-but division-modulo */

typedef struct f16sincos  { f16  sin, cos; } f16sincos;  /*!< 16-bit floating-point sincos, storage type */
typedef struct h16sincos  { h16  sin, cos; } h16sincos;  /*!< 16-bit floating-point sincos, working type */
typedef struct f32sincos  { f32  sin, cos; } f32sincos;  /*!< 32-bit floating-point sincos */
typedef struct f64sincos  { f64  sin, cos; } f64sincos;  /*!< 64-bit floating-point sincos */
typedef struct f128sincos { f128 sin, cos; } f128sincos; /*!< 128-bit floating-point sincos */

#ifndef TYPES_PRIMITIVE_LWC
#define TYPES_PRIMITIVE_LWC
typedef struct lwc32 { i32 tile; f32 local; } lwc32; /*!< 32-bit large world coordinate */
typedef struct lwc64 { i64 tile; f64 local; } lwc64; /*!< 64-bit large world coordinate */
#endif

DISABLE_PADDED

#ifdef __cplusplus
}
#endif

#endif // TYPES_PRIMITIVE_H
