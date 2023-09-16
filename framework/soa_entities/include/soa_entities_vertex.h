#pragma once

/**
 * @file
 * @brief 3D entities.
 */

#include <soa.h>
#include <soa_components_color.h>
#include <soa_components_graphics.h>
#include <soa_components_transform.h>
#include <types/bundle.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_vertex_3d {
	soa_entity_t _ent;
	soa_position3 position;
	soa_color color;
	soa_texcoord texcoord;
} soa_vertex_3d;

#ifdef __cplusplus
}
#endif
