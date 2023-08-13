#pragma once

#include "asset.h"

static const tilemap_encoding_t tilemap_encoding1 = {
	.char_to_enum = (tile_enum_t[]){
		[' '] = ASSET_TILE_EMPTY,
		['#'] = ASSET_TILE_WALL,
		['.'] = ASSET_TILE_SOIL,
		['w'] = ASSET_TILE_GRASS,
		['W'] = ASSET_TILE_SHRUB,
		['T'] = ASSET_TILE_TREE,
		['b'] = ASSET_TILE_BUSH,
		['r'] = ASSET_TILE_ROCK,
		['P'] = ASSET_START_PLAYER,
		['B'] = ASSET_OBJECT_BARREL,
		['M'] = ASSET_OBJECT_MONSTER,
		['S'] = ASSET_SPAWNER_MONSTER,
	},
};
