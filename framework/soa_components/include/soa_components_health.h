#pragma once

/**
 * @file
 * @brief Health components.
 */

#include <soa.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_health {
	f32 val[SOA_LIMIT];
} soa_health;

#ifdef __cplusplus
}
#endif
