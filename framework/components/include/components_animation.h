#pragma once

#include <types/primitive.h>
#include <soa.h>

typedef struct soa_animation {
	u8 begin_frame[SOA_LIMIT];
	u8 end_frame[SOA_LIMIT];
	u8 current_frame[SOA_LIMIT];
	f32seconds frame_elapsed[SOA_LIMIT];
	f32seconds frame_time[SOA_LIMIT];
} soa_animation;
