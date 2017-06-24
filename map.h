#include <maze.h>
#include <SDL2/SDL.h>
int **map;
void geraMap(int cols, int rows, int tile);
void freeMap();
void drawMap(SDL_Renderer*,int); 
