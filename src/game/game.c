#include "game.h"
#include <stdio.h>
#include "gameobj.h"
#include "texmgr.h"

bool isRunning;
SDL_Window *window;
SDL_Renderer *renderer;
GameObj *playerTex;
int count = 0;

void init(
    const char *title,
    size_t xpos,
    size_t ypos,
    size_t width,
    size_t height,
    bool fullscreen) {
    Uint32 flags = 0;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        printf("Subsystems Initialized!\n");
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);  // Attemp to create a window
        if (!window) {
            // Failed to create a window
            printf("Error window creation failed!\n %s", SDL_GetError());
            return;
        } else {
            renderer = SDL_CreateRenderer(window, -1, 0);  // Attempt to create a renderer for window
            if (!renderer) {
                // Failed to create a renderer
                printf("Error renderer creation failed!\n %s", SDL_GetError());
                return;
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Setting window color
            printf("Renderer initialized\n");
        }

        isRunning = true;  // Starts game loop

        playerTex = getGameObj("assets/steve.png", renderer);
    } else {
        // Initialization has failed
        printf("Error Initializing!\n %s", SDL_GetError());
        return;
    }
}

void handleEvents(void) {
    SDL_Event ev;
    SDL_PollEvent(&ev);
    switch (ev.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void update(void) {
    ++count;
    updateObj(playerTex, count, count, 448, 556, 256, 286);
}

bool running(void) {
    return isRunning;
}

void render(void) {
    SDL_RenderClear(renderer);
    // Render stuff from here on out
    renderObj(playerTex);
    SDL_RenderPresent(renderer);
}

void clean(void) {
    freeGameObj(playerTex);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game cleaned\n");
}