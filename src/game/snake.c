#include <stdio.h>
#include <time.h>

#include "game.h"
#include "shapes.h"

Rect *Tail;
Rect Head;
Rect Apple;

int TailLength = 0;

typedef enum {
    up,
    down,
    left,
    right
} Direction;

Direction currDirection = up;

char *str;

int roundint(int n) {
    int a = (n / 20) * 20;
    int b = a + 20;
    return (n - a > b - n) ? b : a;
}

void growSnake(void) {
    Rect Temp;
    Temp.rect.h = Temp.rect.w = 20;
    Temp.color.a = 255;
    Temp.color.r = 255;
    Temp.color.g = 255;
    Temp.color.b = 255;

    switch (currDirection) {
        case up:
            if (TailLength == 0) {
                Temp.rect.y = Head.rect.y + Head.rect.h;
                Temp.rect.x = Head.rect.x;
            } else {
                Temp.rect.x = Tail[TailLength - 1].rect.x;
                Temp.rect.y = Tail[TailLength - 1].rect.y + Tail[TailLength - 1].rect.h;
            }
            break;
        case down:
            if (TailLength == 0) {
                Temp.rect.y = Head.rect.y - Head.rect.h;
                Temp.rect.x = Head.rect.x;
            } else {
                Temp.rect.x = Tail[TailLength - 1].rect.x;
                Temp.rect.y = Tail[TailLength - 1].rect.y - Tail[TailLength - 1].rect.h;
            }
            break;
        case left:
            if (TailLength == 0) {
                Temp.rect.y = Head.rect.y;
                Temp.rect.x = Head.rect.x + Head.rect.h;
            } else {
                Temp.rect.x = Tail[TailLength - 1].rect.x + Tail[TailLength - 1].rect.w;
                Temp.rect.y = Tail[TailLength - 1].rect.y;
            }
            break;
        case right:
            if (TailLength == 0) {
                Temp.rect.y = Head.rect.y;
                Temp.rect.x = Head.rect.x - Head.rect.h;
            } else {
                Temp.rect.x = Tail[TailLength - 1].rect.x - Tail[TailLength - 1].rect.w;
                Temp.rect.y = Tail[TailLength - 1].rect.y;
            }
            break;
        default:
            break;
    }
    Tail[TailLength] = Temp;
    TailLength++;
}

void resetApple(void) {
    srand((unsigned)time(NULL));
    Apple.rect.x = roundint(rand() % (SCREEN_W - 20));
    Apple.rect.y = roundint(rand() % (SCREEN_H - 20));
}

char *getScore(void) {
    sprintf(str, "%d", TailLength);
    return str;
}

int getScoreInt(void) {
    return TailLength;
}

bool isCollision(void) {
    int ax = Apple.rect.x, ay = Apple.rect.y, ah = Apple.rect.h, aw = Apple.rect.w;
    int hx = Head.rect.x, hy = Head.rect.y, hh = Head.rect.h, hw = Head.rect.w;
    switch (currDirection) {
        case up:
            if (hx + hw > ax && hx < ax + aw && hy == ay + ah) return true;
            break;

        case down:
            if (ax + aw > hx && ax < hx + hw && ay == hy + hh) return true;
            break;

        case left:
            if (hy + hh > ay && hy < ay + ah && hx == ax + aw) return true;
            break;

        case right:
            if (ay + ah > hy && ay < hy + hh && hx + hw == ax) return true;
            break;

        default:
            break;
    }
    return false;
}

bool checkSnakeCollision(void) {
    int headX, headY, headW, headH, tailX, tailY, tailW, tailH;
    headX = Head.rect.x;
    headY = Head.rect.y;
    headW = Head.rect.w;
    headH = Head.rect.h;

    for (size_t i = 0; i < TailLength; ++i) {
        Rect t = Tail[i];
        tailX = t.rect.x;
        tailY = t.rect.y;
        tailH = t.rect.h;
        tailW = t.rect.w;
        switch (currDirection) {
            case up:
                if (headX + headH > tailX && headX < tailX + tailW && headY == tailY + tailH) {
                    return true;
                }
                break;
            case down:
                if (headX + headH > tailX && headX < tailX + tailW && tailY == headY + headH) {
                    return true;
                }
                break;
            case left:
                if (headY + headH > tailY && headY < tailY + tailH && headX == tailX + tailW) {
                    return true;
                }
                break;
            case right:
                if (headY + headH > tailY && headY < tailY + tailH && tailX == headX + headW) {
                    return true;
                }
                break;
            default:
                break;
        }
    }
    return false;
}

