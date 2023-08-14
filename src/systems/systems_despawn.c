#include "soa.h"
#include "components/components_transform.h"
#include "components/components_movement.h"
#include "components/components_health.h"
#include "systems_despawn.h"
#include <math.h>

void get_destination_reached_despawn_slots(
	const soa_position2 *e_position,
	const soa_destination2 *e_destination,
	const usize entity_count,
	const f32 reach_distance,
	soa_slot_t output[entity_count],
	usize *output_count)
{
	usize count = 0;
	for (usize e = 0; e < entity_count; ++e) {
		const f32 dx = e_destination->x[e] - e_position->x[e];
		const f32 dy = e_destination->y[e] - e_position->y[e];
		const f32 distance = sqrt(dx * dx + dy * dy);
		const bool is_close = distance < reach_distance;
		output[count] = (soa_slot_t){ e };
		count += is_close;
	}
	*output_count = count;
}

void get_dead_despawn_slots(
	const soa_health *e_health,
	const usize entity_count,
	soa_slot_t output[entity_count],
	usize *output_count)
{
	usize count = 0;
	for (usize e = 0; e < entity_count; ++e) {
		const bool is_dead = e_health->val[e] <= 0.f;
		output[count] = (soa_slot_t){ e };
		count += is_dead;
	}
	*output_count = count;
}