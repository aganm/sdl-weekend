#pragma once

#include <soa.h>
#include <types/primitive.h>

typedef struct soa_movement2 {
	f32 x[SOA_LIMIT];
	f32 y[SOA_LIMIT];
} soa_movement2;

typedef struct soa_destination2 {
	f32 x[SOA_LIMIT];
	f32 y[SOA_LIMIT];
} soa_destination2;

typedef struct soa_speed {
	f32 val[SOA_LIMIT];
} soa_speed;
