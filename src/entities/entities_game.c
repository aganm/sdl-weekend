#include "entities_game.h"
#include "math_helpers.h"

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

soa_slot_t soa_bullet_new1(
	soa_bullet *bullet,
	const soa_bullet_desc_t *desc)
{
	const soa_slot_t slot = soa_new_slot1(&bullet->_ent);
	const usize b = slot.idx;
	bullet->position.x[b] = desc->position.x;
	bullet->position.y[b] = desc->position.y;
	bullet->destination.x[b] = desc->destination.x;
	bullet->destination.y[b] = desc->destination.y;
	bullet->rotation.x[b] = angle_between_points(desc->position, desc->destination);
	bullet->size.w[b] = desc->size.w;
	bullet->size.h[b] = desc->size.h;
	bullet->speed.val[b] = desc->speed;
	bullet->damage.val[b] = desc->damage;
	bullet->animation.begin_frame[b] = desc->animation.begin_frame;
	bullet->animation.end_frame[b] = desc->animation.end_frame;
	bullet->animation.current_frame[b] = desc->animation.begin_frame;
	bullet->animation.frame_time[b].seconds = desc->animation.frame_time.seconds;
	return slot;
}

void soa_dynamic_free(
	soa_dynamic *dynamic,
	const soa_slot_t *slots,
	const usize slot_count)
{
	for (usize i = 0; i < slot_count; ++i) {
		const usize d = slots[i].idx;
		dynamic->size.w[d] = 0.f;
		dynamic->size.h[d] = 0.f;
	}
	return soa_free_slot(&dynamic->_ent, slots, slot_count);
}

void soa_bullet_free(
	soa_bullet *bullet,
	const soa_slot_t *slots,
	const usize slot_count)
{
	for (usize i = 0; i < slot_count; ++i) {
		const usize b = slots[i].idx;
		bullet->damage.val[b] = 0.f;
		bullet->size.w[b] = 0.f;
		bullet->size.h[b] = 0.f;
	}
	return soa_free_slot(&bullet->_ent, slots, slot_count);
}
