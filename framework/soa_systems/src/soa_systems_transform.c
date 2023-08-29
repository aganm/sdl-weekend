#include <soa.h>
#include <soa_components_transform.h>
#include <soa_systems_transform.h>

f32v2 soa_get_one_position2(
	const soa_position2 *e_position,
	const soa_slot_t entity_slot)
{
	const usize e = entity_slot.idx;
	return (f32v2) {
		.x = e_position->x[e],
		.y = e_position->y[e]
	};
}

void soa_change_one_position2(
	soa_position2 *e_position,
	const soa_slot_t entity_slot,
	const f32v2 new_position)
{
	const usize e = entity_slot.idx;
	e_position->x[e] = new_position.x;
	e_position->y[e] = new_position.y;
}

void soa_backup_position2(
	const soa_position2 *e_position,
	soa_position2 *e_old_position,
	const usize entity_count)
{
	for (usize e = 0; e < entity_count; ++e) {
		e_old_position->x[e] = e_position->x[e];
		e_old_position->y[e] = e_position->y[e];
	}
}
