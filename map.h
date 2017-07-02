#include "maze.h"
#include <SDL.h>
#include <SDL_image.h>
int **map;
void geraMap(SDL_Window* window, int cols, int rows, int tile);
void freeMap();
void drawMap(SDL_Window* window, SDL_Renderer*,int);
