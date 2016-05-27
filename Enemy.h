#ifndef ENEMY_H
#define ENEMY_H

#include<SDL.h>
#include<SDL_image.h>

class Enemy
{
    public:
        double x;
        double y;
        SDL_Texture *texture;
        SDL_Rect rect;
        SDL_Renderer *renderer;
        Enemy(double x, double y,SDL_Renderer* renderer);
        void logic();
        void draw();
};

#endif // ENEMY_H
