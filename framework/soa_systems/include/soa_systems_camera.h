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

void soa_apply_camera_2d(
	soa_position2 *e_position,
	const usize entity_count,
	const f32v2 camera);

#ifdef __cplusplus
}
#endif
