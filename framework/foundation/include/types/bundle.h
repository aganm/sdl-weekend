#ifndef TYPES_BUNDLE_H
#define TYPES_BUNDLE_H

/**
 * @file
 * @brief Bundle types.
 */

#include "primitive.h"

/* Bundle types. */

typedef union f32v2 {
	struct { f32 x, y; };
	struct { f32 w, h; };
	struct { f32 min, max; };
} f32v2;

typedef union f32v3 {
	struct { f32 x, y, z; };
} f32v3;

typedef union i32v2 {
	struct { i32 x, y; };
	struct { i32 w, h; };
	struct { i32 min, max; };
} i32v2;

typedef union i32v3 {
	struct { i32 x, y, z; };
} i32v3;

typedef union u8v4 {
	struct { u8 x, y, w, h; };
	struct { u8 r, g, b, a; };
} u8v4;

typedef struct f32rect {
	f32 x, y, w, h;
} f32rect;

typedef struct i32rect {
	i32 x, y, w, h;
} i32rect;

#endif // TYPES_BUNDLE_H
