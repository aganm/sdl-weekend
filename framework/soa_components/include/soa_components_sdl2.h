#pragma once

/**
 * @file
 * @brief SDL2 components.
 */

#include <soa.h>
#include <types/primitive.h>
#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_sdl2_vertex {
	SDL_Vertex val[SOA_LIMIT];
} soa_sdl2_vertex;

#ifdef __cplusplus
}
#endif
