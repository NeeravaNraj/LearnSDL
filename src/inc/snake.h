#ifndef _SNAKE_H
#define _SNAKE_H
#include "game.h"

extern void initSnake(void);
extern void cleanSnake(void);
extern void renderSnake(SDL_Renderer *ren);
extern void moveSnake(void);
extern void changeDirection(int dir);
extern void initApple(void);
#endif