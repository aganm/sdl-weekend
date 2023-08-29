#pragma once

/**
 * @file
 * @brief Animation components.
 */

#include <soa.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_animation {
	u8 begin_frame[SOA_LIMIT];
	u8 end_frame[SOA_LIMIT];
	u8 current_frame[SOA_LIMIT];
	f32seconds frame_elapsed[SOA_LIMIT];
	f32seconds frame_time[SOA_LIMIT];
} soa_animation;

#ifdef __cplusplus
}
#endif
