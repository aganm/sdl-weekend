#include <SDL2/SDL.h>
#include <camera2d.h>
#include <math/math_helpers.h>
#include <sdl2_app.h>
#include <soa.h>
#include <stdlib.h>
#include <time.h>
#include <types/bundle.h>
#include <types/primitive.h>

#include "assets/tile_animations.h"
#include "assets/tile_properties.h"
#include "assets/tilemap_encodings.h"
#include "assets/tilemaps.h"
#include "assets/tilesets.h"

#include <soa_entities_sdl2.h>
#include <soa_entities_tds.h>
#include <soa_entities_vertex.h>
#include <soa_systems_animation.h>
#include <soa_systems_bullet.h>
#include <soa_systems_camera.h>
#include <soa_systems_despawn.h>
#include <soa_systems_movement.h>
#include <soa_systems_physics.h>
#include <soa_systems_sdl2.h>
#include <soa_systems_tilemap.h>
#include <soa_systems_transform.h>
#include <soa_systems_vertex.h>

typedef struct SDL_SceneData {
	SDL_Texture *tileset1_texture;
	f32v2 texture_size;
	i32v2 tile_size;
	soa_timer_t gameplay_timer;
	soa_character player;
	soa_character monster;
	soa_bullet bullet;
	soa_slot_t player_slot;
	f32v2 camera;
	soa_vertex_3d vertex_3d;
	soa_sdl2_vertex_array sdl2_vertex_array;
	bool render_3d;
} SDL_SceneData;

