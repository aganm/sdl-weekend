#include <SDL2/SDL.h>
#include <bundle_types.h>
#include <primitive_types.h>

typedef struct game_data_t game_data_t;
usize game_data_size(void);
void game_init(game_data_t* data, SDL_Renderer* renderer);
void game_fini(game_data_t* data);
void game_handle_sdl_event(game_data_t* data, const SDL_Event* event);
void game_tick(game_data_t* data, f64seconds tick_dt, f32v2 viewport);

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	const char *title = argc >= 1 ? argv[0] : "NO_TITLE";
	SDL_Window *window = SDL_CreateWindow(title, -1, -1, -1, -1, SDL_WINDOW_RESIZABLE);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	u64 old_ticks = SDL_GetPerformanceCounter();

	/* Maximime window in full screen area. */
	int top, left, bottom, right;
	SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right);
	SDL_Rect bounds;
	SDL_GetDisplayUsableBounds(0, &bounds);
	const SDL_Rect display = { bounds.x, bounds.y + top, bounds.w, bounds.h - top };
	SDL_SetWindowPosition(window, display.x, display.y);
	SDL_SetWindowSize(window, display.w, display.h);

	game_data_t *game_data = SDL_malloc(game_data_size());
	game_init(game_data, renderer);

	bool running = true;
	while (running) {
		const u64 new_ticks = SDL_GetPerformanceCounter();
		const u64 diff_ticks = new_ticks - old_ticks;
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
			game_handle_sdl_event(game_data, &event);
		}

		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		game_tick(game_data, delta_time, (f32v2){ w, h });
		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
	}

	game_fini(game_data);
	SDL_free(game_data);

	SDL_Quit();
	return 0;
}
