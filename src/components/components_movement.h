#pragma once

#include "soa.h"
#include <primitive_types.h>

typedef struct soa_movement2 {
	f32 x[SOA_LIMIT];
	f32 y[SOA_LIMIT];
} soa_movement2;

typedef struct soa_speed {
	f32 val[SOA_LIMIT];
} soa_speed;
