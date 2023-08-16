#include "entities_game.h"
#include <math_helpers.h>

soa_slot_t soa_character_new1(
	soa_character *character,
	const soa_character_desc_t *desc)
{
	const soa_slot_t slot = soa_new_slot1(&character->_ent);
	const usize c = slot.idx;
	character->position.x[c] = desc->position.x;
	character->position.y[c] = desc->position.y;
	character->size.w[c] = desc->size.w;
	character->size.h[c] = desc->size.h;
	character->speed.val[c] = desc->speed;
	character->health.val[c] = desc->health;
	character->animation.begin_frame[c] = desc->animation.begin_frame;
	character->animation.end_frame[c] = desc->animation.end_frame;
	character->animation.current_frame[c] = desc->animation.begin_frame;
	character->animation.frame_time[c].seconds = desc->animation.frame_time.seconds;
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

void soa_character_free(
	soa_character *character,
	const soa_slot_t *slots,
	const usize slot_count)
{
	for (usize i = 0; i < slot_count; ++i) {
		const usize c = slots[i].idx;
		character->damage.val[c] = 0.f;
		character->size.w[c] = 0.f;
		character->size.h[c] = 0.f;
	}
	return soa_free_slot(&character->_ent, slots, slot_count);
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
