#ifndef MATH_HELPERS_H
#define MATH_HELPERS_H

/**
 * @file
 * @brief Math library.
 */

#include <types/bundle.h>
#include <types/primitive.h>

static inline f32   angle_between_points 	(f32v2 a, f32v2 b);
static inline f32   rad_to_deg 			(f32 rad);
static inline f32v2 tile_position_to_position 	(i32v2 tile_position, i32v2 tile_size);
static inline f32v2 rotate_about 		(f32v2 point, f32v2 origin, f32 rad);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <math.h>

static inline f32 angle_between_points(f32v2 a, f32v2 b)
{
	return atan2(a.y - b.y, a.x - b.x);
}

static inline f32 rad_to_deg(f32 rad)
{
	return rad / (M_PI * 2.f) * 360.f;
}

static inline f32v2 tile_position_to_position(i32v2 tile_position, i32v2 tile_size)
{
	return (f32v2){
		tile_position.x * tile_size.w,
		tile_position.y * tile_size.h,
	};
}

static inline f32v2 rotate_about(f32v2 point, f32v2 origin, f32 rad)
{
	const f32 sin = sinf(rad), cos = cosf(rad);
	const f32v2 local = {
		point.x - origin.x,
		point.y - origin.y,
	};
	const f32v2 rotated_local = {
		cos * local.x - sin * local.y,
		sin * local.x + cos * local.y,
	};
	const f32v2 rotated = {
		rotated_local.x + origin.x,
		rotated_local.y + origin.y,
	};
	return rotated;
}

#endif // MATH_HELPERS_H
