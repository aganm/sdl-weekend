#include "soa.h"
#include "components/components_transform.h"
#include "components/components_shape.h"
#include "components/components_movement.h"
#include "components/components_health.h"
#include "components/components_damage.h"
#include "systems_despawn.h"
#include <primitive_types.h>

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
	usize collided_count = 0;

	for (usize b = 0; b < bullet_count; ++b) {
		for (usize s = 0; s < something_count; ++s) {
			const f32v2 p = { b_pos->x[b], b_pos->y[b] };
			const f32r4 r = { s_pos->x[s], s_pos->y[s], s_size->w[s], s_size->h[s] };
			const bool overlaps =
				(p.x > r.x) && (p.x < r.x + r.w) &&
				(p.y > r.y) && (p.y < r.y + r.h);

			if (overlaps) {
				collided_somethings[collided_count] = (soa_slot_t){ s };
				collided_bullets[collided_count] = (soa_slot_t){ b };
				collided_count += 1;
				break;
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