static void load_map_objects(
	SDL_SceneData *data,
	const tilemap_t *tilemap,
	const tilemap_encoding_t *tilemap_encoding)
{
	const u32 mapwidth = tilemap->width;
	const u32 mapheight = tilemap->height;
	const i32v2 tile_size = data->tile_size;
	const f32v2 entity_size = { tile_size.width, tile_size.height };

	for (usize l = 0; l < tilemap->num_layers; ++l) {
		const tilemap_layer_t *layer = &tilemap->layers[l];

		for (usize y = 0; y < mapheight; ++y) {
			for (usize x = 0; x < mapwidth; ++x) {
				const i32v2 tile_position = { x, y };
				const usize offset = y * mapwidth + x;
				const u8 tile_char = layer->offset_to_char[offset];
				const tile_enum_t tile_enum = tilemap_encoding->char_to_enum[tile_char];

				switch (tile_enum) {
				case TILEMAP_START_PLAYER: {
					data->player_slot = soa_character_new1(&data->player, &(const soa_character_desc_t) {
						.position = tile_position_to_position(tile_position, tile_size),
						.size = entity_size,
						.speed = 400.f,
						.animation = {
							.begin_frame = player_animation.begin_tile_frame,
							.end_frame = player_animation.end_tile_frame,
							.frame_time = player_animation.frame_time,
						},
					});
					break;
				}
				case TILEMAP_OBJECT_MONSTER: {
					soa_character_new1(&data->monster, &(const soa_character_desc_t) {
						.position = tile_position_to_position(tile_position, tile_size),
						.size = entity_size,
						.speed = 200.f,
						.health = 100.f,
						.animation = {
							.begin_frame = monster_animation.begin_tile_frame,
							.end_frame = monster_animation.end_tile_frame,
							.frame_time = monster_animation.frame_time,
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

static void game_init(
	SDL_App *app,
	SDL_SceneData *data)
{
	SDL_Surface* surface = SDL_LoadBMP(tileset1.image_path);
	const tile_color_key_t color_key_A = tileset1.color_key;
	const Uint32 color_key_B = SDL_MapRGB(surface->format, color_key_A.r, color_key_A.g, color_key_A.b);
	SDL_SetColorKey(surface, SDL_TRUE, color_key_B);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(app->renderer, surface);
	const f32v2 texture_size = { surface->w, surface->h };
	SDL_FreeSurface(surface);

	*data = (SDL_SceneData) { 0 };
	data->tileset1_texture = texture;
	data->texture_size = texture_size;
	data->tile_size = (i32v2) { 32, 32 };
	data->gameplay_timer = soa_timer_init();
	data->player = (soa_character)SOA_ENTITY_WITH_TOMBSTONE;
	data->monster = (soa_character)SOA_ENTITY_WITH_TOMBSTONE;
	data->bullet = (soa_bullet)SOA_ENTITY_WITH_TOMBSTONE;
	data->player_slot = (soa_slot_t) { 0 };
	data->vertex_3d = (soa_vertex_3d)SOA_ENTITY_ZERO;
	data->sdl2_vertex_array = (soa_sdl2_vertex_array)SOA_ENTITY_ZERO;
	data->render_3d = false;

	load_map_objects(data, &level1_map, &tilemap_encoding1);

	soa_calculate_tilemap_collision_buffer(&level1_map, &tilemap_encoding1, &tile_properties1);
}

static void game_fini(
	SDL_App *app,
	SDL_SceneData *data)
{
	(void)app;
	SDL_DestroyTexture(data->tileset1_texture);
	soa_timer_fini(&data->gameplay_timer);
}

static void fire_bullet(
	SDL_SceneData* data,
	f32v2 mouse,
	usize count)
{
	const f32v2 world_mouse_position = { data->camera.x + mouse.x, data->camera.y + mouse.y };
	const f32v2 origin = soa_get_one_position2(&data->player.position, data->player_slot);

	for (usize i = 0; i < count; ++i) {
		const f32v2 bullet_position = {
			origin.x + i * 5.f,
			origin.y + i * 5.f,
		};
		soa_bullet_new1(&data->bullet, &(const soa_bullet_desc_t) {
			.position = bullet_position,
			.destination = world_mouse_position,
			.size = { data->tile_size.x, data->tile_size.y },
			.speed = 600.f,
			.damage = 50.f,
			.animation = {
				.begin_frame = bullet_animation.begin_tile_frame,
				.end_frame = bullet_animation.end_tile_frame,
				.frame_time = bullet_animation.frame_time,
			},
		});
	}
}

static void spawn_monsters(
	SDL_SceneData* data,
	f32rect area,
	usize count)
{
	for (usize i = 0; i < count; ++i) {
		const f32v2 monster_position = {
			area.x + ((f32)rand() / (f32)RAND_MAX) * area.w,
			area.y + ((f32)rand() / (f32)RAND_MAX) * area.h,
		};
		soa_character_new1(&data->monster, &(const soa_character_desc_t) {
			.position = monster_position,
			.size = { data->tile_size.x, data->tile_size.y },
			.speed = 200.f,
			.health = 100.f,
			.animation = {
				.begin_frame = monster_animation.begin_tile_frame,
				.end_frame = monster_animation.end_tile_frame,
				.frame_time = monster_animation.frame_time,
			},
		});
	}
}

static void game_handle_sdl_event(
	SDL_App *app,
	SDL_SceneData *data,
	const SDL_Event *event)
{
	(void)app;

	static bool move_left = false;
	static bool move_right = false;
	static bool move_up = false;
	static bool move_down = false;

	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_Z)
			data->render_3d = !data->render_3d;

		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			spawn_monsters(data, (f32rect){ 0.f, 0.f, 1024.f, 1024.f }, 10);

		if (event->key.keysym.scancode == SDL_SCANCODE_A)
			move_left = true;
		if (event->key.keysym.scancode == SDL_SCANCODE_D)
			move_right = true;
		if (event->key.keysym.scancode == SDL_SCANCODE_W)
			move_up = true;
		if (event->key.keysym.scancode == SDL_SCANCODE_S)
			move_down = true;
		break;
	case SDL_KEYUP:
		if (event->key.keysym.scancode == SDL_SCANCODE_A)
			move_left = false;
		if (event->key.keysym.scancode == SDL_SCANCODE_D)
			move_right = false;
		if (event->key.keysym.scancode == SDL_SCANCODE_W)
			move_up = false;
		if (event->key.keysym.scancode == SDL_SCANCODE_S)
			move_down = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
			fire_bullet(data, (f32v2){ event->button.x, event->button.y }, 1);
		if (event->button.button == SDL_BUTTON_RIGHT)
			fire_bullet(data, (f32v2){ event->button.x, event->button.y }, 10);
		break;
	}

	soa_character *player = &data->player;
	const usize p = data->player_slot.idx;

	if (move_left) {
		player->movement.x[p] = -1.f;
	} else if (move_right) {
		player->movement.x[p] = 1.f;
	} else {
		player->movement.x[p] = 0.f;
	}
	if (move_up) {
		player->movement.y[p] = -1.f;
	} else if (move_down) {
		player->movement.y[p] = 1.f;
	} else {
		player->movement.y[p] = 0.f;
	}

}

static void game_tick(
	SDL_App *app,
	SDL_SceneData *data,
	f64seconds tick_dt,
	f32v2 viewport)
{
	soa_character *player = &data->player;
	soa_character *monster = &data->monster;
	soa_bullet *bullet = &data->bullet;
	const soa_slot_t player_slot = data->player_slot;
	soa_vertex_3d *vertex_3d = &data->vertex_3d;
	soa_sdl2_vertex_array *sdl2_vertex_array = &data->sdl2_vertex_array;

	/* update gameplay at 60hz */
	soa_timer_t *gameplay_timer = &data->gameplay_timer;
	soa_timer_tick(gameplay_timer, tick_dt);
	while (soa_timer_do_frame(gameplay_timer, 1.0 / 60.0)) {
		const f32seconds dt = { soa_timer_delta_seconds(gameplay_timer) };

		soa_reset_velocity(&player->velocity, player->_ent.count);
		soa_movement_to_velocity(&player->movement, &player->speed, &player->velocity, player->_ent.count);
		soa_multiply_velocity_by_future_tile_speed(&player->position, &player->velocity, player_slot, &level1_map, data->tile_size, dt);
		soa_apply_forwards_velocity(&player->position, &player->velocity, player->_ent.count, dt);
		soa_progress_animation_if_moving(&player->animation, &player->velocity, player->_ent.count, dt);
		soa_fetch_tileset_animation(&player->animation, &player->clip, player->_ent.count, &tileset1);

		soa_reset_velocity(&monster->velocity, monster->_ent.count);
		soa_follow_one_target(&monster->movement, &monster->position, &monster->speed, monster->_ent.count, &player->position, player_slot);
		soa_movement_to_velocity(&monster->movement, &monster->speed, &monster->velocity, monster->_ent.count);
		soa_apply_forwards_velocity(&monster->position, &monster->velocity, monster->_ent.count, dt);
		soa_progress_animation_if_moving(&monster->animation, &monster->velocity, monster->_ent.count, dt);
		soa_fetch_tileset_animation(&monster->animation, &monster->clip, monster->_ent.count, &tileset1);

		soa_slot_t despawn_monster_slots[monster->_ent.count];
		usize despawn_monster_slot_count;
		soa_get_dead_despawn_slots(&monster->health, monster->_ent.count, despawn_monster_slots, &despawn_monster_slot_count);
		soa_character_free(monster, despawn_monster_slots, despawn_monster_slot_count);

		soa_reset_velocity(&bullet->velocity, bullet->_ent.count);
		soa_forward_movement_from_rotation(&bullet->movement, &bullet->rotation, bullet->_ent.count);
		soa_movement_to_velocity(&bullet->movement, &bullet->speed, &bullet->velocity, bullet->_ent.count);
		soa_apply_forwards_velocity(&bullet->position, &bullet->velocity, bullet->_ent.count, dt);
		soa_fetch_tileset_animation(&bullet->animation, &bullet->clip, bullet->_ent.count, &tileset1);

		soa_slot_t despawn_bullet_slots[bullet->_ent.count];
		usize despawn_bullet_slot_count;
		soa_get_destination_reached_despawn_slots(&bullet->position, &bullet->destination, bullet->_ent.count,
						10.f, despawn_bullet_slots, &despawn_bullet_slot_count);
		soa_bullet_free(bullet, despawn_bullet_slots, despawn_bullet_slot_count);

		const usize collided_max = bullet->_ent.count;
		soa_slot_t collided_monsters[collided_max];
		soa_slot_t collided_bullets[collided_max];
		usize collided_count;
		soa_detect_bullet_collisions_with_something(&monster->position, &monster->size, monster->_ent.count,
							&bullet->position, bullet->_ent.count,
							collided_monsters, collided_bullets, &collided_count);
		soa_bullet_damages_something(&monster->health, &bullet->damage,
					collided_monsters, collided_bullets, collided_count);
		soa_bullet_free(bullet, collided_bullets, collided_count);
	}

	/* old rendering */
	const f32v2 center = soa_get_one_position2(&player->position, player_slot);
	const f32v2 camera = camera_center_offset(viewport, center);
	const f32v3 camera_3d = { .x = camera.x, .y = 20.f, .z = camera.y };
	data->camera = camera;

	soa_draw_tilemap(&level1_map, &tilemap_encoding1, &tileset1,
		data->tile_size, app->renderer, data->tileset1_texture, camera);
	soa_draw_sprite(&player->position, &player->size, &player->clip, player->_ent.count,
		app->renderer, data->tileset1_texture, camera);
	// soa_draw_sprite(&monster->position, &monster->size, &monster->clip, monster->_ent.count,
	//	app->renderer, data->tileset1_texture, camera);
	soa_draw_rect(&monster->position, &monster->size, monster->_ent.count,
		app->renderer, camera);
	soa_draw_sprite_rotated(&bullet->position, &bullet->rotation, &bullet->size, &bullet->clip, bullet->_ent.count,
		app->renderer, data->tileset1_texture, camera);
	// soa_draw_tilemap_collision_buffer(&level1_map, data->tile_size, data->renderer, camera);

	/* new rendering */
	soa_clear(&vertex_3d->_ent);
	soa_clear(&sdl2_vertex_array->_ent);

	soa_make_cube(&vertex_3d->position, &vertex_3d->color, &vertex_3d->texcoord, &vertex_3d->_ent,
			(f32v3){ 100.f, 100.f, 0.f }, 100.f);
	if (!data->render_3d) {
		soa_make_sprite_vertices(&monster->position, &monster->rotation, &monster->size, &monster->clip, &monster->color, monster->_ent.count,
			&vertex_3d->position, &vertex_3d->color, &vertex_3d->texcoord, &vertex_3d->_ent,
			data->texture_size);
		soa_apply_camera_2d(&vertex_3d->position, vertex_3d->_ent.count,
			camera);
	} else {
		soa_make_sprite_vertices_3d(&monster->position, &monster->rotation, &monster->size, &monster->clip, &monster->color, monster->_ent.count,
			&vertex_3d->position, &vertex_3d->color, &vertex_3d->texcoord, &vertex_3d->_ent,
			data->texture_size);
		soa_apply_camera_3d(&vertex_3d->position, vertex_3d->_ent.count,
			camera_3d, viewport);
	}
	soa_make_sdl2_vertex(&vertex_3d->position, &vertex_3d->color, &vertex_3d->texcoord, vertex_3d->_ent.count,
		&sdl2_vertex_array->vertex, &sdl2_vertex_array->_ent);
	soa_draw_geometry(&sdl2_vertex_array->vertex, sdl2_vertex_array->_ent.count,
		app->renderer, data->tileset1_texture);
}

SDL_SceneDesc export_sdl_scene(
	void)
{
	return (SDL_SceneDesc) {
		.data_size = sizeof(SDL_SceneData),
		.init = game_init,
		.fini = game_fini,
		.handle_sdl_event = game_handle_sdl_event,
		.tick = game_tick,
	};
}
