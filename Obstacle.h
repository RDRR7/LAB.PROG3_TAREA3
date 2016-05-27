#ifndef OBSTACLE_H
#define OBSTACLE_H
#include<SDL.h>
#include<SDL_image.h>

class Obstacle
{
    public:
        double x;
        double y;
        SDL_Texture *texture;
        SDL_Rect rect;
        SDL_Renderer *renderer;
        Obstacle(double x, double y,SDL_Renderer* renderer);
        void draw();
};

#endif // OBSTACLE_H
