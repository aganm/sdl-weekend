#pragma once

#include "soa.h"
#include <primitive_types.h>

typedef struct soa_clip {
	u16 x[SOA_LIMIT];
	u16 y[SOA_LIMIT];
	u16 w[SOA_LIMIT];
	u16 h[SOA_LIMIT];
} soa_clip;
