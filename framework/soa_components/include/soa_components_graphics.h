#pragma once

/**
 * @file
 * @brief Graphics components.
 */

#include <soa.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_clip {
	u16 x[SOA_LIMIT];
	u16 y[SOA_LIMIT];
	u16 w[SOA_LIMIT];
	u16 h[SOA_LIMIT];
} soa_clip;

#ifdef __cplusplus
}
#endif
