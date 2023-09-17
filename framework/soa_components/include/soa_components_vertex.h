#pragma once

/**
 * @file
 * @brief Vertex components.
 */

#include <soa.h>
#include <types/bundle.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_xy_st_rgba8_t {
	f32v2 xy;
	f32v2 st;
	u8v4 rgba;
} soa_xy_st_rgba8_t;

typedef struct soa_xy_st_rgba8 {
	soa_xy_st_rgba8_t val[SOA_LIMIT];
} soa_xy_st_rgba8;

#ifdef __cplusplus
}
#endif
