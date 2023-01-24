#include "game.h"

void drawRect(SDL_Renderer *ren, SDL_Rect *rect, Color *color) {
    SDL_SetRenderDrawColor(ren, color->r, color->g, color->b, color->a);  // Setting window color
    SDL_RenderDrawRect(ren, rect);
    SDL_RenderFillRect(ren, rect);
}