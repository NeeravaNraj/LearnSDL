#include "gameobj.h"

#include <stdlib.h>

#include "texmgr.h"

GameObj* getGameObj(const char* texSheet, SDL_Renderer* ren) {
    GameObj* obj = malloc(sizeof(GameObj));
    obj->renderer = ren;
    obj->tex = LoadTexture(texSheet, obj->renderer);
    return obj;
}

void updateObj(
    GameObj* obj,
    int xpos, 
    int ypos, 
    int srcW, 
    int srcH, 
    int destW, 
    int destH
) {
    obj->srcR.w = srcW;
    obj->srcR.h = srcH;
    obj->srcR.x = 0;
    obj->srcR.y = 0;

    obj->destR.w = destW;
    obj->destR.h = destH;
    obj->destR.x = xpos;
    obj->destR.y = ypos;
}

void renderObj(GameObj* obj) {
    SDL_RenderCopy(obj->renderer, obj->tex, &obj->srcR, &obj->destR);
}

void freeGameObj(GameObj* obj){
    free(obj);
}