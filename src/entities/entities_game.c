#include "entities_game.h"

soa_slot_t soa_dynamic_new1(
	soa_dynamic *dynamic,
	const soa_dynamic_desc_t *desc)
{
	const soa_slot_t slot = soa_new_slot1(&dynamic->_ent);
	const usize d = slot.idx;
	dynamic->position.x[d] = desc->position.x;
	dynamic->position.y[d] = desc->position.y;
	dynamic->size.w[d] = desc->size.w;
	dynamic->size.h[d] = desc->size.h;
	dynamic->speed.val[d] = desc->speed;
	dynamic->animation.begin_frame[d] = desc->animation.begin_frame;
	dynamic->animation.end_frame[d] = desc->animation.end_frame;
	dynamic->animation.current_frame[d] = desc->animation.begin_frame;
	dynamic->animation.frame_time[d].seconds = desc->animation.frame_time.seconds;
	return slot;
}

void soa_dynamic_free1(
	soa_dynamic *dynamic,
	soa_slot_t slot)
{
	return soa_free_slot1(&dynamic->_ent, slot);
}
