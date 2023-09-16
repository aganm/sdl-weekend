#pragma once

/**
 * @file
 * @brief SDL2 entities.
 */

#include <soa.h>
#include <soa_components_sdl2.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_sdl2_vertex_array {
	soa_entity_t _ent;
	soa_sdl2_vertex vertex;
} soa_sdl2_vertex_array;

#ifdef __cplusplus
}
#endif
