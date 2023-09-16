#pragma once

/**
 * @file
 * @brief Despawn systems.
 */

#include <types/primitive.h>
#include <soa.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_slot_t soa_slot_t;
typedef struct soa_position soa_position2;
typedef struct soa_destination2 soa_destination2;
typedef struct soa_health soa_health;

void soa_get_destination_reached_despawn_slots(
	const soa_position2 *e_position,
	const soa_destination2 *e_destination,
	const usize entity_count,
	const f32 reach_distance,
	soa_slot_t *output,
	usize *output_count);

void soa_get_dead_despawn_slots(
	const soa_health *e_health,
	const usize entity_count,
	soa_slot_t *output,
	usize *output_count);

#ifdef __cplusplus
}
#endif
