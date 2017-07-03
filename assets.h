#ifndef TESTE 
#define TESTE 10 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

SDL_Surface* loadEnemySurface(SDL_Window* window);
SDL_Surface* loadGrass(SDL_Window* window);
SDL_Surface* loadObstacle(SDL_Window* window);
SDL_Surface* loadPlayerSurface(SDL_Window* window);
Mix_Chunk * loadBattleSound();
char* getFile(char* filename);

char dest[500];
SDL_Surface* eSurface=NULL;
SDL_Surface* gSurface = NULL;
SDL_Surface* oSurface = NULL;
SDL_Surface* pSurface = NULL;
Mix_Chunk *bSound = NULL;
#endif 
