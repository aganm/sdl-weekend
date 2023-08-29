#pragma once

/**
 * @file
 * @brief Transform components.
 */

#include <soa.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_position2 {
	f32 x[SOA_LIMIT];
	f32 y[SOA_LIMIT];
} soa_position2;

typedef struct soa_rotation1 {
	f32 x[SOA_LIMIT];
} soa_rotation1;

#ifdef __cplusplus
}
#endif
