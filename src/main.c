#include <stdio.h>

#include "game.h"

int main() {
    const int FPS = 30;
    const int frameDelay = 2 * 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    init("Lets gooOo!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, false);
    while (isRunning) {
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
        frameStart = SDL_GetTicks();
        handleEvents();
        update();
        render();
    }
    printf("Game over\n");
    clean();
    return 0;
}