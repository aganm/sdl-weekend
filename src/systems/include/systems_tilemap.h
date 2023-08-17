#pragma once

#include <bundle_types.h>
#include <primitive_types.h>

typedef struct soa_slot_t soa_slot_t;
typedef struct soa_position2 soa_position2;
typedef struct soa_velocity2 soa_velocity2;
typedef struct tilemap_t tilemap_t;
typedef struct tilemap_encoding_t tilemap_encoding_t;
typedef struct tile_properties_t tile_properties_t;

f32v2 tile_position_to_position(
	i32v2 tile_position,
	i32v2 tile_size);

void calculate_tilemap_collision_buffer(
	tilemap_t *tilemap,
	const tilemap_encoding_t *tilemap_encoding,
	const tile_properties_t *tile_properties);

void multiply_velocity_by_future_tile_speed(
	const soa_position2 *e_position,
	soa_velocity2 *e_velocity,
	const soa_slot_t entity_slot,
	const tilemap_t *tilemap,
	const i32v2 tile_size,
	const f32seconds dt);
