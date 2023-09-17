#pragma once

/**
 * @file
 * @brief Physics components.
 */

#include <soa.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_velocity {
	f32 x[SOA_LIMIT];
	f32 y[SOA_LIMIT];
} soa_velocity2;

typedef struct soa_weight {
	f32 kg[SOA_LIMIT];
} soa_weight;

#ifdef __cplusplus
}
#endif
