#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

typedef float    f32;
typedef double   f64;
typedef uint8_t  u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t   usize;

typedef struct f64seconds    { f64 seconds;       } f64seconds;
typedef struct entity        { u32 slot;          } entity;
typedef struct component     { u32 slot;          } component; // DEAD CODE
typedef struct data_position { f32 x, y;          } data_position;
typedef struct data_speed    { f32 val;           } data_speed;
typedef struct data_color    { u8 r, g, b, a ;    } data_color;
typedef struct data_size     { f32 width, height; } data_size;

// DEAD CODE
static component     *position_component = NULL;
static component     *color_component    = NULL;
static component     *size_component     = NULL;

static data_position *position           = NULL;
static data_speed    *speed              = NULL;
static data_color    *color              = NULL;
static data_size     *size               = NULL;

static usize          entity_count       = 0;
static usize          entity_max         = 0;

void create_entities(
	entity *out,
	usize count)
{
	const usize new_count = entity_count + count;
	const bool resize = new_count > entity_max;
	if (resize) {
		position = realloc(position, sizeof(*position) * new_count);
		speed    = realloc(speed,    sizeof(*speed)    * new_count);
		color    = realloc(color,    sizeof(*color)    * new_count);
		size     = realloc(size,     sizeof(*size)     * new_count);
	}
	for (usize i = 0; i < count; i++) {
		out[i] = (entity){ .slot = entity_count + i };
	}
	entity_count = new_count;
	entity_max   = new_count;
}

void move_on_inputs(
	data_position    *e_position,
	const data_speed *e_speed,
	const usize      entity_count,
	const f64seconds dt,
	const bool       up,
	const bool       down,
	const bool       left,
	const bool       right)
{
	for (usize e = 0; e < entity_count; e += 1) {
		const f32 move = e_speed[e].val * (f32)dt.seconds;
		e_position[e].x -= move * left;
		e_position[e].x += move * right;
		e_position[e].y -= move * up;
		e_position[e].y += move * down;
	}
}

void render_square(
	const data_position *e_position,
	const data_size     *e_size,
	const data_color    *e_color,
	const usize         entity_count,
	SDL_Renderer        *renderer)
{
	for (usize e = 0; e < entity_count; e += 1) {
		SDL_FRect rect = {
			.x = e_position[e].x,
			.y = e_position[e].y,
			.w = e_size[e].width,
			.h = e_size[e].height
		};
		SDL_Color color = {
			.r = e_color[e].r,
			.g = e_color[e].g,
			.b = e_color[e].b,
			.a = e_color[e].a,
		};
		// TODO: Batch this up
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRectF(renderer, &rect);
	}
}

void spawn_entities_in_rect(
	int min_x,
	int max_x,
	int min_y,
	int max_y,
	usize count)
{
	entity entities[count];
	create_entities(entities, count);
	for (usize ii = 0; ii < count; ++ii) {
		const usize i  = entities[ii].slot;
		position[i].x  = rand() % (max_x - min_x) + min_x;
		position[i].y  = rand() % (max_y - min_y) + min_y;
		size[i].width  = rand() % 50 + 10;
		size[i].height = rand() % 50 + 10;
		speed[i].val   = rand() % 1000 + 200;
		color[i].r     = rand() % 255;
		color[i].g     = rand() % 255;
		color[i].b     = rand() % 255;
		color[i].a     = 255;
	}
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	/* Application stuff. */
	const char   *title            = argc >= 1 ? argv[0] : "NO_TITLE";
	SDL_Window   *window           = SDL_CreateWindow(title, -1, -1, -1, -1, SDL_WINDOW_RESIZABLE);
	SDL_Renderer *renderer         = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	u64           old_ticks        = SDL_GetPerformanceCounter();
	const u64     ticks_per_second = SDL_GetPerformanceFrequency();

	/* Maximime window in full screen area. */
	int top, left, bottom, right;
	SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right);
	SDL_Rect bounds;
	SDL_GetDisplayUsableBounds(0, &bounds);
	const SDL_Rect display = { bounds.x, bounds.y + top, bounds.w, bounds.h - top };
	SDL_SetWindowPosition(window, display.x, display.y);
	SDL_SetWindowSize(window, display.w, display.h);
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	/* Spawn initial entities. */
	spawn_entities_in_rect(0, w, 0, h, 1024);

	/* Game loop. */
	bool running = true;
	while (running) {
		/* Delta time. */
		const u64 new_ticks = SDL_GetPerformanceCounter();
		const u64 diff_ticks = new_ticks - old_ticks;
		const f64seconds delta_time = { (f64)diff_ticks / (f64)ticks_per_second };
		old_ticks = new_ticks;

		/* Inputs. */
		static bool up = false;
		static bool down = false;
		static bool left = false;
		static bool right = false;
		bool        space = false;
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.scancode) {
					case SDL_SCANCODE_SPACE: space = true; break;
					case SDL_SCANCODE_UP:    up    = true; break;
					case SDL_SCANCODE_DOWN:  down  = true; break;
					case SDL_SCANCODE_LEFT:  left  = true; break;
					case SDL_SCANCODE_RIGHT: right = true; break;
					default:                               break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.scancode) {
					case SDL_SCANCODE_UP:    up    = false; break;
					case SDL_SCANCODE_DOWN:  down  = false; break;
					case SDL_SCANCODE_LEFT:  left  = false; break;
					case SDL_SCANCODE_RIGHT: right = false; break;
					default:                                break;
				}
				break;

			default:
				break;
			};
		}

		/* Gameplay. */
		if (space) spawn_entities_in_rect(0, w, 0, h, 1024);
		move_on_inputs(position, speed, entity_count, delta_time, up, down, left, right);
		render_square(position, size, color, entity_count, renderer);

		/* Present. */
		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
	}

	SDL_Quit();
}
