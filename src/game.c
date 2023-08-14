#include "game.h"
#include "assets/tile_animations.h"
#include "assets/tile_properties.h"
#include "assets/tilemap_encodings.h"
#include "assets/tilemaps.h"
#include "assets/tilesets.h"
#include "game_data.h"
#include "game_timer.h"
#include "soa.h"
#include "systems/systems_animation.h"
#include "systems/systems_bullet.h"
#include "systems/systems_camera.h"
#include "systems/systems_despawn.h"
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
				case TILEMAP_START_PLAYER: {
					data->player_slot = soa_character_new1(&data->player,
					    &(const soa_character_desc_t) {
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
				case TILEMAP_OBJECT_MONSTER: {
					soa_character_new1(&data->monster,
					    &(const soa_character_desc_t) {
						.position = tile_position_to_position(tile_position, tile_size),
						.size = entity_size,
						.speed = 250.f,
						.health = 100.f,
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
	data->player = (soa_character)SOA_ENTITY_INIT;
	data->monster = (soa_character)SOA_ENTITY_INIT;
	data->bullet = (soa_bullet)SOA_ENTITY_INIT;
	data->player_slot = (soa_slot_t) { 0 };

	load_map_objects(data, &level1_map, &tilemap_encoding1);

	soa_character *player = &data->player;
	fetch_tileset_animation(&player->animation, &player->clip, player->_ent.count, &tileset1);

	calculate_tilemap_collision_buffer(&level1_map, &tilemap_encoding1, &tile_properties1);
}

void game_fini(game_data_t *data)
{
	SDL_DestroyTexture(data->tileset1_texture);
	game_timer_fini(&data->gameplay_timer);
}

static void fire_bullet(game_data_t* data, f32v2 mouse, usize count)
{
	const f32v2 world_mouse_position = { data->camera.x + mouse.x, data->camera.y + mouse.y };
	const f32v2 origin = get_one_position2(&data->player.position, data->player_slot);

	for (usize i = 0; i < count; ++i) {
		const f32v2 bullet_position = {
			origin.x + i * 5.f,
			origin.y + i * 5.f,
		};
		const soa_slot_t b = soa_bullet_new1(&data->bullet,
		    &(const soa_bullet_desc_t) {
			.position = bullet_position,
			.destination = world_mouse_position,
			.size = { data->tile_size.x, data->tile_size.y },
			.speed = 1000.f,
			.damage = 50.f,
			.animation = {
			    .begin_frame = bullet_animation.begin_tile_frame,
			    .end_frame = bullet_animation.end_tile_frame,
			    .frame_time = bullet_animation.frame_seconds,
			},
		    });
	}
}

void game_handle_sdl_event(game_data_t *data, const SDL_Event *event)
{
	soa_character *player = &data->player;
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
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
			fire_bullet(data, (f32v2){ event->button.x, event->button.y }, 1);
		break;
	}
}

void game_tick(game_data_t *data, f64seconds tick_dt, f32v2 viewport)
{
	soa_character *player = &data->player;
	soa_character *monster = &data->monster;
	soa_bullet *bullet = &data->bullet;
	const soa_slot_t player_slot = data->player_slot;

	/* update gameplay at 60hz */
	game_timer_t *gameplay_timer = &data->gameplay_timer;
	if (game_timer_tick(gameplay_timer, tick_dt, 1.0 / 60.0)) {
		const f32seconds dt = { game_timer_delta_seconds(gameplay_timer) };

		// backup_position2(&player->position, &player->old_position, player->_ent.count);

		reset_velocity(&player->velocity, player->_ent.count);
		reset_velocity(&monster->velocity, monster->_ent.count);
		reset_velocity(&bullet->velocity, bullet->_ent.count);
		follow_one_target(&monster->movement, &monster->position, &monster->speed, monster->_ent.count,
				&player->position, player_slot);
		forward_movement_from_rotation(&bullet->movement, &bullet->rotation, &bullet->speed, bullet->_ent.count);
		movement_to_velocity(&player->movement, &player->speed, &player->velocity, player->_ent.count);
		movement_to_velocity(&monster->movement, &monster->speed, &monster->velocity, monster->_ent.count);
		movement_to_velocity(&bullet->movement, &bullet->speed, &bullet->velocity, bullet->_ent.count);
		multiply_velocity_by_future_tile_speed(&player->position, &player->velocity, player_slot,
						&level1_map, data->tile_size, dt);

		apply_forwards_velocity(&player->position, &player->velocity, player->_ent.count, dt);
		apply_forwards_velocity(&monster->position, &monster->velocity, monster->_ent.count, dt);
		apply_forwards_velocity(&bullet->position, &bullet->velocity, bullet->_ent.count, dt);

		progress_animation_if_moving(&player->animation, &player->velocity, player->_ent.count, dt);
		progress_animation_if_moving(&monster->animation, &monster->velocity, monster->_ent.count, dt);
		fetch_tileset_animation(&player->animation, &player->clip, player->_ent.count, &tileset1);
		fetch_tileset_animation(&monster->animation, &monster->clip, monster->_ent.count, &tileset1);
		fetch_tileset_animation(&bullet->animation, &bullet->clip, bullet->_ent.count, &tileset1);

		soa_slot_t despawn_bullet_slots[bullet->_ent.count];
		usize despawn_bullet_slot_count;
		get_destination_reached_despawn_slots(&bullet->position, &bullet->destination, bullet->_ent.count,
						10.f, despawn_bullet_slots, &despawn_bullet_slot_count);
		soa_bullet_free(bullet, despawn_bullet_slots, despawn_bullet_slot_count);

		const usize collided_max = monster->_ent.count * bullet->_ent.count;
		soa_slot_t collided_monsters[collided_max];
		soa_slot_t collided_bullets[collided_max];
		usize collided_count;
		detect_bullet_collisions_with_something(&monster->position, &monster->size, monster->_ent.count,
							&bullet->position, bullet->_ent.count,
							collided_monsters, collided_bullets, &collided_count);
		bullet_damages_something(&monster->health, &bullet->damage,
					collided_monsters, collided_bullets, collided_count);
		soa_bullet_free(bullet, collided_bullets, collided_count);

		soa_slot_t despawn_monster_slots[monster->_ent.count];
		usize despawn_monster_slot_count;
		get_dead_despawn_slots(&monster->health, monster->_ent.count,
					despawn_monster_slots, & despawn_monster_slot_count);
		soa_character_free(monster, despawn_monster_slots, despawn_monster_slot_count);
	}

	/* render */
	const f32v2 center = get_one_position2(&player->position, player_slot);
	const f32v2 camera = camera_center_offset(viewport, center);
	data->camera = camera;

	draw_tilemap(&level1_map, &tilemap_encoding1, &tileset1,
		data->tile_size, data->renderer, data->tileset1_texture, camera);
	draw_sprite(&player->position, &player->size, &player->clip, player->_ent.count,
		data->renderer, data->tileset1_texture, camera);
	draw_sprite(&monster->position, &monster->size, &monster->clip, monster->_ent.count,
		data->renderer, data->tileset1_texture, camera);
	draw_sprite_rotated(&bullet->position, &bullet->rotation, &bullet->size, &bullet->clip, bullet->_ent.count,
		data->renderer, data->tileset1_texture, camera);
	// draw_tilemap_collision_buffer(&level1_map, data->tile_size, data->renderer, camera);
}
