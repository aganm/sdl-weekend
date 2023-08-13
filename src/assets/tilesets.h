#pragma once

#include "tilemap.h"

static const tileset_t tileset1 = {
	.enum_to_tile = (tile_t[]) {
		[TILEMAP_TILE_WALL] = { 0, 0, 8, 8 },
		[TILEMAP_TILE_SOIL] = { 8, 0, 8, 8 },
		[TILEMAP_TILE_GRASS] = { 16, 0, 8, 8 },
		[TILEMAP_TILE_SHRUB] = { 24, 0, 8, 8 },
		[TILEMAP_TILE_TREE] = { 32, 0, 8, 8 },
		[TILEMAP_TILE_BUSH] = { 40, 0, 8, 8 },
		[TILEMAP_TILE_ROCK] = { 48, 0, 8, 8 },
		[TILEMAP_TILE_BARREL] = { 56, 0, 8, 8 },
		[TILEMAP_TILE_EXPLOSION] = { 64, 0, 8, 8 },
		[TILEMAP_TILE_BULLET] = { 72, 0, 8, 8 },
		[TILEMAP_TILE_PLAYER_00] = { 80, 0, 8, 8 },
		[TILEMAP_TILE_PLAYER_01] = { 88, 0, 8, 8 },
		[TILEMAP_TILE_MONSTER_00] = { 96, 0, 8, 8 },
		[TILEMAP_TILE_MONSTER_01] = { 104, 0, 8, 8 },
	},
	.image_path = "art/art.bmp",
	.color_key = { 255, 0, 255 },
};
