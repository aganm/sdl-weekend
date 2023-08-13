#include "asset.h"
#include "components/components_animation.h"
#include "components/components_graphics.h"
#include "components/components_physics.h"
#include "systems_animation.h"
#include <SDL2/SDL_render.h>

void progress_animation_if_moving(
	soa_animation *e_animation,
	const soa_velocity2 *e_velocity,
	const usize entity_count,
	const f32seconds dt)
{
	for (usize e = 0; e < entity_count; ++e) {
		if (e_velocity->x[e] != 0.f || e_velocity->y[e] != 0.f) {
			e_animation->frame_elapsed[e].seconds += dt.seconds;
		}
		if (e_animation->frame_elapsed[e].seconds > e_animation->frame_time[e].seconds) {
			e_animation->frame_elapsed[e].seconds = 0.f;
			e_animation->current_frame[e] += 1;
			if (e_animation->current_frame[e] > e_animation->end_frame[e]) {
				e_animation->current_frame[e] = e_animation->begin_frame[e];
			}
		}
	}
}

void fetch_tileset_animation(
	const soa_animation *e_animation,
	soa_clip *e_clip,
	const usize entity_count,
	const tileset_t *tileset)
{
	for (usize e = 0; e < entity_count; ++e) {
		const tile_enum_t tile_enum = e_animation->current_frame[e];
		const tile_t tile = tileset->enum_to_tile[tile_enum];
		e_clip->x[e] = tile.x;
		e_clip->y[e] = tile.y;
		e_clip->w[e] = tile.w;
		e_clip->h[e] = tile.h;
	}
}
