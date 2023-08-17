#pragma once

#include <primitive_types.h>

typedef struct soa_animation soa_animation;
typedef struct soa_clip soa_clip;
typedef struct soa_velocity2 soa_velocity2;
typedef struct tileset_t tileset_t;

void progress_animation_if_moving(
	soa_animation *e_animation,
	const soa_velocity2 *e_velocity,
	const usize entity_count,
	const f32seconds dt);

void fetch_tileset_animation(
	const soa_animation *e_animation,
	soa_clip *e_clip,
	const usize entity_count,
	const tileset_t *tileset);
