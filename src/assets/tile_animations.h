#pragma once

#include "tilemap.h"

static const tile_animation_t player_animation = {
	.begin_tile_frame = TILEMAP_TILE_PLAYER_00,
	.end_tile_frame = TILEMAP_TILE_PLAYER_01,
	.frame_seconds = 1.f / 30.f,
};

static const tile_animation_t monster_animation = {
	.begin_tile_frame = TILEMAP_TILE_MONSTER_00,
	.end_tile_frame = TILEMAP_TILE_MONSTER_01,
	.frame_seconds = 1.f / 30.f,
};
