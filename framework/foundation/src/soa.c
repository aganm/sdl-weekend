#include "soa.h"
#include <assert.h>
#include <stdlib.h>

usize soa_round_up(
	usize number,
	usize multiple)
{
	if (multiple == 0) {
		return number;
	}
	const usize result = ((number + multiple / 2) / multiple) * multiple;
	return result < number ? result + multiple : result;
}

usize soa_simd_count(
	usize vector_size,
	usize scalar_size,
	usize count)
{
	const usize multiple = vector_size / scalar_size;
	return soa_round_up(count, multiple) / multiple;
}

soa_slot_t soa_new_slot1(
	soa_entity_t *entity)
{
	soa_slot_t slot;
	if (entity->num_free_slots > 0) {
		slot = entity->free_slots[--entity->num_free_slots];
	} else if (entity->count >= SOA_LIMIT) {
		slot = (soa_slot_t){ 0 };
	} else {
		slot = (soa_slot_t){ entity->count++ };
	}
	entity->is_occupied[slot.idx] = true;
	return slot;
}

void soa_free_slot(
	soa_entity_t *entity,
	const soa_slot_t *slots,
	usize slot_count)
{
	for (usize i = 0; i < slot_count; i++) {
		const soa_slot_t slot = slots[i];
		if ((entity->count - 1) == slot.idx) {
			entity->count -= 1;
			continue;
		}
		if (entity->is_occupied[slot.idx]) {
			entity->free_slots[entity->num_free_slots++] = slot;
			entity->is_occupied[slot.idx] = false;
		}
	}
}

void soa_clear(
	soa_entity_t *entity)
{
	const soa_entity_t tmp = {
		.count = entity->clear_count,
		.clear_count = entity->clear_count,
	};

	*entity = tmp;
}

soa_timer_t soa_timer_init(
	void)
{
	return (soa_timer_t){ 0 };
}

void soa_timer_fini(
	soa_timer_t *timer)
{
	(void)timer;
}

void soa_timer_tick(
	soa_timer_t *timer, f64seconds dt)
{
	timer->counter.seconds += dt.seconds;
}

bool soa_timer_do_frame(
	soa_timer_t *timer,
	f64 interval)
{
	if (timer->counter.seconds >= interval) {
		timer->counter.seconds -= interval;
		timer->dt.seconds = interval;
		return true;
	}
	return false;
}

f64 soa_timer_delta_seconds(
	const soa_timer_t *timer)
{
	return timer->dt.seconds;
}
