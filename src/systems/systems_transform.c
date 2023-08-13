#include "soa.h"
#include "components/components_transform.h"
#include "systems_transform.h"

void change_one_position2(
	soa_position2 *e_position,
	const soa_slot_t entity_slot,
	const f32v2 new_position)
{
	const usize e = entity_slot.idx;
	e_position->x[e] = new_position.x;
	e_position->y[e] = new_position.y;
}
