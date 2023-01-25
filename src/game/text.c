#include "game.h"
#include "text.h"

SDL_Color color = {255, 255, 255};
TTF_Font *font;

void initFont(int size){
   font = TTF_OpenFont("./assets/Fonts/font.ttf", size); 
}

SDL_Texture *createTextArea(SDL_Renderer *ren, const char *text){
    SDL_Surface *surfaceText = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *txrText = SDL_CreateTextureFromSurface(ren, surfaceText);
    SDL_FreeSurface(surfaceText);
    return txrText;
}

void putText(SDL_Renderer *ren, const char *text, TextPos pos){
    SDL_Texture *txrText = createTextArea(ren, text);
    SDL_Rect rect = {
        .x = pos.x,
        .y = pos.y,
        .h = pos.h,
        .w = pos.w
    };
    SDL_RenderCopy(ren, txrText, NULL, &rect);
}