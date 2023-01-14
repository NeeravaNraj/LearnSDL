#ifndef __GAME_H
#define __GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stddef.h>

// SDL_Renderer *renderer;
extern void init(
const char *title, 
size_t xpos, 
size_t ypos, 
size_t width, 
size_t height, 
bool fullscreen);
extern void handleEvents(void);
extern void update(void);
extern void render(void);
extern void clean(void);
extern bool running(void);

#endif