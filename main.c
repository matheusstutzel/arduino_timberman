#include <global.h>

#include <stdio.h>

#include <stdlib.h>

#include <SDL2/SDL_image.h>

#include <player.h>

#include <map.h>



SDL_Event e;

SDL_Renderer* renderer;



    SDL_Texture *texture = NULL;



Uint32 now,delay,last;

int *text;

int rows = 630;

int cols = 470;



void draw_background(SDL_Renderer* render ){

  SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0x00);

  SDL_RenderFillRect(renderer, NULL);

}



void draw(){

  draw_background(renderer);

  drawMap(renderer,tile);

  drawPlayer(renderer,tile);

  drawPlayerView(renderer,tile,rows,cols);

}

int testMap(int dx,int dy){

  int x; int y;

  getPosPlayer(&x,&y);

  x+=dx;

  y+=dy;



  return !map[y][x];

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

int loop(){

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

int main (int argc, char* args[])

{

  /* INITIALIZATION */



  int err = SDL_Init(SDL_INIT_EVERYTHING);



  SDL_Window* window = SDL_CreateWindow("Input",

  SDL_WINDOWPOS_UNDEFINED,

  SDL_WINDOWPOS_UNDEFINED,

  rows, cols, SDL_WINDOW_SHOWN);

  IMG_Init(IMG_INIT_PNG);

      texture = IMG_LoadTexture(renderer, "grass.png");



  renderer = SDL_CreateRenderer(window,-1,0);

  geraMap(rows, cols,tile);



  /* EXECUTION */



  delay = 16;



  while (loop());



  /* FINALIZATION */

  myFree();

  SDL_DestroyWindow(window);

  SDL_Quit();



  return 0;

}
 
