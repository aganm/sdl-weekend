#pragma once

#include <primitive_types.h>

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
