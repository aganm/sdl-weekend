#pragma once

/**
 * @file
 * @brief Damage components.
 */

#include <soa.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_damage {
	f32 val[SOA_LIMIT];
} soa_damage;

#ifdef __cplusplus
}
#endif
