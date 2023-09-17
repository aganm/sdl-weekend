#pragma once

/**
 * @file
 * @brief Camera systems.
 */

#include <types/bundle.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_position soa_position2;
typedef struct soa_position soa_position3;

void soa_apply_camera_2d(
	soa_position2 *e_position,
	const usize entity_count,
	f32v2 camera);

void soa_apply_camera_3d(
	soa_position3 *e_position,
	const usize entity_count,
	f32v3 camera,
	f32v2 viewport);

#ifdef __cplusplus
}
#endif
