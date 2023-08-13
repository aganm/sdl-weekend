#pragma once

#include <primitive_types.h>

typedef struct soa_position2 soa_position2;
typedef struct soa_size2 soa_size2;
typedef struct soa_clip soa_clip;
typedef struct tilemap_t tilemap_t;
typedef struct tileset_t tileset_t;
typedef struct tilemap_encoding_t tilemap_encoding_t;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;

void draw_sprite(
	const soa_position2 *e_position,
	const soa_size2 *e_size,
	const soa_clip *e_clip,
	const usize entity_count,
	SDL_Renderer *renderer,
	SDL_Texture *texture,
	const f32v2 camera);

void draw_tilemap(
	const tilemap_t *tilemap,
	const tilemap_encoding_t *tilemap_encoding,
	const tileset_t *tileset,
	i32v2 tile_size,
	SDL_Renderer *renderer,
	SDL_Texture *tilesheet_texture,
	const f32v2 camera);
