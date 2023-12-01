#pragma once

/**
 * @file
 * @brief Math library.
 */

#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <types/bundle.h>

static inline f32v2 camera_center_offset  (f32v2 viewport, f32v2 center);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

f32v2 camera_center_offset(f32v2 viewport, f32v2 center)
{
	return (f32v2){
		center.x - viewport.width * 0.5f,
		center.y - viewport.height * 0.5f,
	};
}

#endif // CAMERA2D_H
