#pragma once

/**
 * @file
 * @brief Physics systems.
 */

#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_position2 soa_position2;
typedef struct soa_velocity2 soa_velocity2;

void reset_velocity(
	soa_velocity2 *e_velocity,
	const usize entity_count);

void apply_forwards_velocity(
	soa_position2 *e_position,
	const soa_velocity2 *e_velocity,
	const usize entity_count,
	const f32seconds dt);

#ifdef __cplusplus
}
#endif
