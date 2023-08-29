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

#endif // MATH_HELPERS_H
