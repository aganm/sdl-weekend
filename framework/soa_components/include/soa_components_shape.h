#pragma once

/**
 * @file
 * @brief Shape components.
 */

#include <soa.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_size2 {
	f32 w[SOA_LIMIT];
	f32 h[SOA_LIMIT];
} soa_size2;

#ifdef __cplusplus
}
#endif
