#pragma once

#include <primitive_types.h>

typedef struct soa_slot_t soa_slot_t;
typedef struct soa_position2 soa_position2;
typedef struct soa_movement2 soa_movement2;
typedef struct soa_speed soa_speed;
typedef struct soa_velocity2 soa_velocity2;

void apply_movement(
	const soa_movement2 *e_movement,
	const soa_speed *e_speed,
	soa_velocity2 *e_velocity,
	const usize entity_count);

void follow_one_target(
	const soa_position2 *f_position,
	soa_movement2 *f_movement,
	const soa_speed *f_speed,
	const usize follower_count,
	const soa_position2 *t_position,
	const soa_slot_t target_slot);
