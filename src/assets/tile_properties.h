#pragma once

#include "asset.h"

static const tile_properties_t tile_properties1 = {
	.enum_to_walking_speed = (float[]) {
		[ASSET_TILE_WALL] = 0.f,
		[ASSET_TILE_SOIL] = 1.f,
		[ASSET_TILE_GRASS] = 1.f,
		[ASSET_TILE_SHRUB] = 0.75f,
		[ASSET_TILE_TREE] = 0.f,
		[ASSET_TILE_BUSH] = 0.5f,
		[ASSET_TILE_ROCK] = 0.f,
		[ASSET_TILE_BARREL] = 1.f,
		[ASSET_TILE_EXPLOSION] = 1.f,
		[ASSET_TILE_BULLET] = 1.f,
		[ASSET_TILE_PLAYER_00] = 1.f,
		[ASSET_TILE_PLAYER_01] = 1.f,
		[ASSET_TILE_MONSTER_00] = 1.f,
		[ASSET_TILE_MONSTER_01] = 1.f,
	},
};
