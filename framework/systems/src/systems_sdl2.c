#include <SDL2/SDL_render.h>
#include <math_helpers.h>
#include <tilemap.h>
#include <components_graphics.h>
#include <components_shape.h>
#include <components_transform.h>
#include <systems_sdl2.h>

void draw_sprite(
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
		const SDL_Rect origrect = {
			e_position->x[e] - e_size->w[e] / 2.f,
			e_position->y[e] - e_size->h[e],
			e_size->w[e],
			e_size->h[e],
		};
		const SDL_Rect dstrect = {
			origrect.x - camera.x,
			origrect.y - camera.y,
			origrect.w,
			origrect.h,
		};
		SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
	}
}

void draw_sprite_rotated(
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
		const SDL_Rect origrect = {
			e_position->x[e] - e_size->w[e] / 2.f,
			e_position->y[e] - e_size->h[e],
			e_size->w[e],
			e_size->h[e],
		};
		const SDL_Rect dstrect = {
			origrect.x - camera.x,
			origrect.y - camera.y,
			origrect.w,
			origrect.h,
		};
		const f32 angle = rad_to_deg(e_rotation->x[e]);
		SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, angle, NULL, SDL_FLIP_NONE);
	}
}

void draw_tilemap(
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
	const u32 tilewidth = tile_size.w;
	const u32 tileheight = tile_size.h;

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

void draw_tilemap_collision_buffer(
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
				x * tile_size.w - (i32)camera.x,
				y * tile_size.h - (i32)camera.y,
				tile_size.w,
				tile_size.h,
			};
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100.f * (1.f - tile_speed));
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}
