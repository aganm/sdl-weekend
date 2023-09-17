#pragma once

/**
 * @file
 * @brief Movement components.
 */

#include <soa.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_movement {
	f32 x[SOA_LIMIT];
	f32 y[SOA_LIMIT];
} soa_movement2;

typedef struct soa_destination {
	f32 x[SOA_LIMIT];
	f32 y[SOA_LIMIT];
} soa_destination2;

typedef struct soa_speed {
	f32 val[SOA_LIMIT];
} soa_speed;

#ifdef __cplusplus
}
#endif
