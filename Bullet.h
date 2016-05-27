#ifndef BULLET_H
#define BULLET_H

#include<SDL.h>
#include<SDL_image.h>
#include <math.h>

#define PI 3.14159265

class Bullet
{
public:
    double x;
    double y;
    double angle;
    SDL_Texture *texture;
    SDL_Rect rect;
    SDL_Renderer *renderer;
    double bullet_velocity;
    Bullet(double x,double y,double angle,double bullet_velocity,SDL_Renderer* renderer);
    void logic();
    void draw();
};
#endif // BULLET_H
