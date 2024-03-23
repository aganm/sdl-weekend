#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include "mesh.h"

typedef float    f32;
typedef double   f64;
typedef uint8_t  u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t   usize;

typedef struct f64seconds      { f64 seconds;       } f64seconds;
typedef struct entity          { u32 slot;          } entity;
typedef struct data_position   { f32 x, y;          } data_position;
typedef struct data_velocity   { f32 x, y;          } data_velocity;
typedef struct data_speed      { f32 val;           } data_speed;
typedef struct data_color      { u8 r, g, b, a ;    } data_color;
typedef struct data_size       { f32 width, height; } data_size;
typedef struct data_sdl_vertex { SDL_Vertex val;    } data_sdl_vertex;

typedef struct data_entity_square {
	usize          count;
	usize          max;
	data_position *position;
	data_speed    *speed;
	data_color    *color;
	data_size     *size;
} data_entity_square;

typedef struct data_entity_particle {
	usize          count;
	usize          max;
	data_position *position;
	data_velocity *velocity;
	data_color    *color;
} data_entity_particle;

typedef struct data_entity_vertex {
	usize            count;
	usize            max;
	data_sdl_vertex *sdl_vertex;
} data_entity_vertex;

bool create_entities_should_resize(
	usize      *entity_count,
	usize      *entity_max,
	entity     *out_entities,
	const usize create_count)
{
	const usize new_count = *entity_count + create_count;
	const bool resize = new_count > *entity_max;
	for (usize i = 0; i < create_count; i++) {
		out_entities[i] = (entity){ .slot = *entity_count + i };
	}
	*entity_count = new_count;
	*entity_max   = new_count;
	return resize;
}

void create_square_entities(
	data_entity_square *square,
	entity             *out_entities,
	const usize         create_count)
{
	if (create_entities_should_resize(&square->count, &square->max, out_entities, create_count))
	{
		square->position = realloc(square->position, sizeof(*square->position) * square->count);
		square->speed    = realloc(square->speed,    sizeof(*square->speed)    * square->count);
		square->color    = realloc(square->color,    sizeof(*square->color)    * square->count);
		square->size     = realloc(square->size,     sizeof(*square->size)     * square->count);
	}
}

void create_particle_entities(
	data_entity_particle *particle,
	entity               *out_entities,
	const usize           create_count)
{
	if (create_entities_should_resize(&particle->count, &particle->max, out_entities, create_count))
	{
		particle->position = realloc(particle->position, sizeof(*particle->position) * particle->count);
		particle->velocity = realloc(particle->velocity, sizeof(*particle->velocity) * particle->count);
		particle->color    = realloc(particle->color,    sizeof(*particle->color)    * particle->count);
	}
}

void create_vertex_entities(
	data_entity_vertex *vertex,
	entity             **out_entities,
	const usize        create_count)
{
	/* Heap buffer for vertex entities because could get very big. */
	static entity *buffer     = NULL;
	static usize   buffer_max = 0;
	if (buffer_max < create_count) {
		buffer = realloc(buffer, sizeof(*buffer) * create_count);
		buffer_max = create_count;
	}
	*out_entities = buffer;

	if (create_entities_should_resize(&vertex->count, &vertex->max, *out_entities, create_count))
	{
		vertex->sdl_vertex = realloc(vertex->sdl_vertex, sizeof(*vertex->sdl_vertex) * vertex->count);
	}
}

void spawn_squares_in_area(
	data_entity_square *square,
	const int           min_x,
	const int           max_x,
	const int           min_y,
	const int           max_y,
	const usize         spawn_count)
{
	entity entities[spawn_count];
	create_square_entities(square, entities, spawn_count);
	for (usize ii = 0; ii < spawn_count; ii++) {
		const usize i  = entities[ii].slot;
		square->position[i].x  = rand() % (max_x - min_x) + min_x;
		square->position[i].y  = rand() % (max_y - min_y) + min_y;
		square->size[i].width  = rand() % 50 + 10;
		square->size[i].height = rand() % 50 + 10;
		square->speed[i].val   = rand() % 1000 + 200;
		square->color[i].r     = rand() % 255;
		square->color[i].g     = rand() % 255;
		square->color[i].b     = rand() % 255;
		square->color[i].a     = 255;
	}
}

void spawn_particles_on_entity(
	data_entity_particle *particle,

	const data_position  *e_position,
	const data_size      *e_size,
	const data_color     *e_color,
	const entity          entity_target,

	const usize           spawn_count)
{
	const usize      e  = entity_target.slot;
	const f32        x  = e_position[e].x;
	const f32        y  = e_position[e].y;
	const f32        w  = e_size[e].width;
	const f32        h  = e_size[e].height;
	const data_color c  = e_color[e];

	const int min_x = x;
	const int max_x = x + w;
	const int min_y = y;
	const int max_y = y + h;

	entity entities[spawn_count];
	create_particle_entities(particle, entities, spawn_count);
	for (usize ii = 0; ii < spawn_count; ii++) {
		const usize i  = entities[ii].slot;
		particle->position[i].x  = rand() % (max_x - min_x) + min_x;
		particle->position[i].y  = rand() % (max_y - min_y) + min_y;
		particle->velocity[i].x  = rand() % 2000 - 1000;
		particle->velocity[i].y  = rand() % 2000 - 1000;
		particle->color[i]       = c;
	}
}

