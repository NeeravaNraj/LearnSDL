#ifndef __GAME_OBJ
#define __GAME_OBJ
#include "game.h"

typedef struct {
    SDL_Texture* tex;
    SDL_Rect srcR, destR;
    SDL_Renderer* renderer;
} GameObj;

extern GameObj* getGameObj(const char* texSheet, SDL_Renderer* ren);
extern void updateObj(
    GameObj* obj,
    int xpos,
    int ypos,
    int srcW,
    int srcH,
    int destW,
    int destH);
extern void renderObj(GameObj* obj);
extern void freeGameObj(GameObj* obj);
#endif