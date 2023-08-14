#ifndef GAME_TIMER_H
#define GAME_TIMER_H

#include <primitive_types.h>

typedef struct game_timer_t {
	f64seconds counter;
	f64seconds dt;
} game_timer_t;

game_timer_t game_timer_init(void);
void game_timer_fini(game_timer_t *timer);
void game_timer_tick(game_timer_t *timer, f64seconds dt);
bool game_timer_frame(game_timer_t *timer, f64 interval);
f64 game_timer_delta_seconds(const game_timer_t *timer);

#endif // GAME_TIMER_H
