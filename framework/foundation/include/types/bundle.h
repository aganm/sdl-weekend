#pragma once

/**
 * @file
 * @brief Bundle types.
 */

#ifndef TYPES_BUNDLE_H
#define TYPES_BUNDLE_H

#include <assert.h>  /* assert() */
#include <stddef.h>  /* size_t, intptr_t */
#include <stdint.h>  /* int32_t and family */
#include <warning.h> /* ENABLE_PADDED */

#ifdef __cplusplus
extern "C" {
#endif

ENABLE_PADDED

/* @primitives (grep tag): copy-pasted from types/primitives.h */
#ifndef TYPES_PRIMITIVE_F16
#define TYPES_PRIMITIVE_F16
#ifndef F16_IS_F32
typedef uint16_t _f16raw;
#else
typedef float _f16raw;
#endif
typedef struct f16 { _f16raw _; } f16;
#endif
struct            f16;      /*!< 16-bit floating-point (10-bit mantissa) IEEE-754-2008 binary16 storage type */
typedef float     h16;      /*!< 16-bit floating-point (10-bit mantissa) IEEE-754-2008 binary16 working type */
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
typedef long double       f128; /*!< 128-bit floating-point (112-bit mantissa) IEEE-754-2008 binary128 */
#ifdef __SIZEOF_INT128__
typedef __int128          i128; /*!< signed 128-bit integer, nonstandard extension */
typedef unsigned __int128 u128; /*!< signed 128-bit integer, nonstandard extension */
#endif
#ifndef TYPES_PRIMITIVE_LWC
#define TYPES_PRIMITIVE_LWC
typedef struct lwc32 { i32 tile; f32 local; } lwc32; /*!< 32-bit large world coordinate */
typedef struct lwc64 { i64 tile; f64 local; } lwc64; /*!< 64-bit large world coordinate */
#endif

/* Utility macros to expand bundle type members. */

#define UNPACK2(var) (var).raw[0], (var).raw[1]
#define UNPACK3(var) (var).raw[0], (var).raw[1], (var).raw[2]
#define UNPACK4(var) (var).raw[0], (var).raw[1], (var).raw[2], (var).raw[3]

/* Swizzle macros. */

#define BUNDLE_SWIZZLE_VECTOR_2(typename, type) \
	struct { type x, y; }; \
	\
	struct { type u, v; }; \
	\
	struct { type min, max; }; \
	\
	struct { type width, height; }; \
	\
	struct { type left, right; }; \
	\
	type raw[2];

#define BUNDLE_SWIZZLE_VECTOR_3(typename, type) \
	struct { type x, y, z; }; \
	struct { typename##v2 xy; type _pad0; }; \
	struct { type _pad1; typename##v2 yz; }; \
	\
	struct { type u, v, w; }; \
	struct { typename##v2 uv; type _pad2; }; \
	struct { type _pad3; typename##v2 vw; }; \
	\
	struct { type r, g, b; }; \
	\
	struct { type width, height, depth; }; \
	\
	type raw[3];

#define BUNDLE_SWIZZLE_VECTOR_4(typename, type) \
	struct { type x, y, z, w; }; \
	struct { typename##v2 xy, zw; }; \
	struct { type _pad0; typename##v2 yz; type _pad1; }; \
	struct { typename##v3 xyz; type _pad2; }; \
	\
	struct { type x1, y1, x2, y2; }; \
	struct { typename##v2 xy1, xy2; }; \
	\
	struct { type r, g, b, a; }; \
	struct { typename##v3 rgb; type _pad3; }; \
	\
	type raw[4];

#define BUNDLE_SWIZZLE_MATRIX_2X2(typename, type) \
	struct { \
		type x1, y1; \
		type x2, y2; \
	}; \
	struct { \
		type m00, m01; \
		type m10, m11; \
	}; \
	type raw[4]; \
	type m[2][2];

#define BUNDLE_SWIZZLE_MATRIX_2X3(typename, type) \
	struct { \
		type x1, y1, z1; \
		type x2, y2, z2; \
	}; \
	struct { \
		type m00, m01, m02; \
		type m10, m11, m12; \
	}; \
	type raw[6]; \
	type m[2][3];

#define BUNDLE_SWIZZLE_MATRIX_2X4(typename, type) \
	struct { \
		type x1, y1, z1, w1; \
		type x2, y2, z2, w2; \
	}; \
	struct { \
		type m00, m01, m02, m03; \
		type m10, m11, m12, m13; \
	}; \
	type raw[8]; \
	type m[2][4];

#define BUNDLE_SWIZZLE_MATRIX_3X2(typename, type) \
	struct { \
		type cx1, cy1; \
		type cx2, cy2; \
		type cx3, cy3; \
	}; \
	struct { \
		type m00, m01; \
		type m10, m11; \
		type m20, m21; \
	}; \
	type raw[6]; \
	type m[3][2];

#define BUNDLE_SWIZZLE_MATRIX_3X3(typename, type) \
	struct { \
		type x1, y1, z1; \
		type x2, y2, z2; \
		type x3, y3, z3; \
	}; \
	struct { \
		type m00, m01, m02; \
		type m10, m11, m12; \
		type m20, m21, m22; \
	}; \
	type raw[9]; \
	type m[3][3];

#define BUNDLE_SWIZZLE_MATRIX_3X4(typename, type) \
	struct { \
		type x1, y1, z1, w1; \
		type x2, y2, z2, w2; \
		type x3, y3, z3, w3; \
	}; \
	struct { \
		type m00, m01, m02, m03; \
		type m10, m11, m12, m13; \
		type m20, m21, m22, m23; \
	}; \
	type raw[12]; \
	type m[3][4];

#define BUNDLE_SWIZZLE_MATRIX_4X2(typename, type) \
	struct { \
		type x1, y1; \
		type x2, y2; \
		type x3, y3; \
		type x4, y4; \
	}; \
	struct { \
		type m00, m01; \
		type m10, m11; \
		type m20, m21; \
		type m30, m31; \
	}; \
	type raw[8]; \
	type m[4][2];

#define BUNDLE_SWIZZLE_MATRIX_4X3(typename, type) \
	struct { \
		type x1, y1, z1; \
		type x2, y2, z2; \
		type x3, y3, z3; \
		type x4, y4, z4; \
	}; \
	struct { \
		type m00, m01, m02; \
		type m10, m11, m12; \
		type m20, m21, m22; \
		type m30, m31, m32; \
	}; \
	type raw[12]; \
	type m[4][3];

#define BUNDLE_SWIZZLE_MATRIX_4X4(typename, type) \
	struct { \
		type x1, y1, z1, w1; \
		type x2, y2, z2, w2; \
		type x3, y3, z3, w3; \
		type x4, y4, z4, w4; \
	}; \
	struct { \
		type m00, m01, m02, m03; \
		type m10, m11, m12, m13; \
		type m20, m21, m22, m23; \
		type m30, m31, m32, m33; \
	}; \
	type raw[16]; \
	type m[4][4];

#define BUNDLE_SWIZZLE_RECT_4(typename, type) \
	struct { type x, y, w, h; }; \
	struct { typename##v2 xy, wh; }; \
	\
	struct { type _pad0, _pad1, width, height; }; \
	\
	type raw[4];

#define BUNDLE_SWIZZLE_QUAT(typename, type) \
	struct { type x, y, z, w; }; \
	struct { typename##v3 xyz; type _pad0; }; \
	struct { typename##v4 xyzw; }; \
	type raw[4];

#define BUNDLE_SWIZZLE_AABB_2(typename, type) \
	struct { \
		typename##v2 min; \
		typename##v2 max; \
	}; \
	type raw[4];

#define BUNDLE_SWIZZLE_AABB_3(typename, type) \
	struct { \
		typename##v3 min; \
		typename##v3 max; \
	}; \
	type raw[6];

#define BUNDLE_SWIZZLE_AABB_4(typename, type) \
	struct { \
		typename##v4 min; \
		typename##v4 max; \
	}; \
	type raw[8];

#define BUNDLE_SWIZZLE_RAY_2(typename, type) \
	struct { \
		typename##v2 origin; \
		typename##v2 direction; \
	}; \
	type raw[4];

#define BUNDLE_SWIZZLE_RAY_3(typename, type) \
	struct { \
		typename##v3 origin; \
		typename##v3 direction; \
	}; \
	type raw[6];

#define BUNDLE_SWIZZLE_RAY_4(typename, type) \
	struct { \
		typename##v4 origin; \
		typename##v4 direction; \
	}; \
	type raw[8];

/* Vector types. */

typedef struct f16v2  { union { BUNDLE_SWIZZLE_VECTOR_2(f16, f16); }; } f16v2;
typedef struct f16v3  { union { BUNDLE_SWIZZLE_VECTOR_3(f16, f16); }; } f16v3;
typedef struct f16v4  { union { BUNDLE_SWIZZLE_VECTOR_4(f16, f16); }; } f16v4;
typedef struct h16v2  { union { BUNDLE_SWIZZLE_VECTOR_2(h16, h16); }; } h16v2;
typedef struct h16v3  { union { BUNDLE_SWIZZLE_VECTOR_3(h16, h16); }; } h16v3;
typedef struct h16v4  { union { BUNDLE_SWIZZLE_VECTOR_4(h16, h16); }; } h16v4;
typedef struct f32v2  { union { BUNDLE_SWIZZLE_VECTOR_2(f32, f32); }; } f32v2;
typedef struct f32v3  { union { BUNDLE_SWIZZLE_VECTOR_3(f32, f32); }; } f32v3;
typedef struct f32v4  { union { BUNDLE_SWIZZLE_VECTOR_4(f32, f32); }; } f32v4;
typedef struct f64v2  { union { BUNDLE_SWIZZLE_VECTOR_2(f64, f64); }; } f64v2;
typedef struct f64v3  { union { BUNDLE_SWIZZLE_VECTOR_3(f64, f64); }; } f64v3;
typedef struct f64v4  { union { BUNDLE_SWIZZLE_VECTOR_4(f64, f64); }; } f64v4;
typedef struct i32v2  { union { BUNDLE_SWIZZLE_VECTOR_2(i32, i32); }; } i32v2;
typedef struct i32v3  { union { BUNDLE_SWIZZLE_VECTOR_3(i32, i32); }; } i32v3;
typedef struct i32v4  { union { BUNDLE_SWIZZLE_VECTOR_4(i32, i32); }; } i32v4;
typedef struct u32v2  { union { BUNDLE_SWIZZLE_VECTOR_2(u32, u32); }; } u32v2;
typedef struct u32v3  { union { BUNDLE_SWIZZLE_VECTOR_3(u32, u32); }; } u32v3;
typedef struct u32v4  { union { BUNDLE_SWIZZLE_VECTOR_4(u32, u32); }; } u32v4;
typedef struct i64v2  { union { BUNDLE_SWIZZLE_VECTOR_2(i64, i64); }; } i64v2;
typedef struct i64v3  { union { BUNDLE_SWIZZLE_VECTOR_3(i64, i64); }; } i64v3;
typedef struct i64v4  { union { BUNDLE_SWIZZLE_VECTOR_4(i64, i64); }; } i64v4;
typedef struct u64v2  { union { BUNDLE_SWIZZLE_VECTOR_2(u64, u64); }; } u64v2;
typedef struct u64v3  { union { BUNDLE_SWIZZLE_VECTOR_3(u64, u64); }; } u64v3;
typedef struct u64v4  { union { BUNDLE_SWIZZLE_VECTOR_4(u64, u64); }; } u64v4;
typedef struct i16v2  { union { BUNDLE_SWIZZLE_VECTOR_2(i16, i16); }; } i16v2;
typedef struct i16v3  { union { BUNDLE_SWIZZLE_VECTOR_3(i16, i16); }; } i16v3;
typedef struct i16v4  { union { BUNDLE_SWIZZLE_VECTOR_4(i16, i16); }; } i16v4;
typedef struct u16v2  { union { BUNDLE_SWIZZLE_VECTOR_2(u16, u16); }; } u16v2;
typedef struct u16v3  { union { BUNDLE_SWIZZLE_VECTOR_3(u16, u16); }; } u16v3;
typedef struct u16v4  { union { BUNDLE_SWIZZLE_VECTOR_4(u16, u16); }; } u16v4;
typedef struct i8v2   { union { BUNDLE_SWIZZLE_VECTOR_2(i8, i8); }; } i8v2;
typedef struct i8v3   { union { BUNDLE_SWIZZLE_VECTOR_3(i8, i8); }; } i8v3;
typedef struct i8v4   { union { BUNDLE_SWIZZLE_VECTOR_4(i8, i8); u32 u32; }; } i8v4;
typedef struct u8v2   { union { BUNDLE_SWIZZLE_VECTOR_2(u8, u8); }; } u8v2;
typedef struct u8v3   { union { BUNDLE_SWIZZLE_VECTOR_3(u8, u8); }; } u8v3;
typedef struct u8v4   { union { BUNDLE_SWIZZLE_VECTOR_4(u8, u8); u32 u32; }; } u8v4;
typedef struct f128v2 { union { BUNDLE_SWIZZLE_VECTOR_2(f128, f128); }; } f128v2;
typedef struct f128v3 { union { BUNDLE_SWIZZLE_VECTOR_3(f128, f128); }; } f128v3;
typedef struct f128v4 { union { BUNDLE_SWIZZLE_VECTOR_4(f128, f128); }; } f128v4;
#ifdef __SIZEOF_INT128__
typedef struct i128v2 { union { BUNDLE_SWIZZLE_VECTOR_2(i128, i128); }; } i128v2;
typedef struct i128v3 { union { BUNDLE_SWIZZLE_VECTOR_3(i128, i128); }; } i128v3;
typedef struct i128v4 { union { BUNDLE_SWIZZLE_VECTOR_4(i128, i128); }; } i128v4;
typedef struct u128v2 { union { BUNDLE_SWIZZLE_VECTOR_2(u128, u128); }; } u128v2;
typedef struct u128v3 { union { BUNDLE_SWIZZLE_VECTOR_3(u128, u128); }; } u128v3;
typedef struct u128v4 { union { BUNDLE_SWIZZLE_VECTOR_4(u128, u128); }; } u128v4;
#endif
typedef struct lwc32v2 { union { BUNDLE_SWIZZLE_VECTOR_2(lwc32, lwc32); }; } lwc32v2;
typedef struct lwc32v3 { union { BUNDLE_SWIZZLE_VECTOR_3(lwc32, lwc32); }; } lwc32v3;
typedef struct lwc32v4 { union { BUNDLE_SWIZZLE_VECTOR_4(lwc32, lwc32); }; } lwc32v4;

/* Matrix types (Column Major). */

typedef struct f16m2x2  { union { BUNDLE_SWIZZLE_MATRIX_2X2(f16, f16); }; } f16m2x2;
typedef struct f16m2x3  { union { BUNDLE_SWIZZLE_MATRIX_2X3(f16, f16); }; } f16m2x3;
typedef struct f16m2x4  { union { BUNDLE_SWIZZLE_MATRIX_2X4(f16, f16); }; } f16m2x4;
typedef struct f16m3x2  { union { BUNDLE_SWIZZLE_MATRIX_3X2(f16, f16); }; } f16m3x2;
typedef struct f16m3x3  { union { BUNDLE_SWIZZLE_MATRIX_3X3(f16, f16); }; } f16m3x3;
typedef struct f16m3x4  { union { BUNDLE_SWIZZLE_MATRIX_3X4(f16, f16); }; } f16m3x4;
typedef struct f16m4x2  { union { BUNDLE_SWIZZLE_MATRIX_4X2(f16, f16); }; } f16m4x2;
typedef struct f16m4x3  { union { BUNDLE_SWIZZLE_MATRIX_4X3(f16, f16); }; } f16m4x3;
typedef struct f16m4x4  { union { BUNDLE_SWIZZLE_MATRIX_4X4(f16, f16); }; } f16m4x4;
typedef struct h16m2x2  { union { BUNDLE_SWIZZLE_MATRIX_2X2(h16, h16); }; } h16m2x2;
typedef struct h16m2x3  { union { BUNDLE_SWIZZLE_MATRIX_2X3(h16, h16); }; } h16m2x3;
typedef struct h16m2x4  { union { BUNDLE_SWIZZLE_MATRIX_2X4(h16, h16); }; } h16m2x4;
typedef struct h16m3x2  { union { BUNDLE_SWIZZLE_MATRIX_3X2(h16, h16); }; } h16m3x2;
typedef struct h16m3x3  { union { BUNDLE_SWIZZLE_MATRIX_3X3(h16, h16); }; } h16m3x3;
typedef struct h16m3x4  { union { BUNDLE_SWIZZLE_MATRIX_3X4(h16, h16); }; } h16m3x4;
typedef struct h16m4x2  { union { BUNDLE_SWIZZLE_MATRIX_4X2(h16, h16); }; } h16m4x2;
typedef struct h16m4x3  { union { BUNDLE_SWIZZLE_MATRIX_4X3(h16, h16); }; } h16m4x3;
typedef struct h16m4x4  { union { BUNDLE_SWIZZLE_MATRIX_4X4(h16, h16); }; } h16m4x4;
typedef struct f32m2x2  { union { BUNDLE_SWIZZLE_MATRIX_2X2(f32, f32); }; } f32m2x2;
typedef struct f32m2x3  { union { BUNDLE_SWIZZLE_MATRIX_2X3(f32, f32); }; } f32m2x3;
typedef struct f32m2x4  { union { BUNDLE_SWIZZLE_MATRIX_2X4(f32, f32); }; } f32m2x4;
typedef struct f32m3x2  { union { BUNDLE_SWIZZLE_MATRIX_3X2(f32, f32); }; } f32m3x2;
typedef struct f32m3x3  { union { BUNDLE_SWIZZLE_MATRIX_3X3(f32, f32); }; } f32m3x3;
typedef struct f32m3x4  { union { BUNDLE_SWIZZLE_MATRIX_3X4(f32, f32); }; } f32m3x4;
typedef struct f32m4x2  { union { BUNDLE_SWIZZLE_MATRIX_4X2(f32, f32); }; } f32m4x2;
typedef struct f32m4x3  { union { BUNDLE_SWIZZLE_MATRIX_4X3(f32, f32); }; } f32m4x3;
typedef struct f32m4x4  { union { BUNDLE_SWIZZLE_MATRIX_4X4(f32, f32); }; } f32m4x4;
typedef struct f64m2x2  { union { BUNDLE_SWIZZLE_MATRIX_2X2(f64, f64); }; } f64m2x2;
typedef struct f64m2x3  { union { BUNDLE_SWIZZLE_MATRIX_2X3(f64, f64); }; } f64m2x3;
typedef struct f64m2x4  { union { BUNDLE_SWIZZLE_MATRIX_2X4(f64, f64); }; } f64m2x4;
typedef struct f64m3x2  { union { BUNDLE_SWIZZLE_MATRIX_3X2(f64, f64); }; } f64m3x2;
typedef struct f64m3x3  { union { BUNDLE_SWIZZLE_MATRIX_3X3(f64, f64); }; } f64m3x3;
typedef struct f64m3x4  { union { BUNDLE_SWIZZLE_MATRIX_3X4(f64, f64); }; } f64m3x4;
typedef struct f64m4x2  { union { BUNDLE_SWIZZLE_MATRIX_4X2(f64, f64); }; } f64m4x2;
typedef struct f64m4x3  { union { BUNDLE_SWIZZLE_MATRIX_4X3(f64, f64); }; } f64m4x3;
typedef struct f64m4x4  { union { BUNDLE_SWIZZLE_MATRIX_4X4(f64, f64); }; } f64m4x4;
typedef struct f128m2x2 { union { BUNDLE_SWIZZLE_MATRIX_2X2(f128, f128); }; } f128m2x2;
typedef struct f128m2x3 { union { BUNDLE_SWIZZLE_MATRIX_2X3(f128, f128); }; } f128m2x3;
typedef struct f128m2x4 { union { BUNDLE_SWIZZLE_MATRIX_2X4(f128, f128); }; } f128m2x4;
typedef struct f128m3x2 { union { BUNDLE_SWIZZLE_MATRIX_3X2(f128, f128); }; } f128m3x2;
typedef struct f128m3x3 { union { BUNDLE_SWIZZLE_MATRIX_3X3(f128, f128); }; } f128m3x3;
typedef struct f128m3x4 { union { BUNDLE_SWIZZLE_MATRIX_3X4(f128, f128); }; } f128m3x4;
typedef struct f128m4x2 { union { BUNDLE_SWIZZLE_MATRIX_4X2(f128, f128); }; } f128m4x2;
typedef struct f128m4x3 { union { BUNDLE_SWIZZLE_MATRIX_4X3(f128, f128); }; } f128m4x3;
typedef struct f128m4x4 { union { BUNDLE_SWIZZLE_MATRIX_4X4(f128, f128); }; } f128m4x4;

/* Rectangle types. */

typedef struct f16rect  { union { BUNDLE_SWIZZLE_RECT_4(f16, f16); }; } f16rect;
typedef struct h16rect  { union { BUNDLE_SWIZZLE_RECT_4(h16, h16); }; } h16rect;
typedef struct f32rect  { union { BUNDLE_SWIZZLE_RECT_4(f32, f32); }; } f32rect;
typedef struct f64rect  { union { BUNDLE_SWIZZLE_RECT_4(f64, f64); }; } f64rect;
typedef struct i32rect  { union { BUNDLE_SWIZZLE_RECT_4(i32, i32); }; } i32rect;
typedef struct u32rect  { union { BUNDLE_SWIZZLE_RECT_4(u32, u32); }; } u32rect;
typedef struct i64rect  { union { BUNDLE_SWIZZLE_RECT_4(i64, i64); }; } i64rect;
typedef struct u64rect  { union { BUNDLE_SWIZZLE_RECT_4(u64, u64); }; } u64rect;
typedef struct i16rect  { union { BUNDLE_SWIZZLE_RECT_4(i16, i16); }; } i16rect;
typedef struct u16rect  { union { BUNDLE_SWIZZLE_RECT_4(u16, u16); }; } u16rect;
typedef struct i8rect   { union { BUNDLE_SWIZZLE_RECT_4(i8, i8); u32 u32; }; } i8rect;
typedef struct u8rect   { union { BUNDLE_SWIZZLE_RECT_4(u8, u8); u32 u32; }; } u8rect;
typedef struct f128rect { union { BUNDLE_SWIZZLE_RECT_4(f128, f128); }; } f128rect;
#ifdef __SIZEOF_INT128__
typedef struct i128rect { union { BUNDLE_SWIZZLE_RECT_4(i128, i128); }; } i128rect;
typedef struct u128rect { union { BUNDLE_SWIZZLE_RECT_4(u128, u128); }; } u128rect;
#endif

/* Quaternion types. */

typedef struct f16quat  { union { BUNDLE_SWIZZLE_QUAT(f16, f16); }; } f16quat;
typedef struct h16quat  { union { BUNDLE_SWIZZLE_QUAT(h16, h16); }; } h16quat;
typedef struct f32quat  { union { BUNDLE_SWIZZLE_QUAT(f32, f32); }; } f32quat;
typedef struct f64quat  { union { BUNDLE_SWIZZLE_QUAT(f64, f64); }; } f64quat;
typedef struct f128quat { union { BUNDLE_SWIZZLE_QUAT(f128, f128); }; } f128quat;

/* Axis-aligned bounding box types. */

typedef struct f16aabb2  { union { BUNDLE_SWIZZLE_AABB_2(f16, f16); }; } f16aabb2;
typedef struct f16aabb3  { union { BUNDLE_SWIZZLE_AABB_3(f16, f16); }; } f16aabb3;
typedef struct f16aabb4  { union { BUNDLE_SWIZZLE_AABB_4(f16, f16); }; } f16aabb4;
typedef struct h16aabb2  { union { BUNDLE_SWIZZLE_AABB_2(h16, h16); }; } h16aabb2;
typedef struct h16aabb3  { union { BUNDLE_SWIZZLE_AABB_3(h16, h16); }; } h16aabb3;
typedef struct h16aabb4  { union { BUNDLE_SWIZZLE_AABB_4(h16, h16); }; } h16aabb4;
typedef struct f32aabb2  { union { BUNDLE_SWIZZLE_AABB_2(f32, f32); }; } f32aabb2;
typedef struct f32aabb3  { union { BUNDLE_SWIZZLE_AABB_3(f32, f32); }; } f32aabb3;
typedef struct f32aabb4  { union { BUNDLE_SWIZZLE_AABB_4(f32, f32); }; } f32aabb4;
typedef struct f64aabb2  { union { BUNDLE_SWIZZLE_AABB_2(f64, f64); }; } f64aabb2;
typedef struct f64aabb3  { union { BUNDLE_SWIZZLE_AABB_3(f64, f64); }; } f64aabb3;
typedef struct f64aabb4  { union { BUNDLE_SWIZZLE_AABB_4(f64, f64); }; } f64aabb4;
typedef struct f128aabb2 { union { BUNDLE_SWIZZLE_AABB_2(f128, f128); }; } f128aabb2;
typedef struct f128aabb3 { union { BUNDLE_SWIZZLE_AABB_3(f128, f128); }; } f128aabb3;
typedef struct f128aabb4 { union { BUNDLE_SWIZZLE_AABB_4(f128, f128); }; } f128aabb4;

/* Ray types. */

typedef struct f16ray2  { union { BUNDLE_SWIZZLE_RAY_2(f16, f16); }; } f16ray2;
typedef struct f16ray3  { union { BUNDLE_SWIZZLE_RAY_3(f16, f16); }; } f16ray3;
typedef struct f16ray4  { union { BUNDLE_SWIZZLE_RAY_4(f16, f16); }; } f16ray4;
typedef struct h16ray2  { union { BUNDLE_SWIZZLE_RAY_2(h16, h16); }; } h16ray2;
typedef struct h16ray3  { union { BUNDLE_SWIZZLE_RAY_3(h16, h16); }; } h16ray3;
typedef struct h16ray4  { union { BUNDLE_SWIZZLE_RAY_4(h16, h16); }; } h16ray4;
typedef struct f32ray2  { union { BUNDLE_SWIZZLE_RAY_2(f32, f32); }; } f32ray2;
typedef struct f32ray3  { union { BUNDLE_SWIZZLE_RAY_3(f32, f32); }; } f32ray3;
typedef struct f32ray4  { union { BUNDLE_SWIZZLE_RAY_4(f32, f32); }; } f32ray4;
typedef struct f64ray2  { union { BUNDLE_SWIZZLE_RAY_2(f64, f64); }; } f64ray2;
typedef struct f64ray3  { union { BUNDLE_SWIZZLE_RAY_3(f64, f64); }; } f64ray3;
typedef struct f64ray4  { union { BUNDLE_SWIZZLE_RAY_4(f64, f64); }; } f64ray4;
typedef struct f128ray2 { union { BUNDLE_SWIZZLE_RAY_2(f128, f128); }; } f128ray2;
typedef struct f128ray3 { union { BUNDLE_SWIZZLE_RAY_3(f128, f128); }; } f128ray3;
typedef struct f128ray4 { union { BUNDLE_SWIZZLE_RAY_4(f128, f128); }; } f128ray4;

DISABLE_PADDED

#ifdef __cplusplus
}
#endif

#endif // TYPES_BUNDLE_H
