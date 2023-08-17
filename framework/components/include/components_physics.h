#pragma once

#include <types/primitive.h>
#include <soa.h>

typedef struct soa_velocity2 {
	f32 x[SOA_LIMIT];
	f32 y[SOA_LIMIT];
} soa_velocity2;

typedef struct soa_weight {
	f32 kg[SOA_LIMIT];
} soa_weight;
