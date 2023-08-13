#pragma once

#include <primitive_types.h>

typedef struct game_data_t game_data_t;
typedef struct SDL_Renderer SDL_Renderer;
typedef union SDL_Event SDL_Event;

void game_init(game_data_t *data, SDL_Renderer *renderer);
void game_fini(game_data_t *data);
void game_handle_sdl_event(game_data_t *data, const SDL_Event *event);
void game_tick(game_data_t *data, f64seconds tick_dt);
