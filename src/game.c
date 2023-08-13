#include "game.h"
#include "assets/tile_animations.h"
#include "assets/tilemap_encodings.h"
#include "assets/tilemaps.h"
#include "assets/tilesets.h"
#include "game_data.h"
#include "game_timer.h"
#include "soa.h"
#include "systems/systems_animation.h"
#include "systems/systems_movement.h"
#include "systems/systems_physics.h"
#include "systems/systems_sdl2.h"
#include "systems/systems_tilemap.h"
#include "systems/systems_transform.h"
#include <SDL2/SDL.h>
#include <primitive_types.h>

static void load_map_objects(
	game_data_t *data,
	const tilemap_t *tilemap,
	const tilemap_encoding_t *tilemap_encoding)
{
	const i32 width = tilemap->width;
	const i32 height = tilemap->height;
	const i32v2 tile_size = data->tile_size;
	const f32v2 entity_size = { tile_size.w, tile_size.h };

	for (int l = 0; l < tilemap->num_layers; ++l) {
		const tilemap_layer_t *layer = &tilemap->layers[l];

		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				const i32v2 tile_position = { x, y };
				const char tile_char = layer->offset_to_char[y * width + x];
				const tile_enum_t tile_enum = tilemap_encoding->char_to_enum[tile_char];

				switch (tile_enum) {
				case ASSET_START_PLAYER: {
					data->player_slot = soa_dynamic_new1(&data->dynamic,
					    &(const soa_dynamic_desc_t) {
						.position = tile_position_to_position(tile_position, tile_size),
						.size = entity_size,
						.speed = 500.f,
						.animation = {
						    .begin_frame = player_animation.begin_tile_frame,
						    .end_frame = player_animation.end_tile_frame,
						    .frame_time = player_animation.frame_seconds,
						},
					    });
					break;
				}
				case ASSET_OBJECT_MONSTER: {
					soa_dynamic_new1(&data->dynamic,
					    &(const soa_dynamic_desc_t) {
						.position = tile_position_to_position(tile_position, tile_size),
						.size = entity_size,
						.speed = 250.f,
						.animation = {
						    .begin_frame = monster_animation.begin_tile_frame,
						    .end_frame = monster_animation.end_tile_frame,
						    .frame_time = monster_animation.frame_seconds,
						},
					    });
					break;
				}
				default:
					break;
				}
			}
		}
	}
}

void game_init(game_data_t *data, SDL_Renderer *renderer)
{
	SDL_Surface* surface = SDL_LoadBMP(tileset1.image_path);
	const tile_color_key_t color_key_A = tileset1.color_key;
	const Uint32 color_key_B = SDL_MapRGB(surface->format, color_key_A.r, color_key_A.g, color_key_A.b);
	SDL_SetColorKey(surface, SDL_TRUE, color_key_B);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	*data = (game_data_t) { 0 };
	data->tile_size = (i32v2) { 32, 32 };
	data->renderer = renderer;
	data->tileset1_texture = texture;
	data->gameplay_timer = game_timer_init();
	data->dynamic = (soa_dynamic)SOA_ENTITY_INIT;
	data->player_slot = (soa_slot_t) { 0 };

	load_map_objects(data, &level1_map, &tilemap_encoding1);

	soa_dynamic *dynamic = &data->dynamic;
	fetch_tileset_animation(&dynamic->animation, &dynamic->clip, dynamic->_ent.count, &tileset1);
}

void game_fini(game_data_t *data)
{
	SDL_DestroyTexture(data->tileset1_texture);
	game_timer_fini(&data->gameplay_timer);
}

void game_handle_sdl_event(game_data_t *data, const SDL_Event *event)
{
	soa_dynamic *player = &data->dynamic;
	const usize p = data->player_slot.idx;

	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_A)
			player->movement.x[p] = -1.f;
		if (event->key.keysym.scancode == SDL_SCANCODE_D)
			player->movement.x[p] = 1.f;
		if (event->key.keysym.scancode == SDL_SCANCODE_W)
			player->movement.y[p] = -1.f;
		if (event->key.keysym.scancode == SDL_SCANCODE_S)
			player->movement.y[p] = 1.f;
		break;
	case SDL_KEYUP:
		if (event->key.keysym.scancode == SDL_SCANCODE_A)
			player->movement.x[p] = 0.f;
		if (event->key.keysym.scancode == SDL_SCANCODE_D)
			player->movement.x[p] = 0.f;
		if (event->key.keysym.scancode == SDL_SCANCODE_W)
			player->movement.y[p] = 0.f;
		if (event->key.keysym.scancode == SDL_SCANCODE_S)
			player->movement.y[p] = 0.f;
		break;
	}
}

void game_tick(game_data_t *data, f64seconds tick_dt)
{
	soa_dynamic *player = &data->dynamic;
	soa_dynamic *monster = &data->dynamic;
	const soa_slot_t player_slot = data->player_slot;

	/* update gameplay at 60hz */
	game_timer_t *gameplay_timer = &data->gameplay_timer;
	if (game_timer_tick(gameplay_timer, tick_dt, 1.0 / 60.0)) {
		const f32seconds dt = { game_timer_delta_seconds(gameplay_timer) };
		reset_velocity(&player->velocity, player->_ent.count);
		follow_one_target(&monster->position, &monster->movement, &monster->speed, monster->_ent.count,
				&player->position, player_slot);
		apply_movement(&player->movement, &player->speed, &player->velocity, player->_ent.count);
		apply_forwards_velocity(&player->position, &player->velocity, player->_ent.count, dt);
		progress_animation_if_moving(&player->animation, &player->velocity, player->_ent.count, dt);
		fetch_tileset_animation(&player->animation, &player->clip, player->_ent.count, &tileset1);
	}

	/* render */
	draw_tilemap(&level1_map, &tilemap_encoding1, &tileset1,
		data->tile_size, data->renderer, data->tileset1_texture);
	draw_sprite(&player->position, &player->size, &player->clip, player->_ent.count,
		data->renderer, data->tileset1_texture);
}
