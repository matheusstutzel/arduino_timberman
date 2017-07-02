#include "enemy.h"

SDL_Surface* enemySurface=NULL;
void updateEnemy(enemy e){

}

void loadEnemySurface(SDL_Window* window){
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load("C:\\Users\\Rodrigo\\Desktop\\Reativos\\enemy.png");
    if( loadedSurface == NULL ){
        printf( "Unable to load image grass! SDL_image Error: %s\n", IMG_GetError() );
    }
    else{
        //Convert surface to screen format
        enemySurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface(window)->format, NULL );
        if( enemySurface == NULL ){
            printf( "Unable to optimize image grass! SDL Error: %s\n", SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
}

void drawEnemy(enemy e, SDL_Renderer* renderer, SDL_Window* window, int tile){
    if(e.hp>0){
        SDL_Rect rect = {0,0,tile,tile- (tile/10)};
        if(e.hp>0){
                SDL_SetRenderDrawColor(renderer,e.r,e.g,e.b,0x00);
        }else{
            SDL_SetRenderDrawColor(renderer,255,0,0,0x00);
        }
        rect.x=e.x*tile;
        rect.y=e.y*tile;
        SDL_BlitSurface(enemySurface, NULL, SDL_GetWindowSurface(window), &rect);
        SDL_SetRenderDrawColor(renderer,255,0,0,0x00);
        rect.h=(tile/10);
        rect.w=(int)((e.hp/e.HPMAX)*(tile));
        rect.x=e.x*tile;
        rect.y=e.y*tile+(tile-(tile/10));

        SDL_RenderFillRect(renderer,&rect);
    }
}

void spawnEnemy(enemy * e ,int x, int y,int level, SDL_Window* window){
    e->x=x;
	e->y=y;
	e->r=50;
	e->g=255;
	e->b=150;
	e->hp=100;
	e->atk=level;
	e->def=level/2;
	e->speed=1;
	e->state=0;
	e->HPMAX= 100.0;
	loadEnemySurface(window);
}

void freeEnemy(enemy *e){
	free(e);
}