void move_by_velocity(
	data_position       *e_position,
	const data_velocity *e_velocity,
	const usize          entity_count,
	const f64seconds     dt)
{
	for (usize e = 0; e < entity_count; e += 1) {
		e_position[e].x += e_velocity[e].x * dt.seconds;
		e_position[e].y += e_velocity[e].y * dt.seconds;
	}
}

void move_on_inputs(
	data_position    *e_position,
	const data_speed *e_speed,
	const usize       entity_count,
	const f64seconds  dt,
	const bool        up,
	const bool        down,
	const bool        left,
	const bool        right,
	const bool        fast)
{
	const f32         fast_multiplier = fast ? 5.f : 1.f;

	for (usize e = 0; e < entity_count; e += 1) {
		const f32 move = e_speed[e].val * dt.seconds * fast_multiplier;
		e_position[e].x -= move * left;
		e_position[e].x += move * right;
		e_position[e].y -= move * up;
		e_position[e].y += move * down;
	}
}

typedef struct find_result {
	bool found;
	entity found_entity;
} find_result;

find_result find_rect_at_position(
	const data_position *e_position,
	const data_size     *e_size,
	const usize          entity_count,
	const data_position  at_position)
{
	find_result result = { 0 };
	for (usize e = 0; e < entity_count; e += 1) {
		const bool inside_rect = {
			at_position.x >= e_position[e].x &&
			at_position.y >= e_position[e].y &&
			at_position.x <= e_position[e].x + e_size[e].width &&
			at_position.y <= e_position[e].y + e_size[e].height
		};
		if (inside_rect) {
			result.found = true;
			result.found_entity = (entity){ e };
			break;
		}
	}
	return result;
}

void generate_one_size_colored_triangle_sdl_vertex(
	data_entity_vertex  *vertex,
	const data_position *e_position,
	const data_color    *e_color,
	const usize          entity_count,
	const data_size      one_size)
{
	const usize vertex_count = entity_count * 3;
	entity *vertices;
	create_vertex_entities(vertex, &vertices, vertex_count);

	for (usize e = 0; e < entity_count; e += 1)
	{
		const usize v0 = vertices[e * 3 + 0].slot;
		const usize v1 = vertices[e * 3 + 1].slot;
		const usize v2 = vertices[e * 3 + 2].slot;

		const data_position pos = e_position[e];
		const data_color    col = e_color[e];

		vertex->sdl_vertex[v0].val = (SDL_Vertex){
			.position = { pos.x - one_size.width / 2.f, pos.y - one_size.height / 2.f },
			.color    = { col.r, col.g, col.b, col.a },
		};
		vertex->sdl_vertex[v1].val = (SDL_Vertex){
			.position = { pos.x, pos.y + one_size.height / 2.f },
			.color    = { col.r, col.g, col.b, col.a },
		};
		vertex->sdl_vertex[v2].val = (SDL_Vertex){
			.position = { pos.x + one_size.width / 2.f, pos.y - one_size.height / 2.f },
			.color    = { col.r, col.g, col.b, col.a },
		};
	}
}

void generate_shadowed_triangle_sdl_vertex_from_3d_text_mesh(
	data_entity_vertex  *vertex,
	vertex_3d           *mesh,
	const usize          mesh_length,
	const data_color     color_a,
	const data_color     color_b)
{
	entity *vertices;
	create_vertex_entities(vertex, &vertices, mesh_length * 2);

	for (usize m = 0; m < mesh_length; m += 1)
	{
		const usize v = vertices[m].slot;
		vertex->sdl_vertex[v].val = (SDL_Vertex){
			/* a bit of a hack, model data is upside down :p */
			.position = { mesh[m].x + 203.f, -mesh[m].y + 503.f },
			.color    = { color_b.r, color_b.g, color_b.b, color_b.a },
		};
	}
	for (usize m = 0; m < mesh_length; m += 1)
	{
		const usize v = vertices[m + mesh_length].slot;
		vertex->sdl_vertex[v].val = (SDL_Vertex){
			/* a bit of a hack, model data is upside down :p */
			.position = { mesh[m].x + 200.f, -mesh[m].y + 500.f },
			.color    = { color_a.r, color_a.g, color_a.b, color_a.a },
		};
	}

}

void render_sdl_rect(
	const data_position *e_position,
	const data_size     *e_size,
	const data_color    *e_color,
	const usize          entity_count,
	SDL_Renderer        *renderer)
{
	for (usize e = 0; e < entity_count; e += 1) {
		// TODO: Batch this up
		const SDL_FRect rect = { e_position[e].x, e_position[e].y, e_size[e].width, e_size[e].height };
		const SDL_Color color = { e_color[e].r, e_color[e].g, e_color[e].b, e_color[e].a };
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRectF(renderer, &rect);
	}
}

