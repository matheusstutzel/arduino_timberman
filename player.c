#include <player.h>

int x = 1;
int y = 1;
int rv = 10;

void movePlayer(int Dx,int Dy){
 x+=Dx;
 y+=Dy;
}
void getPosPlayer(int *px,int *py){
 *px = x;
 *py = y;
}

void drawPlayer(SDL_Renderer* renderer, int tile){
 SDL_Rect rect = {0,0,tile,tile};

 SDL_SetRenderDrawColor(renderer,0,0,255,0x00);
   rect.x=x*tile;
   rect.y=y*tile;

   SDL_RenderFillRect(renderer,&rect);
}
void drawPlayerView(SDL_Renderer* renderer,int tile,int w,int h){
 SDL_Rect rect = {0,0,tile,tile};

 SDL_SetRenderDrawColor(renderer,0,0,0,0x00);
 for(int i = 0; i < w/tile; i++)for(int j = 0; j < h/tile; j++){
   rect.x=i*tile;
   rect.y=j*tile;

   if(!((i-x)*(i-x) +(j - y)*(j - y) < rv * rv))SDL_RenderFillRect(renderer,&rect);
 }
}
