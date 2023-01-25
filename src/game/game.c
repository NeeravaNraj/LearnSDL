#include "game.h"

#include <stdio.h>

#include "shapes.h"
#include "snake.h"
#include "text.h"

bool isRunning;
App app;
static TextPos pos = {
    .x = 15,
    .y = 3,
    .h = 64,
    .w = 32
};
static TextPos pos2 = {
    .x = 15,
    .y = 3,
    .h = 64,
    .w = 64
};

SDL_Event ev;

void init(
    const char *title,
    size_t xpos,
    size_t ypos,
    size_t width,
    size_t height,
    bool fullscreen) {
    Uint32 windowFlags = 0;
    Uint32 renderFlags = SDL_RENDERER_ACCELERATED;

    if (fullscreen) {
        windowFlags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        printf("Subsystems Initialized!\n");
        app.window = SDL_CreateWindow(title, xpos, ypos, width, height, windowFlags);  // Attemp to create a window
        if (!app.window) {
            // Failed to create a window
            printf("Error window creation failed!\n %s", SDL_GetError());
            return;
        } else {
            app.renderer = SDL_CreateRenderer(app.window, -1, renderFlags);  // Attempt to create a renderer for window
            if (!app.renderer) {
                // Failed to create a renderer
                printf("Error renderer creation failed!\n %s", SDL_GetError());
                return;
            }
            printf("Renderer initialized\n");
        }

        if (TTF_Init() < 0){
            printf("Error initializing font!\n %s", TTF_GetError());
            return;
        }
        isRunning = true;   // Starts game loop
        initFont(16);         // Sets up font
        initSnake();        // Sets up Snake body
        initApple();        // Sets up Apple

    } else {
        // Initialization has failed
        printf("Error Initializing!\n %s", SDL_GetError());
        return;
    }
}

void handleEvents(void) {
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym) {
                    case SDLK_w:
                        changeDirection(0);
                        break;
                    case SDLK_s:
                        changeDirection(1);
                        break;
                    case SDLK_a:
                        changeDirection(2);
                        break;
                    case SDLK_d:
                        changeDirection(3);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void update(void) {
    moveSnake();
}

void render(void) {
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);  // Setting window color
    SDL_RenderClear(app.renderer);
    // Render stuff from here on out
    renderSnake(app.renderer);
    if (getScoreInt() < 10) putText(app.renderer, getScore(), pos);
    else putText(app.renderer, getScore(), pos2);
    SDL_RenderPresent(app.renderer);
}

void clean(void) {
    SDL_DestroyWindow(app.window);
    SDL_DestroyRenderer(app.renderer);
    cleanSnake();
    SDL_Quit();
    printf("Game cleaned\n");
}