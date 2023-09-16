#pragma once

/**
 * @file
 * @brief Transform systems.
 */

#include <types/bundle.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_slot_t soa_slot_t;
typedef struct soa_position soa_position2;

f32v2 soa_get_one_position2(
	const soa_position2 *e_position,
	const soa_slot_t entity_slot);

void soa_change_one_position2(
	soa_position2 *e_position,
	const soa_slot_t entity_slot,
	const f32v2 new_position);

void soa_backup_position2(
	const soa_position2 *e_position,
	soa_position2 *e_old_position,
	const usize entity_count);

#ifdef __cplusplus
}
#endif
