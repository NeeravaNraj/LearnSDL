#include "texmgr.h"


SDL_Texture* LoadTexture(const char *file, SDL_Renderer *ren){
    SDL_Surface *tmpSurf = IMG_Load(file);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, tmpSurf);
    SDL_FreeSurface(tmpSurf);
    return texture;
}