#pragma once

#include "soa.h"
#include "components/components_animation.h"
#include "components/components_damage.h"
#include "components/components_graphics.h"
#include "components/components_movement.h"
#include "components/components_physics.h"
#include "components/components_shape.h"
#include "components/components_transform.h"
#include <primitive_types.h>

typedef struct soa_dynamic {
	soa_entity_t _ent;
	soa_position2 position;
	soa_position2 old_position;
	soa_size2 size;
	soa_velocity2 velocity;
	soa_speed speed;
	soa_movement2 movement;
	soa_animation animation;
	soa_clip clip;
} soa_dynamic;

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

typedef struct soa_dynamic_desc_t {
	f32v2 position;
	f32v2 size;
	f32 speed;
	struct {
		u8 begin_frame;
		u8 end_frame;
		f32seconds frame_time;
	} animation;
} soa_dynamic_desc_t;

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

soa_slot_t soa_dynamic_new1(
	soa_dynamic *dynamic,
	const soa_dynamic_desc_t *desc);

soa_slot_t soa_bullet_new1(
	soa_bullet *bullet,
	const soa_bullet_desc_t *desc);

void soa_dynamic_free(
	soa_dynamic *dynamic,
	const soa_slot_t *slot,
	const usize slot_count);

void soa_bullet_free(
	soa_bullet *bullet,
	const soa_slot_t *slots,
	const usize slot_count);
