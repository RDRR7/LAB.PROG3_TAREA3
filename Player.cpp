#include "Player.h"

Player::Player(double x,double y, double velocity,SDL_Renderer* renderer)
{
    this->x=x;
    this->y=y;
    this->renderer=renderer;
    this->velocity = velocity;

    int w,h;
    texture = IMG_LoadTexture(renderer, "personaje.png");
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    rect.x = 0;
    rect.y = 100;
    rect.w = w;
    rect.h = h;
}

void Player::logic()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        rect.y-=velocity;
    }
    if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    {
        rect.y+=velocity;
    }
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        rect.x+=velocity;
    }
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        rect.x-=velocity;
    }
}

void Player::draw()
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Player::hitObstacle()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        rect.y+=velocity;
    }
    if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    {
        rect.y-=velocity;
    }
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        rect.x-=velocity;
    }
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        rect.x+=velocity;
    }
}
