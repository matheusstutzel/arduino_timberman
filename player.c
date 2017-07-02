#include <player.h>
#define new_max(x,y) ((x) >= (y)) ? (x) : (y)
#define new_min(x,y) ((x) <= (y)) ? (x) : (y)
int x = 1;
int y = 1;
int atk = 10;
int def = 10;
int hp = 100;
float HPMAX =100.0;
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
SDL_Rect rect = {0,0,tile,tile- (tile/10)};

 SDL_SetRenderDrawColor(renderer,0,0,255,0x00);
   rect.x=x*tile;
   rect.y=y*tile;

   SDL_RenderFillRect(renderer,&rect);

   SDL_SetRenderDrawColor(renderer,0,255,0,0x00);
	rect.h=(tile/10);
	rect.w=(int)((hp/HPMAX)*(tile));
   rect.x=x*tile;
   rect.y=y*tile+(tile-(tile/10));

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

void combat(enemy *e){
	printf("COMbATEU %d %d\n",hp,e->hp);
	e->hp-= new_max(10,e->def-atk);
	hp-= new_max(10,def-e->atk);
}
