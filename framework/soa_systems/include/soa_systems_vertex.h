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
typedef struct soa_size soa_size2;
typedef struct soa_clip soa_clip;
typedef struct soa_color soa_color;
typedef struct soa_texcoord soa_texcoord;
typedef struct soa_entity_t soa_entity_t;

void soa_make_sprite_vertices(
	soa_position2 *f_position,
	soa_size2 *f_size,
	soa_clip *f_clip,
	soa_color *f_color,
	usize from_count,
	soa_position2 *t_position,
	soa_color *t_color,
	soa_texcoord *t_texcoord,
	soa_entity_t *to_entity);

#ifdef __cplusplus
}
#endif
