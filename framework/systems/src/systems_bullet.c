#include <types/bundle.h>
#include <types/primitive.h>
#include <soa.h>
#include <components_transform.h>
#include <components_shape.h>
#include <components_movement.h>
#include <components_health.h>
#include <components_damage.h>
#include <systems_despawn.h>

void detect_bullet_collisions_with_something(
	const soa_position2 *s_pos,
	const soa_size2 *s_size,
	const usize something_count,
	const soa_position2 *b_pos,
	const usize bullet_count,
	soa_slot_t out_collided_somethings[something_count],
	soa_slot_t out_collided_bullets[bullet_count],
	usize *out_collided_count)
{
	usize total_collided_count = 0;

#pragma omp parallel
{
	soa_slot_t worker_collided_somethings[something_count];
	soa_slot_t worker_collided_bullets[something_count];
	usize worker_collided_count = 0;
#pragma omp for
	for (usize b = 0; b < bullet_count; ++b) {
		for (usize s = 0; s < something_count; ++s) {
			const f32v2 pos = { b_pos->x[b], b_pos->y[b] };
			const f32rect rect = { s_pos->x[s], s_pos->y[s], s_size->w[s], s_size->h[s] };
			const bool overlaps = (pos.x > rect.x) && (pos.x < rect.x + rect.w) &&
						(pos.y > rect.y) && (pos.y < rect.y + rect.h);
			if (overlaps) {
				worker_collided_somethings[worker_collided_count] = (soa_slot_t){ s };
				worker_collided_bullets[worker_collided_count] = (soa_slot_t){ b };
				worker_collided_count += 1;
				break;
			}
		}
	}
#pragma omp critical
	{
		for (usize i = 0; i < worker_collided_count; ++i) {
			out_collided_somethings[total_collided_count + i] = worker_collided_somethings[i];
			out_collided_bullets[total_collided_count + i] = worker_collided_bullets[i];
		}
		total_collided_count += worker_collided_count;
	}
}
	*out_collided_count = total_collided_count;
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
