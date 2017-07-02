#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "enemy.h"

void movePlayer(int Dx,int Dy);
void getPosPlayer(int *x,int *y);
void drawPlayer(SDL_Renderer* renderer, SDL_Window* window, int tile);
void drawPlayerView(SDL_Renderer* renderer,int tile,int w,int h, int vision);
void combat(enemy *e);
void playerInit(SDL_Window* window);
