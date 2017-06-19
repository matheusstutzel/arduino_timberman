#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>


SDL_Event e;
SDL_Renderer* renderer;

    SDL_Texture *texture = NULL;

Uint32 now,delay,last;
int **map;
int *text;

	int rows = 640;
	int cols = 480;

void convertTile(int code, SDL_Rect* dest){
	if(code ==0)SDL_RenderCopy(renderer, texture, NULL, dest);
	if(code ==1)SDL_SetRenderDrawColor(renderer,0,0,0,0x00);
	SDL_RenderFillRect(renderer,dest);
	//SDL_RenderDrawPoint(renderer, j*10, i*10);
}
void draw_background(){
	SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0x00);
	SDL_RenderFillRect(renderer, NULL);
	SDL_Rect rect = {0,0,10,10};

	SDL_SetRenderDrawColor(renderer,255,0,0,0x00);
	for(int i = 0; i < rows; i++)for(int j = 0; j < cols; j++){
		rect.x=j*10;
		rect.y=i*10;
		convertTile(text[map[i][j]],&rect);
	}
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
		}
	}
	return 0;
}
int loop(){
	draw_background();
	if(keyEvent())return 0;
	now = SDL_GetTicks();
	if(now > last + delay){
		last = SDL_GetTicks();
	}
	
	SDL_RenderPresent(renderer);
	return 1;
}
void geraMap(){
	FILE* file = fopen ("dust.map", "r");
	int tex;
	fscanf (file, "%d %d\n%d\n", &cols,&rows,&tex);
	map = (int **)malloc(rows * sizeof(int*));
	for(int i = 0; i < rows; i++) map[i] = (int *)malloc(cols * sizeof(int));
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++){
			fscanf (file, "%d ", &map[i][j]);
		}
	text = (int *)malloc(tex * sizeof(int));
	for(int i=0;i<=tex;i++)fscanf (file, "%d", &text[i]);
	fclose (file); 
}
void myFree(){

	for(int i = 0; i < rows; i++) free(map[i]);
	free(map);
	
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
	geraMap();

	/* EXECUTION */

	delay = 16;

	while (loop());

	/* FINALIZATION */
	myFree();
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

