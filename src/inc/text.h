#ifndef _TEXT_H
#define _TEXT_H
#include <SDL2/SDL_ttf.h>

typedef struct {
    int x, y, w, h;
} TextPos;

void initFont(int size);
void putText(SDL_Renderer *ren, const char *text, TextPos pos);
#endif
