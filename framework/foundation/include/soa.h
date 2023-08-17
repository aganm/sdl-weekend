#pragma once

#include <types/primitive.h>

enum {
	SOA_LIMIT = 4096,
	SOA_CLEAR_COUNT = 1,
};

typedef struct soa_slot_t { 
	u32 idx;
} soa_slot_t;

typedef struct soa_entity_t {
	usize count;
	usize num_free_slots;
	soa_slot_t free_slots[SOA_LIMIT];
	u8bool is_occupied[SOA_LIMIT];
} soa_entity_t;

typedef struct soa_timer_t {
	f64seconds counter;
	f64seconds dt;
} soa_timer_t;

#define SOA_ENTITY_INIT \
	{ ._ent = { \
		.count = SOA_CLEAR_COUNT, \
		.is_occupied = { [SOA_CLEAR_COUNT - 1] = false }, \
	} } \

usize soa_round_up(usize number, usize multiple);
usize soa_simd_count(usize vector_size, usize scalar_size, usize count);

soa_slot_t soa_new_slot1(soa_entity_t *entity);
void soa_free_slot(soa_entity_t *entity, const soa_slot_t *slots, usize slot_count);
void soa_clear(soa_entity_t *entity);

soa_timer_t soa_timer_init(void);
void soa_timer_fini(soa_timer_t *timer);
void soa_timer_tick(soa_timer_t *timer, f64seconds dt);
bool soa_timer_do_frame(soa_timer_t *timer, f64 interval);
f64 soa_timer_delta_seconds(const soa_timer_t *timer);
