#include "assets.h"

SDL_Surface* loadEnemySurface(SDL_Window* window){
	SDL_Surface* enemySurface=NULL;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(getFile("enemy.png"));
    if( loadedSurface == NULL ){
        printf( "Unable to load image grass! SDL_image Error: %s\n", IMG_GetError() );
    }
    else{
        //Convert surface to screen format
        enemySurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface(window)->format, 0 );
        if( enemySurface == NULL ){
            printf( "Unable to optimize image grass! SDL Error: %s\n", SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
	return enemySurface;
}

SDL_Surface* loadGrass(SDL_Window* window){
	SDL_Surface* grassSurface = NULL;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(getFile("grass.png"));
    if( loadedSurface == NULL ){
        printf( "Unable to load image grass! SDL_image Error: %s\n", IMG_GetError() );
    }else{
        //Convert surface to screen format
        grassSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface(window)->format, 0 );
        if( grassSurface == NULL ){
            printf( "Unable to optimize image grass! SDL Error: %s\n", SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
	return grassSurface;
}

SDL_Surface* loadObstacle(SDL_Window* window){
	SDL_Surface* obstacleSurface = NULL;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(getFile("obstacle.png"));
    if( loadedSurface == NULL ){
        printf( "Unable to load image grass! SDL_image Error: %s\n", IMG_GetError() );
    }else{
        //Convert surface to screen format
        obstacleSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface(window)->format, 0 );
        if( obstacleSurface == NULL ){
            printf( "Unable to optimize image grass! SDL Error: %s\n", SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
	return obstacleSurface;
}

SDL_Surface* loadPlayerSurface(SDL_Window* window){
	SDL_Surface* playerSurface = NULL;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(getFile("hero.png"));
    if( loadedSurface == NULL ){
        printf( "Unable to load image grass! SDL_image Error: %s\n", IMG_GetError() );
    }
    else{
        //Convert surface to screen format
        playerSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface(window)->format, 0 );
        if( playerSurface == NULL ){
            printf( "Unable to optimize image grass! SDL Error: %s\n", SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
	return playerSurface;
}
Mix_Chunk * loadBattleSound(){
	Mix_Chunk *battleSound = NULL;
    //Load sound effects
    battleSound = Mix_LoadWAV(getFile("battleSound.wav"));
    if( battleSound == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	return battleSound;
}
	char dest[500];
char* getFile(char* filename){

   	strcpy(dest, "/home/matheus/Projetos/UERJ/Reativos/projeto-reativos/");
	strcat(dest, filename);
	return dest;
}
