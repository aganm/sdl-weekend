#pragma once

/**
 * @file
 * @brief Vertex systems.
 */

#include <types/bundle.h>
#include <types/primitive.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct soa_position soa_position2;
typedef struct soa_rotation soa_rotation1;
typedef struct soa_size soa_size2;
typedef struct soa_clip soa_clip;
typedef struct soa_color soa_color;
typedef struct soa_color1 soa_color1;
typedef struct soa_texcoord soa_texcoord;
typedef struct soa_entity_t soa_entity_t;

void soa_make_sprite_vertices(
	const soa_position2 *e_position,
	const soa_rotation1 *e_rotation,
	const soa_size2 *e_size,
	const soa_clip *e_clip,
	const soa_color *e_color,
	usize entity_count,
	soa_position2 *v_position,
	soa_color1 *v_color,
	soa_texcoord *v_texcoord,
	soa_entity_t *vertex_entity,
	f32v2 texture_size);

#ifdef __cplusplus
}
#endif
