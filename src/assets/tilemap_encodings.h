#pragma once

#include "tilemap.h"

static const tilemap_encoding_t tilemap_encoding1 = {
	.char_to_enum = (tile_enum_t[]){
		[' '] = TILEMAP_TILE_EMPTY,
		['#'] = TILEMAP_TILE_WALL,
		['.'] = TILEMAP_TILE_SOIL,
		['w'] = TILEMAP_TILE_GRASS,
		['W'] = TILEMAP_TILE_SHRUB,
		['T'] = TILEMAP_TILE_TREE,
		['b'] = TILEMAP_TILE_BUSH,
		['r'] = TILEMAP_TILE_ROCK,
		['P'] = TILEMAP_START_PLAYER,
		['B'] = TILEMAP_OBJECT_BARREL,
		['M'] = TILEMAP_OBJECT_MONSTER,
		['S'] = TILEMAP_SPAWNER_MONSTER,
	},
};
