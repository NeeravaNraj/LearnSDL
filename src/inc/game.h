#ifndef __GAME_H
#define __GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stddef.h>
#define SCREEN_W 1280
#define SCREEN_H 720

typedef struct {
    Uint8 r, g, b, a;
} Color;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} App;

typedef struct {
    SDL_Rect rect;
    Color color;
} Rect;
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
extern bool isRunning;
#endif