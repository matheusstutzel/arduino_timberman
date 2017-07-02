#include <SDL2/SDL.h>
#include <enemy.h>
void movePlayer(int Dx,int Dy);
void getPosPlayer(int *x,int *y);
void drawPlayer(SDL_Renderer*,int tile);
void drawPlayerView(SDL_Renderer* renderer,int tile,int w,int h); 
void combat(enemy *e);
