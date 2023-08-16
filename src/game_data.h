#pragma once

#include "game_timer.h"
#include "entities/entities_game.h"
#include <primitive_types.h>
#include <bundle_types.h>

typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;

typedef struct game_data_t {
	i32v2 tile_size;
	SDL_Renderer *renderer;
	SDL_Texture *tileset1_texture;
	game_timer_t gameplay_timer;
	soa_character player;
	soa_character monster;
	soa_bullet bullet;
	soa_slot_t player_slot;
	f32v2 camera;
} game_data_t;
