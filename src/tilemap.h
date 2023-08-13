#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct tile_t {
	int x, y, w, h;
} tile_t;

typedef enum tile_enum_t {
	TILEMAP_TILE_EMPTY,
	TILEMAP_TILE_BEGIN = 1,
	TILEMAP_TILE_WALL = TILEMAP_TILE_BEGIN,
	TILEMAP_TILE_SOIL,
	TILEMAP_TILE_GRASS,
	TILEMAP_TILE_SHRUB,
	TILEMAP_TILE_TREE,
	TILEMAP_TILE_BUSH,
	TILEMAP_TILE_ROCK,
	TILEMAP_TILE_BARREL,
	TILEMAP_TILE_EXPLOSION,
	TILEMAP_TILE_BULLET,
	TILEMAP_TILE_PLAYER_00,
	TILEMAP_TILE_PLAYER_01,
	TILEMAP_TILE_MONSTER_00,
	TILEMAP_TILE_MONSTER_01,
	TILEMAP_TILE_END = TILEMAP_TILE_MONSTER_01,

	TILEMAP_START_PLAYER,
	TILEMAP_OBJECT_BARREL,
	TILEMAP_OBJECT_MONSTER,
	TILEMAP_SPAWNER_MONSTER,
} tile_enum_t;

typedef struct tile_animation_t {
	tile_enum_t begin_tile_frame;
	tile_enum_t end_tile_frame;
	float frame_seconds;
} tile_animation_t;

typedef struct tilemap_encoding_t {
	const tile_enum_t *char_to_enum;
} tilemap_encoding_t;

typedef struct tile_color_key_t {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} tile_color_key_t;

typedef struct tileset_t {
	const char *image_path;
	tile_color_key_t color_key;
	const tile_t *enum_to_tile;
} tileset_t;

typedef struct tile_properties_t {
	const float *enum_to_walking_speed;
} tile_properties_t;

typedef struct tilemap_layer_t {
	const char *offset_to_char;
} tilemap_layer_t;

typedef struct tilemap_t {
	int width;
	int height;
	int num_layers;
	const tilemap_layer_t *layers;
} tilemap_t;
