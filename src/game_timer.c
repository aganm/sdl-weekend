#include "game_timer.h"
#include <assert.h>

game_timer_t game_timer_init(void)
{
	return (game_timer_t){ 0 };
}

void game_timer_fini(game_timer_t *timer)
{
	(void)timer;
}

static f64 clamp_if_non_zero(
	const f64 interval,
	const f64 elapsed)
{
	assert(interval >= 0.0);
	assert(elapsed >= 0.0);

	if (interval == 0.0) {
		return elapsed;
	}
	const f64 max_multiplier = 2;
	const f64 max = interval * max_multiplier;
	const f64 clamped = elapsed > max ? max : elapsed;
	return clamped;
}

bool game_timer_tick(game_timer_t *timer, f64seconds dt, f64 interval)
{
	timer->counter.seconds += dt.seconds;
	if (timer->counter.seconds >= interval) {
		const f64 clamped_dt = clamp_if_non_zero(interval, timer->counter.seconds);
		timer->counter.seconds = 0.f;
		timer->dt.seconds = clamped_dt;
		return true;
	}
	return false;
}

f64 game_timer_delta_seconds(const game_timer_t *timer)
{
	return timer->dt.seconds;
}
