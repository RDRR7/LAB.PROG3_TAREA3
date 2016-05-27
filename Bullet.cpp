#include "Bullet.h"

Bullet::Bullet(double x,double y,double angle,double bullet_velocity, SDL_Renderer* renderer)
{
    this->x=x;
    this->y=y;
    this->angle=angle;
    this->renderer = renderer;
    this->bullet_velocity=bullet_velocity;

    int w,h;
    texture = IMG_LoadTexture(renderer, "bullet.png");
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    rect.x = 0;
    rect.y = 100;
    rect.w = w;
    rect.h = h;
}

void Bullet::logic()
{
    this->x+=cos(-this->angle*PI/180)*bullet_velocity;
    this->y+=sin(-this->angle*PI/180)*bullet_velocity;
}

void Bullet::draw()
{
    rect.x = this->x;
    rect.y = this->y;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
