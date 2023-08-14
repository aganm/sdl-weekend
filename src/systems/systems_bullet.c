#include "soa.h"
#include "components/components_transform.h"
#include "components/components_shape.h"
#include "components/components_movement.h"
#include "components/components_health.h"
#include "components/components_damage.h"
#include "systems_despawn.h"
#include <primitive_types.h>
#include <assert.h>

void detect_bullet_collisions_with_something(
	const soa_position2 *s_pos,
	const soa_size2 *s_size,
	const usize something_count,
	const soa_position2 *b_pos,
	const usize bullet_count,
	soa_slot_t collided_somethings[something_count],
	soa_slot_t collided_bullets[bullet_count],
	usize *out_collided_count)
{
	(void)s_size;

	f32v2 range_x = { 0.f, 0.f };
	f32v2 range_y = { 0.f, 0.f };
	for (usize s = 0; s < something_count; ++s) {
		const f32 x = s_pos->x[s];
		const f32 y = s_pos->y[s];
		range_x.min = x < range_x.min ? x : range_x.min;
		range_x.max = x > range_x.max ? x : range_x.max;
		range_y.min = y < range_y.min ? y : range_y.min;
		range_y.max = y > range_y.max ? y : range_y.max;
	}
	for (usize b = 0; b < bullet_count; ++b) {
		const f32 x = b_pos->x[b];
		const f32 y = b_pos->y[b];
		range_x.min = x < range_x.min ? x : range_x.min;
		range_x.max = x > range_x.max ? x : range_x.max;
		range_y.min = y < range_y.min ? y : range_y.min;
		range_y.max = y > range_y.max ? y : range_y.max;
	}

	const f32v2 origin_offset = { range_x.min, range_y.min };
	const f32v2 grid_size = { range_x.max - range_x.min, range_y.max - range_y.min };
	const f32v2 cell_size = { 32.f, 32.f };
	const i32v2 cell_count = { grid_size.w / cell_size.w + 1, grid_size.h / cell_size.h + 1};

	soa_slot_t something_grid[cell_count.h][cell_count.w];
	for (i32 y = 0; y < cell_count.h; ++y) {
		for (i32 x = 0; x < cell_count.w; ++x) {
			something_grid[y][x] = (soa_slot_t){ 0 };
		}
	}

	bool s_been_processed[something_count];
	bool b_been_processed[bullet_count];
	usize something_processed_count = SOA_CLEAR_COUNT;
	for (usize s = 0; s < something_count; ++s) {
		s_been_processed[s] = false;
		b_been_processed[s] = false;
	}

	i32v2 grid_cells_to_reset[something_count];
	usize grid_cells_to_reset_count = 0;

	usize collided_count = 0;
	while (something_processed_count <= something_count) {
		for (usize i = 0; i < grid_cells_to_reset_count; ++i) {
			const i32v2 cell = grid_cells_to_reset[i];
			something_grid[cell.y][cell.x] = (soa_slot_t){ 0 };
		}
		grid_cells_to_reset_count = 0;

		for (usize s = 0; s < something_count; ++s) {
			if (!s_been_processed[s]) {
				const f32v2 pos = { s_pos->x[s] - origin_offset.x, s_pos->y[s] - origin_offset.y };
				assert(pos.x >= 0.f);
				assert(pos.y >= 0.f);
				const i32v2 cell = { pos.x / cell_size.w, pos.y / cell_size.h };
				if (something_grid[cell.y][cell.x].idx == 0) {
					something_grid[cell.y][cell.x] = (soa_slot_t){ s };
					something_processed_count += 1;
					s_been_processed[s] = true;
					grid_cells_to_reset[grid_cells_to_reset_count++] = cell;
				}
			}
		}
		for (usize b = 0; b < bullet_count; ++b) {
			if (!b_been_processed[b]) {
				const f32v2 pos = { b_pos->x[b] - origin_offset.x, b_pos->y[b] - origin_offset.y};
				assert(pos.x >= 0.f);
				assert(pos.y >= 0.f);
				const i32v2 cell = { pos.x / cell_size.w, pos.y / cell_size.h };
				if (something_grid[cell.y][cell.x].idx != 0) {
					collided_somethings[collided_count] = something_grid[cell.y][cell.x];
					collided_bullets[collided_count] = (soa_slot_t){ b };
					collided_count += 1;
					b_been_processed[b] = true;
				}
			}
		}
	}

	*out_collided_count = collided_count;
}

void bullet_damages_something(
	soa_health *s_health,
	soa_damage *b_damage,
	const soa_slot_t *something_slots,
	const soa_slot_t *bullet_slots,
	const usize slots_count)
{
	for (usize i = 0; i < slots_count; ++i) {
		const usize s = something_slots[i].idx;
		const usize b = bullet_slots[i].idx;
		s_health->val[s] -= b_damage->val[b];
	}
}
