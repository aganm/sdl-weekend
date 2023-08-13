#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct tile_t {
	int x, y, w, h;
} tile_t;

typedef enum tile_enum_t {
	ASSET_TILE_EMPTY,
	ASSET_TILE_BEGIN = 1,
	ASSET_TILE_WALL = ASSET_TILE_BEGIN,
	ASSET_TILE_SOIL,
	ASSET_TILE_GRASS,
	ASSET_TILE_SHRUB,
	ASSET_TILE_TREE,
	ASSET_TILE_BUSH,
	ASSET_TILE_ROCK,
	ASSET_TILE_BARREL,
	ASSET_TILE_EXPLOSION,
	ASSET_TILE_BULLET,
	ASSET_TILE_PLAYER_00,
	ASSET_TILE_PLAYER_01,
	ASSET_TILE_MONSTER_00,
	ASSET_TILE_MONSTER_01,
	ASSET_TILE_END = ASSET_TILE_MONSTER_01,

	ASSET_START_PLAYER,
	ASSET_OBJECT_BARREL,
	ASSET_OBJECT_MONSTER,
	ASSET_SPAWNER_MONSTER,
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
