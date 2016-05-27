
#include<iostream>
#include<list>
#include <stdlib.h>
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Obstacle.h"
#include <time.h>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background;
SDL_Rect rect_background;

int screen_width = 500;
int screen_height= 250;

double getAngle(double distance_x, double distance_y)
{
    double angle = atan (distance_y/distance_x) * 180 / PI;
    if(distance_x<0)
    {
        angle=180+angle;
    }
    if(distance_x>0 && distance_y<0)
    {
        angle=360+angle;
    }
    return angle;
}

bool isOutOfBounds(int x, int y)
{
    return x>screen_width || x<0 || y>screen_height || y<0;
}

bool collisionCheck(SDL_Rect r1, SDL_Rect r2)
{
    if(r1.x > r2.x+r2.w)//Muy a la derecha
        return false;
    if(r1.x+r1.w < r2.x)//Muy a la izquierda
        return false;
    if(r1.y > r2.y+r2.h)//Muy abajo
        return false;
    if(r1.y+r1.h < r2.y)//Muy arriba
        return false;
    return true;
}

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, screen_width/*WIDTH*/, screen_height/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    srand(time(0));
    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    list<Bullet*>bullets;
    list<Enemy*>enemies;
    list<Obstacle*>obstacles;

    int frame=0;
    int level=1;
    int enemiesKilled=0;
    double player_velocity=3;
    double last_frame_ticks=SDL_GetTicks();
    bool levelBool=true;

    Player *player = new Player(30,30,player_velocity,renderer);

    obstacles.push_back(new Obstacle(rand()%(500-32), rand()%(250-32), renderer));
    obstacles.push_back(new Obstacle(rand()%(500-32), rand()%(250-32), renderer));
    obstacles.push_back(new Obstacle(rand()%(500-32), rand()%(250-32), renderer));

    while(true)//Main Loop
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
        }

        int mouse_x, mouse_y;

        SDL_GetMouseState( &mouse_x, &mouse_y );

        if(frame%30==0)//Crea las balas
        {
            double dist_x = mouse_x - player->rect.x;
            double dist_y = player->rect.y - mouse_y;
            bullets.push_back(new Bullet(player->rect.x,player->rect.y,getAngle(dist_x,dist_y),8,renderer));
        }

        if(frame%100==0)//Crea los enemigos
        {
            enemies.push_back(new Enemy(0,rand()%screen_height-32,renderer));
        }

        SDL_RenderCopy(renderer, background, NULL, &rect_background);

        for(list<Bullet*>::iterator i=bullets.begin();//Movimiento de las balas
            i!=bullets.end();
            i++)
        {
            Bullet* bullet_actual = *i;

            bullet_actual->logic();
            bullet_actual->draw();

            if(isOutOfBounds(bullet_actual->x,bullet_actual->y))
            {
                list<Bullet*>::iterator to_erase=i;
                i--;
                bullets.erase(to_erase);
                delete bullet_actual;
            }
        }

        for(list<Enemy*>::iterator i=enemies.begin();//Movimiento de los enemigos
            i!=enemies.end();
            i++)
        {
            Enemy* current_enemy = *i;

            current_enemy->logic();
            current_enemy->draw();

            if(isOutOfBounds(current_enemy->x,current_enemy->y))
            {
                list<Enemy*>::iterator to_erase=i;
                i--;
                enemies.erase(to_erase);
                delete current_enemy;
            }
        }

        player->logic();//Movimiento jugador
        player->draw();

        for(list<Obstacle*>::iterator i=obstacles.begin();//Dibuja los obstaculos
            i!=obstacles.end();
            i++)
        {
            Obstacle* obstacle_actual=*i;
            obstacle_actual->draw();
            if(collisionCheck(player->rect, obstacle_actual->rect)){
                player->hitObstacle();
            }
        }

        for(list<Obstacle*>::iterator k=obstacles.begin();//Revisa colisiones
                k!=obstacles.end();
                k++)
        {
            Obstacle* obstacle_actual=*k;
            for(list<Enemy*>::iterator i=enemies.begin();
                i!=enemies.end();
                i++)
            {
                Enemy*current_enemy = *i;
                if(collisionCheck(current_enemy->rect, obstacle_actual->rect))
                {
                    list<Enemy*>::iterator to_erase_enemy=i;
                    i--;
                    enemies.erase(to_erase_enemy);
                    delete current_enemy;
                    break;
                }
                for(list<Bullet*>::iterator j=bullets.begin();
                    j!=bullets.end();
                    j++)
                {
                    Bullet*current_bullet = *j;
                    if(collisionCheck(current_enemy->rect,current_bullet->rect))
                    {
                        enemiesKilled++;
                        list<Bullet*>::iterator to_erase=j;
                        j--;
                        bullets.erase(to_erase);
                        delete current_bullet;

                        list<Enemy*>::iterator to_erase_enemy=i;
                        i--;
                        enemies.erase(to_erase_enemy);
                        delete current_enemy;
                        break;
                    }
                    else if(collisionCheck(current_bullet->rect, obstacle_actual->rect))
                    {
                        list<Bullet*>::iterator to_erase=j;
                        j--;
                        bullets.erase(to_erase);
                        delete current_bullet;
                        break;
                    }
                }
            }
        }

        if(enemiesKilled==(10*level))//Cambia de nivel
            level++;

        if(level==2 && levelBool)//Cambia las imagnes de los fondos
        {
            background = IMG_LoadTexture(renderer,"fondo_2.jpg");
            obstacles.push_back(new Obstacle(rand()%(500-32), rand()%(250-32), renderer));
            levelBool=false;
        }
        else if(level==3 && !levelBool)
        {
            background = IMG_LoadTexture(renderer,"fondo_3.png");
            obstacles.push_back(new Obstacle(rand()%(500-32), rand()%(250-32), renderer));
            levelBool=true;
        }
        else if(level==4)
        {
            cout<<"Thanks for playing"<<endl;
            exit(0);
        }

        SDL_RenderPresent(renderer);
        double current_ticks = SDL_GetTicks();
        double ticks_diff = current_ticks-last_frame_ticks;
        double sleep_time = 17-ticks_diff;
        last_frame_ticks=SDL_GetTicks();
        if(sleep_time>0)
            SDL_Delay(sleep_time);
        frame++;
    }
	return 0;
}
