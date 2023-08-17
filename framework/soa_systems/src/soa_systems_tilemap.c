#include <soa_components_physics.h>
#include <soa_components_transform.h>
#include <soa_systems_tilemap.h>
#include <tilemap.h>

f32v2 tile_position_to_position(i32v2 tile_position, i32v2 tile_size)
{
	return (f32v2){
		tile_position.x * tile_size.w,
		tile_position.y * tile_size.h,
	};
}

void calculate_tilemap_collision_buffer(
	tilemap_t *tilemap,
	const tilemap_encoding_t *tilemap_encoding,
	const tile_properties_t *tile_properties)
{
	const u32 mapwidth = tilemap->width;
	const u32 mapheight = tilemap->height;

	for (usize y = 0; y < mapheight; ++y) {
		for (usize x = 0; x < mapwidth; ++x) {
			const usize offset = y * mapwidth + x;
			tilemap->collision_buffer.offset_to_walking_speed[offset] = 1.f;
		}
	}

	for (usize l = 0; l < tilemap->num_layers; ++l) {
		const tilemap_layer_t *layer = &tilemap->layers[l];

		for (usize y = 0; y < mapheight; ++y) {
			for (usize x = 0; x < mapwidth; ++x) {
				const usize offset = y * mapwidth + x;
				const u8 tile_char = layer->offset_to_char[offset];
				const tile_enum_t tile_enum = tilemap_encoding->char_to_enum[tile_char];
				if (tile_enum < TILEMAP_TILE_BEGIN || tile_enum > TILEMAP_TILE_END) continue;

				const f32 walking_speed = tile_properties->enum_to_walking_speed[tile_enum];
				const f32 current_walking_speed = tilemap->collision_buffer.offset_to_walking_speed[offset];

				tilemap->collision_buffer.offset_to_walking_speed[offset] =
					walking_speed < current_walking_speed ?
					walking_speed :
					current_walking_speed;
			}
		}
	}
}

void multiply_velocity_by_future_tile_speed(
	const soa_position2 *e_position,
	soa_velocity2 *e_velocity,
	const soa_slot_t entity_slot,
	const tilemap_t *tilemap,
	const i32v2 tile_size,
	const f32seconds dt)
{
	const u32 mapwidth = tilemap->width;
	const usize e = entity_slot.idx;
	const f32 future_x = e_position->x[e] + e_velocity->x[e] * dt.seconds;
	const f32 future_y = e_position->y[e] + e_velocity->y[e] * dt.seconds;
	const i32 tile_x = future_x / tile_size.w;
	const i32 tile_y = future_y / tile_size.h;
	const usize offset = tile_y * mapwidth + tile_x;
	const f32 tile_speed = tilemap->collision_buffer.offset_to_walking_speed[offset];
	e_velocity->x[e] *= tile_speed;
	e_velocity->y[e] *= tile_speed;
}