void followHead(void) {
    int x, y, prevX, prevY;
    switch (currDirection) {
        case up:
            y = Head.rect.y = Head.rect.y - Head.rect.h;
            x = Head.rect.x;

            for (size_t i = 0; i < TailLength; ++i) {
                prevX = Tail[i].rect.x;
                prevY = Tail[i].rect.y - Head.rect.h;
                Tail[i].rect.x = x;
                Tail[i].rect.y = y + Head.rect.h;
                x = prevX;
                y = prevY;
            }
            break;

        case down:
            y = Head.rect.y = Head.rect.y + Head.rect.h;
            x = Head.rect.x;

            for (size_t i = 0; i < TailLength; ++i) {
                prevX = Tail[i].rect.x;
                prevY = Tail[i].rect.y + Head.rect.h;
                Tail[i].rect.x = x;
                Tail[i].rect.y = y - Head.rect.h;
                x = prevX;
                y = prevY;
            }
            break;

        case left:
            y = Head.rect.y;
            x = Head.rect.x = Head.rect.x - Head.rect.w;

            for (size_t i = 0; i < TailLength; ++i) {
                prevX = Tail[i].rect.x - Head.rect.w;
                prevY = Tail[i].rect.y;
                Tail[i].rect.x = x + Head.rect.w;
                Tail[i].rect.y = y;
                x = prevX;
                y = prevY;
            }
            break;

        case right:
            y = Head.rect.y;
            x = Head.rect.x = Head.rect.x + Head.rect.w;

            for (size_t i = 0; i < TailLength; ++i) {
                prevX = Tail[i].rect.x + Head.rect.w;
                prevY = Tail[i].rect.y;
                Tail[i].rect.x = x - Head.rect.w;
                Tail[i].rect.y = y;
                x = prevX;
                y = prevY;
            }
            break;

        default:
            break;
    }
}

void goToOtherSide(void){
    int hx, hy;
    hx = Head.rect.x;
    hy = Head.rect.y;
    if (hy < 0) Head.rect.y = SCREEN_H;
    else if  (hy > SCREEN_H) Head.rect.y = 0; 

    if (hx < 0) Head.rect.x = SCREEN_W;
    else if (hx > SCREEN_W) Head.rect.x = 0;
}

void moveSnake(void) {
    if (isCollision()) {
        growSnake();
        resetApple();
    }
    if (checkSnakeCollision()) isRunning = false;
    goToOtherSide();
    followHead();
}

void changeDirection(int dir) {
    switch (dir) {
        case 0:
            if (currDirection == up)
                break;
            if (currDirection == down)
                break;
            currDirection = up;
            break;
        case 1:
            if (currDirection == down)
                break;
            if (currDirection == up)
                break;
            currDirection = down;
            break;
        case 2:
            if (currDirection == left)
                break;
            if (currDirection == right)
                break;
            currDirection = left;
            break;
        case 3:
            if (currDirection == right)
                break;
            if (currDirection == left)
                break;
            currDirection = right;
            break;
        default:
            break;
    }
}

void initApple(void) {
    Apple.color.r = 255;
    Apple.color.a = 255;
    Apple.color.g = 0;
    Apple.color.b = 0;
    Apple.rect.h = Apple.rect.w = 20;
    resetApple();
}

void initSnake(void) {
    // allocate memory for snake on heap
    Tail = (Rect *)malloc(sizeof(Rect) * 256);
    Head.rect.h = Head.rect.w = 20;
    Head.rect.x = SCREEN_W / 2;
    Head.rect.y = SCREEN_H / 2;
    Head.color.r = 160;
    Head.color.g = 142;
    Head.color.b = 230;
    Head.color.a = 255;
    str = (char *)malloc(sizeof(char) * 256);
}
void renderSnake(SDL_Renderer *ren) {
    drawRect(ren, &Head.rect, &Head.color);
    drawRect(ren, &Apple.rect, &Apple.color);
    for (size_t i = 0; i < TailLength; ++i) {
        Rect temp = Tail[i];
        drawRect(ren, &temp.rect, &temp.color);
    }
}

void cleanSnake(void) {
    // free memory of the snake tail
    free(Tail);
    free(str);
}
