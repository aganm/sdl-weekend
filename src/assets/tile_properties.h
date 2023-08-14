#pragma once

#include "tilemap.h"

static const tile_properties_t tile_properties1 = {
	.enum_to_walking_speed = (f32[]) {
		[TILEMAP_TILE_WALL] = 0.f,
		[TILEMAP_TILE_SOIL] = 1.f,
		[TILEMAP_TILE_GRASS] = 1.f,
		[TILEMAP_TILE_SHRUB] = 0.75f,
		[TILEMAP_TILE_TREE] = 0.5f,
		[TILEMAP_TILE_BUSH] = 0.5f,
		[TILEMAP_TILE_ROCK] = 0.75f,
		[TILEMAP_TILE_BARREL] = 1.f,
		[TILEMAP_TILE_EXPLOSION] = 1.f,
		[TILEMAP_TILE_BULLET] = 1.f,
		[TILEMAP_TILE_PLAYER_00] = 1.f,
		[TILEMAP_TILE_PLAYER_01] = 1.f,
		[TILEMAP_TILE_MONSTER_00] = 1.f,
		[TILEMAP_TILE_MONSTER_01] = 1.f,
	},
};
