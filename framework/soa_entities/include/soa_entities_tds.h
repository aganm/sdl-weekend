#pragma once

/* Top down shooter entities. */

#include <types/bundle.h>
#include <types/primitive.h>
#include <soa.h>

#include <soa_components_animation.h>
#include <soa_components_damage.h>
#include <soa_components_graphics.h>
#include <soa_components_health.h>
#include <soa_components_movement.h>
#include <soa_components_physics.h>
#include <soa_components_shape.h>
#include <soa_components_transform.h>

typedef struct soa_character {
	soa_entity_t _ent;
	soa_position2 position;
	soa_size2 size;
	soa_velocity2 velocity;
	soa_speed speed;
	soa_movement2 movement;
	soa_animation animation;
	soa_clip clip;
	soa_health health;
	soa_damage damage;
} soa_character;

typedef struct soa_bullet {
	soa_entity_t _ent;
	soa_position2 position;
	soa_size2 size;
	soa_velocity2 velocity;
	soa_rotation1 rotation;
	soa_destination2 destination;
	soa_speed speed;
	soa_movement2 movement;
	soa_animation animation;
	soa_clip clip;
	soa_damage damage;
} soa_bullet;

typedef struct soa_character_desc_t {
	f32v2 position;
	f32v2 size;
	f32 speed;
	f32 health;
	struct {
		u8 begin_frame;
		u8 end_frame;
		f32seconds frame_time;
	} animation;
} soa_character_desc_t;

typedef struct soa_bullet_desc_t {
	f32v2 position;
	f32v2 destination;
	f32v2 size;
	f32 speed;
	f32 damage;
	struct {
		u8 begin_frame;
		u8 end_frame;
		f32seconds frame_time;
	} animation;
} soa_bullet_desc_t;

soa_slot_t soa_character_new1(
	soa_character *character,
	const soa_character_desc_t *desc);

soa_slot_t soa_bullet_new1(
	soa_bullet *bullet,
	const soa_bullet_desc_t *desc);

void soa_character_free(
	soa_character *character,
	const soa_slot_t *slot,
	const usize slot_count);

void soa_bullet_free(
	soa_bullet *bullet,
	const soa_slot_t *slots,
	const usize slot_count);
