#pragma once

/**
 * @file
 * @brief Color components.
 */

#include <soa.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_color {
	u8 r[SOA_LIMIT];
	u8 g[SOA_LIMIT];
	u8 b[SOA_LIMIT];
	u8 a[SOA_LIMIT];
} soa_color;

#ifdef __cplusplus
}
#endif
