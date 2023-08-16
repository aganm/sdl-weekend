#include "game.h"
#include "game_data.h"
#include <SDL2/SDL.h>
#include <primitive_types.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argc;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow(argv[0], -1, -1, -1, -1, SDL_WINDOW_RESIZABLE);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	/* Maximime window in full screen area. */
	int top, left, bottom, right;
	SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right);
	SDL_Rect bounds;
	SDL_GetDisplayUsableBounds(0, &bounds);
	const SDL_Rect display = { bounds.x, bounds.y + top, bounds.w, bounds.h - top };
	SDL_SetWindowPosition(window, display.x, display.y);
	SDL_SetWindowSize(window, display.w, display.h);

	Uint64 old_ticks = SDL_GetPerformanceCounter();

	game_data_t game_data;
	game_init(&game_data, renderer);

	bool running = true;
	while (running) {
		const Uint64 new_ticks = SDL_GetPerformanceCounter();
		const Uint64 diff_ticks = new_ticks - old_ticks;
		const f64seconds delta_time = { (f64)diff_ticks / (f64)SDL_GetPerformanceFrequency() };
		old_ticks = new_ticks;

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				running = false;
				break;
			default:
				break;
			};
			game_handle_sdl_event(&game_data, &event);
		}

		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		game_tick(&game_data, delta_time, (f32v2){ w, h });
		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
	}

	game_fini(&game_data);

	SDL_Quit();
	return 0;
}