void render_sdl_rect_one_size(
	const data_position *e_position,
	const data_color    *e_color,
	const usize          entity_count,
	SDL_Renderer        *renderer,
	const data_size      one_size)
{
	for (usize e = 0; e < entity_count; e += 1) {
		// TODO: Batch this up
		const SDL_FRect rect = { e_position[e].x, e_position[e].y, one_size.width, one_size.height };
		const SDL_Color color = { e_color[e].r, e_color[e].g, e_color[e].b, e_color[e].a };
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRectF(renderer, &rect);
	}
}

void render_sdl_rect_one_size_one_color(
	const data_position *e_position,
	const usize          entity_count,
	SDL_Renderer        *renderer,
	const data_size      one_size,
	const data_color     one_color)
{
	for (usize e = 0; e < entity_count; e += 1) {
		// TODO: Batch this up
		const SDL_FRect rect = { e_position[e].x, e_position[e].y, one_size.width, one_size.height };
		const SDL_Color color = { one_color.r, one_color.g, one_color.b, one_color.a };
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRectF(renderer, &rect);
	}
}

void render_sdl_geometry(
	const data_sdl_vertex *e_vertex,
	const usize            entity_count,
	SDL_Renderer          *renderer)
{
	SDL_RenderGeometry(renderer, NULL, &e_vertex[0].val, entity_count, NULL, 0);
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

	/* Entities. */
	data_entity_vertex   vertex         = { 0 };
	data_entity_square   square         = { 0 };
	data_entity_particle particle       = { 0 };
	data_size            particle_size  = { 10, 10 };
	data_color           white          = { 255, 255, 255, 255 };
	data_color           black          = { 0, 0, 0, 0 };
	data_color           orange         = { 255, 200, 42, 255 };
	data_color           dark_orange    = { 150, 100, 0, 255 };
	data_color           red            = { 255, 50, 50, 255 };
	data_color           green          = { 0, 255, 200, 255 };

	spawn_squares_in_area(&square, 0, w, 0, h, 1024);

	/* Game loop. */
	bool running = true;
	while (running) {
		/* Delta time. */
		const u64 new_ticks = SDL_GetPerformanceCounter();
		const u64 diff_ticks = new_ticks - old_ticks;
		const f64seconds delta_time = { (f64)diff_ticks / (f64)ticks_per_second };
		old_ticks = new_ticks;

		/* Inputs. */
		static bool up      = false;
		static bool down    = false;
		static bool left    = false;
		static bool right   = false;
		static bool fast    = false;
		static bool batch   = true;
		bool        space   = false;
		bool        click   = false;
		int         click_x = 0;
		int         click_y = 0;
		SDL_Event   event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:    click  = true; break;
					default:                                break;
				}
				click_x = event.button.x;
				click_y = event.button.y;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.scancode) {
					case SDL_SCANCODE_SPACE:  space = true;   break;
					case SDL_SCANCODE_W:      up    = true;   break;
					case SDL_SCANCODE_S:      down  = true;   break;
					case SDL_SCANCODE_A:      left  = true;   break;
					case SDL_SCANCODE_D:      right = true;   break;
					case SDL_SCANCODE_LSHIFT: fast  = true;   break;
					case SDL_SCANCODE_TAB:    batch = !batch; break;
					default:                                  break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.scancode) {
					case SDL_SCANCODE_W:      up    = false; break;
					case SDL_SCANCODE_S:      down  = false; break;
					case SDL_SCANCODE_A:      left  = false; break;
					case SDL_SCANCODE_D:      right = false; break;
					case SDL_SCANCODE_LSHIFT: fast  = false; break;
					default:                                 break;
				}
				break;

			default:
				break;
			};
		}

		/* Gameplay. */
		if (space) {
			spawn_squares_in_area(&square, 0, w, 0, h, 1024);
		}
		if (click) {
			find_result find = find_rect_at_position(square.position, square.size, square.count, (data_position){ click_x, click_y });
			if (find.found) spawn_particles_on_entity(&particle, square.position, square.size, square.color, find.found_entity, 10240);
		}
		move_on_inputs(square.position, square.speed, square.count, delta_time, up, down, left, right, fast);
		move_by_velocity(particle.position, particle.velocity, particle.count, delta_time);

		/* Square rendering (non batched). */
		render_sdl_rect(square.position, square.size, square.color, square.count, renderer);

		/* Particle rendering. */
		if (!batch) {
			render_sdl_rect_one_size(particle.position, particle.color, particle.count, renderer, particle_size);
		} else {
			generate_one_size_colored_triangle_sdl_vertex(&vertex, particle.position, particle.color, particle.count, particle_size);
		}

		/* Batched text. */
		if (!batch) {
			generate_shadowed_triangle_sdl_vertex_from_3d_text_mesh(&vertex, mesh_batching_off, MESH_BATCHING_OFF_LENGTH, red, orange);
		} else {
			generate_shadowed_triangle_sdl_vertex_from_3d_text_mesh(&vertex, mesh_batching_on, MESH_BATCHING_ON_LENGTH, orange, red);
		}

		/* Batched rendering. */
		render_sdl_geometry(vertex.sdl_vertex, vertex.count, renderer);
		vertex.count = 0;

		/* Present. */
		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
	}

	SDL_Quit();
}
