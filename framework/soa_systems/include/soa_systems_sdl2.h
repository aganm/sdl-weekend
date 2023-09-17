#pragma once

/**
 * @file
 * @brief SDL2 systems.
 */

#include <types/bundle.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_position soa_position2;
typedef struct soa_rotation soa_rotation1;
typedef struct soa_color soa_color;
typedef struct soa_color1 soa_color1;
typedef struct soa_texcoord soa_texcoord;
typedef struct soa_size soa_size2;
typedef struct soa_clip soa_clip;
typedef struct soa_sdl2_vertex soa_sdl2_vertex;
typedef struct soa_entity_t soa_entity_t;
typedef struct tilemap_t tilemap_t;
typedef struct tileset_t tileset_t;
typedef struct tilemap_encoding_t tilemap_encoding_t;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;

void soa_make_sdl2_vertex(
	const soa_position2 *e_position,
	const soa_color1 *e_color,
	const soa_texcoord *e_texcoord,
	const usize entity_count,
	soa_sdl2_vertex *to_vertex,
	soa_entity_t *to_entity);

void soa_draw_geometry(
	const soa_sdl2_vertex *e_vertex,
	const usize entity_count,
	SDL_Renderer *renderer,
	SDL_Texture *texture);

void soa_draw_sprite(
	const soa_position2 *e_position,
	const soa_size2 *e_size,
	const soa_clip *e_clip,
	const usize entity_count,
	SDL_Renderer *renderer,
	SDL_Texture *texture,
	const f32v2 camera);

void soa_draw_rect(
	const soa_position2 *e_position,
	const soa_size2 *e_size,
	const usize entity_count,
	SDL_Renderer *renderer,
	const f32v2 camera);

void soa_draw_sprite_rotated(
	const soa_position2 *e_position,
	const soa_rotation1 *e_rotation,
	const soa_size2 *e_size,
	const soa_clip *e_clip,
	const usize entity_count,
	SDL_Renderer *renderer,
	SDL_Texture *texture,
	const f32v2 camera);

void soa_draw_tilemap(
	const tilemap_t *tilemap,
	const tilemap_encoding_t *tilemap_encoding,
	const tileset_t *tileset,
	const i32v2 tile_size,
	SDL_Renderer *renderer,
	SDL_Texture *tilesheet_texture,
	const f32v2 camera);

void soa_draw_tilemap_collision_buffer(
	const tilemap_t *tilemap,
	const i32v2 tile_size,
	SDL_Renderer *renderer,
	const f32v2 camera);

#ifdef __cplusplus
}
#endif
