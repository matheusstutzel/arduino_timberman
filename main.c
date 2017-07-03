#include "global.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "player.h"
#include "map.h"
#include "enemy.h"

#define ENEMYSIZE 5
Uint32 now,delay,last;

SDL_Event e;
SDL_Renderer* renderer;
SDL_Texture *texture = NULL;
SDL_Window* window = NULL;
Mix_Music *gMusic = NULL;

int *text;
int rows = 630;
int cols = 470;

enemy es[ENEMYSIZE];

void draw_background(SDL_Renderer* render ){
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0x00);
    SDL_RenderFillRect(renderer, NULL);
}


void drawEnemies(){
    for(int i=0;i<ENEMYSIZE;i++){
            drawEnemy(es[i],renderer,window,tile);
    }
}
void draw(){
    draw_background(renderer);
    drawMap(window, renderer,tile);
    drawEnemies();
    drawPlayer(renderer, window, tile);
    drawPlayerView(renderer,tile,rows,cols, 10);
}

int testMap(int dx,int dy){
    int x; int y;

    getPosPlayer(&x,&y);

    x+=dx;

    y+=dy;
    //!pode andar retorna
    if(map[y][x])return !map[y][x];
    //pode andar....
    for(int i=0;i<ENEMYSIZE;i++){
        if(es[i].x==x && es[i].y==y){
            //tem monstro ataca
            combat(&es[i]);
            //matou? anda...
            return(es[i].hp<=0);
        }
    }
    //!tem monstro anda...
    return 0<1;//true
}



int keyEvent(){

  if(SDL_PollEvent(&e)!=0){

    switch(e.type){

      case SDL_QUIT: {

        return 1;

      }

      case SDL_MOUSEBUTTONDOWN:{

        SDL_MouseButtonEvent* me = (SDL_MouseButtonEvent*) &e;

      }

      case SDL_MOUSEMOTION:{

        SDL_MouseMotionEvent* me = (SDL_MouseMotionEvent*) &e;

      }

      case SDL_KEYDOWN:

        switch (e.key.keysym.sym)

        {

          case SDLK_LEFT:  if(testMap(-1,0))movePlayer(-1,0); break;

          case SDLK_RIGHT: if(testMap(1,0))movePlayer(1,0); break;

          case SDLK_UP:    if(testMap(0,-1))movePlayer(0,-1); break;

          case SDLK_DOWN:  if(testMap(0,1))movePlayer(0,1); break;

        }

        break;

    }

  }

  return 0;

}
void updateEnemies(){
	for(int i=0;i<ENEMYSIZE;i++)updateEnemy(es[i]);
}
int loop(){
    //If there is no music playing
                            if( Mix_PlayingMusic() == 0 )
                            {
                                //Play the music
                                Mix_PlayMusic( gMusic, -1 );
                            }
  updateEnemies();

  draw();

  if(keyEvent())return 0;

  now = SDL_GetTicks();

  if(now > last + delay){

    last = SDL_GetTicks();

  }



  SDL_RenderPresent(renderer);

  return 1;

}



void myFree(){

  freeMap();

}

void geraEnemy(){
	int x,y,achou,count;
	count =0;
	if(map[2][1])
        spawnEnemy(&es[count++],2,1,10,window);
    else
        spawnEnemy(&es[count++],1,2,10,window);
  while(count < ENEMYSIZE){
	achou = 0!=0;//false
	while(!achou){
		x = rand() %(rows/tile);
		y = rand() %(cols/tile);
		achou = !map[y][x];//retorna se o mapa ta vazio naquela posição
	}
	//verifica se tem outro enemy nessa posição
	for(int i =0;i<count;i++)if(es[i].x==x && es[i].y==y)	achou = 0!=0;//false
	if(achou){
		spawnEnemy(&es[count++],x,y,10,window);
	}
  }
}

int main (int argc, char* args[])

{

  /* INITIALIZATION */



  int err = SDL_Init(SDL_INIT_EVERYTHING);



  window = SDL_CreateWindow("Input",

  SDL_WINDOWPOS_UNDEFINED,

  SDL_WINDOWPOS_UNDEFINED,

  rows, cols, SDL_WINDOW_SHOWN);

  IMG_Init(IMG_INIT_PNG);

      texture = IMG_LoadTexture(renderer, "grass.png");

	srand(time(NULL));
     //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
  renderer = SDL_CreateRenderer(window,-1,0);
  geraMap(window, rows, cols,tile);
  playerInit(window);
  gMusic = Mix_LoadMUS( "C:\\Users\\Rodrigo\\Desktop\\Reativos\\music.wav" );
  geraEnemy();


  /* EXECUTION */



  delay = 16;



  while (loop());



  /* FINALIZATION */

  myFree();

  SDL_DestroyWindow(window);

  SDL_Quit();



  return 0;

}

