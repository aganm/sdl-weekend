#pragma once

#include <types/primitive.h>
#include <soa.h>

typedef struct soa_position2 {
	f32 x[SOA_LIMIT];
	f32 y[SOA_LIMIT];
} soa_position2;

typedef struct soa_rotation1 {
	f32 x[SOA_LIMIT];
} soa_rotation1;
