#pragma once

/**
 * @file
 * @brief Bullet systems.
 */

#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_slot_t soa_slot_t;
typedef struct soa_position soa_position2;
typedef struct soa_size soa_size2;
typedef struct soa_health soa_health;
typedef struct soa_damage soa_damage;
typedef struct soa_destination soa_destination2;

void soa_detect_bullet_collisions_with_something(
	const soa_position2 *s_position,
	const soa_size2 *s_size,
	const usize something_count,
	const soa_position2 *b_position,
	const usize bullet_count,
	soa_slot_t *out_collided_somethings,
	soa_slot_t *out_collided_bullets,
	usize *out_collided_count);

void soa_bullet_damages_something(
	soa_health *s_health,
	soa_damage *b_damage,
	const soa_slot_t *something_slots,
	const soa_slot_t *bullet_slots,
	const usize slots_count);

#ifdef __cplusplus
}
#endif
