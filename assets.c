#include "assets.h"

SDL_Surface* grassSurface = NULL;
void loadGrass(SDL_Window* window){
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load("C:\\Users\\Rodrigo\\Desktop\\Reativos\\grass.png");
    if( loadedSurface == NULL ){
        printf( "Unable to load image grass! SDL_image Error: %s\n", IMG_GetError() );
    }
    else{
        //Convert surface to screen format
        grassSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface(window)->format, NULL );
        if( grassSurface == NULL ){
            printf( "Unable to optimize image grass! SDL Error: %s\n", SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
}
