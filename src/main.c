#include <stdio.h>

#include "game.h"

int main() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    init("Lets gooOo!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, false);
    while (isRunning) {
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) SDL_Delay(10 * frameDelay - frameTime);
        frameStart = SDL_GetTicks();
        handleEvents();
        update();
        render();
    }
    clean();
    return 0;
}