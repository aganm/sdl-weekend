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

void game_timer_tick(game_timer_t *timer, f64seconds dt)
{
	timer->counter.seconds += dt.seconds;
}

bool game_timer_frame(game_timer_t *timer, f64 interval)
{
	if (timer->counter.seconds >= interval) {
		timer->counter.seconds -= interval;
		timer->dt.seconds = interval;
		return true;
	}
	return false;
}

f64 game_timer_delta_seconds(const game_timer_t *timer)
{
	return timer->dt.seconds;
}
