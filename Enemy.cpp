#include "Enemy.h"

Enemy::Enemy(double x, double y,SDL_Renderer* renderer)
{
    this->x=x;
    this->y=y;
    this->renderer=renderer;

    int w,h;
    texture = IMG_LoadTexture(renderer, "enemy.png");
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    rect.x = 0;
    rect.y = 100;
    rect.w = w;
    rect.h = h;
}

void Enemy::logic()
{
    this->x++;
}

void Enemy::draw()
{
    rect.x = this->x;
    rect.y = this->y;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
