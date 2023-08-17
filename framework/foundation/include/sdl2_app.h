#ifndef SDL2_APP_H
#define SDL2_APP_H

#include "types/bundle.h"
#include "types/primitive.h"

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef union SDL_Event SDL_Event;
typedef struct SDL_SceneData SDL_SceneData;

typedef struct SDL_App {
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_App;

typedef struct SDL_SceneDesc {
	u64 data_size;
	void (*init)(SDL_App* app, SDL_SceneData* data);
	void (*fini)(SDL_App* app, SDL_SceneData* data);
	void (*handle_sdl_event)(SDL_App* app, SDL_SceneData* data, const SDL_Event* event);
	void (*tick)(SDL_App* app, SDL_SceneData* data, f64seconds tick_dt, f32v2 viewport);
} SDL_SceneDesc;

#endif // SDL2_APP_H
