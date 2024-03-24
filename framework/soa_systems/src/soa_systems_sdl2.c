#include <SDL2/SDL_render.h>
#include <math/math_helpers.h>
#include <soa.h>
#include <soa_components_color.h>
#include <soa_components_graphics.h>
#include <soa_components_sdl2.h>
#include <soa_components_shape.h>
#include <soa_components_transform.h>
#include <soa_systems_sdl2.h>
#include <tilemap.h>

void soa_make_sdl2_vertex(
	const soa_position2 *e_position,
	const soa_color1 *e_color,
	const soa_texcoord *e_texcoord,
	const usize entity_count,
	soa_sdl2_vertex *to_vertex,
	soa_entity_t *to_entity)
{
	for (usize e = 0; e < entity_count; ++e) {
		const usize t = soa_new_slot1(to_entity).idx;
		to_vertex->val[t] = (SDL_Vertex) {
			.position = { e_position->x[e], e_position->y[e] },
			.color = { e_color->val[e].r, e_color->val[e].g, e_color->val[e].b, e_color->val[e].a },
			.tex_coord = { e_texcoord->s[e], e_texcoord->t[e] },
		};
	}
}

void soa_draw_geometry(
	const soa_sdl2_vertex *e_vertex,
	const usize entity_count,
	SDL_Renderer* renderer,
	SDL_Texture* texture)
{
	SDL_RenderGeometry(renderer, texture, e_vertex->val, entity_count, NULL, 0);
}

void soa_draw_sprite(
	const soa_position2 *e_position,
	const soa_size2 *e_size,
	const soa_clip *e_clip,
	const usize entity_count,
	SDL_Renderer *renderer,
	SDL_Texture *texture,
	const f32v2 camera)
{
	for (usize e = 0; e < entity_count; ++e) {
		const SDL_Rect srcrect = {
			e_clip->x[e],
			e_clip->y[e],
			e_clip->w[e],
			e_clip->h[e],
		};
		const SDL_FRect origrect = {
			e_position->x[e] - e_size->w[e] * 0.5f,
			e_position->y[e] - e_size->h[e],
			e_size->w[e],
			e_size->h[e],
		};
		const SDL_FRect dstrect = {
			origrect.x - camera.x,
			origrect.y - camera.y,
			origrect.w,
			origrect.h,
		};
		SDL_RenderCopyF(renderer, texture, &srcrect, &dstrect);
	}
}

void soa_draw_rect(
	const soa_position2 *e_position,
	const soa_size2 *e_size,
	const usize entity_count,
	SDL_Renderer *renderer,
	const f32v2 camera)
{
	for (usize e = 0; e < entity_count; ++e) {
		const SDL_FRect origrect = {
			e_position->x[e] - e_size->w[e] * 0.5f,
			e_position->y[e] - e_size->h[e],
			e_size->w[e],
			e_size->h[e],
		};
		const SDL_FRect dstrect = {
			origrect.x - camera.x,
			origrect.y - camera.y,
			origrect.w,
			origrect.h,
		};
		SDL_RenderDrawRectF(renderer, &dstrect);
	}
}

void soa_draw_sprite_rotated(
	const soa_position2 *e_position,
	const soa_rotation1 *e_rotation,
	const soa_size2 *e_size,
	const soa_clip *e_clip,
	const usize entity_count,
	SDL_Renderer *renderer,
	SDL_Texture *texture,
	const f32v2 camera)
{
	for (usize e = 0; e < entity_count; ++e) {
		const SDL_Rect srcrect = {
			e_clip->x[e],
			e_clip->y[e],
			e_clip->w[e],
			e_clip->h[e],
		};
		const SDL_FRect origrect = {
			e_position->x[e] - e_size->w[e] * 0.5f,
			e_position->y[e] - e_size->h[e],
			e_size->w[e],
			e_size->h[e],
		};
		const SDL_FRect dstrect = {
			origrect.x - camera.x,
			origrect.y - camera.y,
			origrect.w,
			origrect.h,
		};
		const f32 angle = rad_to_deg(e_rotation->x[e]);
		SDL_RenderCopyExF(renderer, texture, &srcrect, &dstrect, angle, NULL, SDL_FLIP_NONE);
	}
}

void soa_draw_tilemap(
	const tilemap_t *tilemap,
	const tilemap_encoding_t *tilemap_encoding,
	const tileset_t *tileset,
	const i32v2 tile_size,
	SDL_Renderer *renderer,
	SDL_Texture *tilesheet_texture,
	const f32v2 camera)
{
	const u32 mapwidth = tilemap->width;
	const u32 mapheight = tilemap->height;
	const u32 tilewidth = tile_size.width;
	const u32 tileheight = tile_size.height;

	for (usize l = 0; l < tilemap->num_layers; ++l) {
		const tilemap_layer_t *layer = &tilemap->layers[l];

		for (usize y = 0; y < mapheight; ++y) {
			for (usize x = 0; x < mapwidth; ++x) {
				const usize offset = y * mapwidth + x;
				const u8 tile_char = layer->offset_to_char[offset];
				const tile_enum_t tile_enum = tilemap_encoding->char_to_enum[tile_char];
				if (tile_enum < TILEMAP_TILE_BEGIN || tile_enum > TILEMAP_TILE_END) continue;
				const tile_t tile = tileset->enum_to_tile[tile_enum];

				const SDL_Rect srcrect = {
					tile.x,
					tile.y,
					tile.w,
					tile.h,
				};
				const SDL_Rect origrect = {
					x * tilewidth,
					y * tileheight,
					tilewidth,
					tileheight,
				};
				const SDL_Rect dstrect = {
					origrect.x - (i32)camera.x,
					origrect.y - (i32)camera.y,
					origrect.w,
					origrect.h,
				};
				SDL_RenderCopy(renderer, tilesheet_texture, &srcrect, &dstrect);
			}
		}
	}
}

void soa_draw_tilemap_collision_buffer(
	const tilemap_t *tilemap,
	const i32v2 tile_size,
	SDL_Renderer *renderer,
	const f32v2 camera)
{
	const u32 mapwidth = tilemap->width;
	const u32 mapheight = tilemap->height;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	for (usize y = 0; y < mapheight; ++y) {
		for (usize x = 0; x < mapwidth; ++x) {
			const usize offset = y * mapwidth + x;
			const f32 tile_speed = tilemap->collision_buffer.offset_to_walking_speed[offset];
			const SDL_Rect rect = {
				x * tile_size.width - (i32)camera.x,
				y * tile_size.height - (i32)camera.y,
				tile_size.width,
				tile_size.height,
			};
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, (Uint8)(100.f * (1.f - tile_speed)));
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}
