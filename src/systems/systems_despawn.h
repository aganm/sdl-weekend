#pragma once

#include "soa.h"
#include <primitive_types.h>

typedef struct soa_slot_t soa_slot_t;
typedef struct soa_position2 soa_position2;
typedef struct soa_destination2 soa_destination2;

void get_destination_reached_despawn_slots(
	const soa_position2 *e_position,
	const soa_destination2 *e_destination,
	const usize entity_count,
	const f32 reach_distance,
	soa_slot_t output[entity_count],
	usize *output_count);
