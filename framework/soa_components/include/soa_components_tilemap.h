#pragma once

/**
 * @file
 * @brief Tilemap components.
 */

#include <soa.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_tile_position2 {
	i32 x[SOA_LIMIT];
	i32 y[SOA_LIMIT];
} soa_tile_position2;

#ifdef __cplusplus
}
#endif
