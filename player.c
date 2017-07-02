#include "player.h"
#define new_max(x,y) ((x) >= (y)) ? (x) : (y)
#define new_min(x,y) ((x) <= (y)) ? (x) : (y)
int x;
int y;
int atk;
int def;
int hp;
float HPMAX;
int rv;
SDL_Surface* playerSurface = NULL;
Mix_Chunk *battleSound = NULL;
void loadPlayerSurface(SDL_Window* window){
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load("C:\\Users\\Rodrigo\\Desktop\\Reativos\\hero.png");
    if( loadedSurface == NULL ){
        printf( "Unable to load image grass! SDL_image Error: %s\n", IMG_GetError() );
    }
    else{
        //Convert surface to screen format
        playerSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface(window)->format, NULL );
        if( playerSurface == NULL ){
            printf( "Unable to optimize image grass! SDL Error: %s\n", SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
}
void loadBattleSound(){
    //Load sound effects
    battleSound = Mix_LoadWAV("C:\\Users\\Rodrigo\\Desktop\\Reativos\\battleSound.wav");
    if( battleSound == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}
void playerInit(SDL_Window* window){
    x = 1;
    y = 1;
    atk = 10;
    def = 10;
    hp = 100;
    HPMAX =100.0;
    rv = 10;
    loadPlayerSurface(window);
    loadBattleSound();
}

void movePlayer(int Dx,int Dy){
    x+=Dx;
    y+=Dy;
}

void getPosPlayer(int *px,int *py){
    *px = x;
    *py = y;
}

void drawPlayer(SDL_Renderer* renderer, SDL_Window* window, int tile){
    SDL_Rect rect = {0,0,tile,tile- (tile/10)};
    rect.x=x*tile;
    rect.y=y*tile;
    SDL_BlitSurface(playerSurface, NULL, SDL_GetWindowSurface(window), &rect);

    SDL_SetRenderDrawColor(renderer,0,0,255,0x00);
	rect.h=(tile/10);
	rect.w=(int)((hp/HPMAX)*(tile));
    rect.x=x*tile;
    rect.y=y*tile+(tile-(tile/10));
    SDL_RenderFillRect(renderer,&rect);
}
void drawPlayerView(SDL_Renderer* renderer,int tile,int w,int h, int vision){
    rv = vision;
    SDL_Rect rect = {0,0,tile,tile};
    SDL_SetRenderDrawColor(renderer,0,0,0,0x00);
    for(int i = 0; i < w/tile; i++)for(int j = 0; j < h/tile; j++){
        rect.x=i*tile;
        rect.y=j*tile;
        if(!((i-x)*(i-x) +(j - y)*(j - y) < rv * rv)){
                SDL_RenderFillRect(renderer,&rect);
        }
    }
}

void combat(enemy *e){
	if(e->hp>0){
        Mix_PlayChannel( -1, battleSound, 0 );
        printf("COMbATEU %d %d\n",hp,e->hp);
        e->hp-= new_max(10,e->def-atk);
        hp-= new_max(10,def-e->atk);
	}
}
