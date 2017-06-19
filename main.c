#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>


SDL_Event e;
SDL_Renderer* renderer;

Uint32 now,delay,last;

struct sQuadrado {
	SDL_Rect r;
	int state,prevState;
	int xstart,ystart;
	int xmax,ymax;
	int velo;
	int R,G,B,A;

};
typedef struct sQuadrado* Quadrado;
Quadrado a,b;

void criaQuadrado(Quadrado q,int x, int y, int size,int maxDesloc, int inc , int R , int G , int B , int A ){
	q->r.x=x;
	q->xstart=x;
	q->r.y=y;
	q->ystart=y;
	q->r.w=size;
	q->r.h=size;
	q->state=0;
	q->prevState=0;
	q->xmax=x+maxDesloc;
	q->ymax=y+maxDesloc;
	q->velo = inc;
	q->R=R;
	q->G=G;
	q->B=B;
	q->A=A;
}

void move(Quadrado q){
	int inc = q->velo;
	if(!(q->state==0 || q->state==1))inc *= -1;

	if(q->state==0){
		if(q->r.x+inc>q->xmax)q->state=1;
		else q->r.x+=inc;
	}else if(q->state==1){
		if(q->r.y+inc>q->ymax)q->state=2;
		else q->r.y+=inc;
	}else if(q->state==2){
		if(q->r.x+inc<q->xstart){ q->state=3; q->r.x=q->xstart;}
		else q->r.x+=inc;
	}else if(q->state==3){
		if(q->r.y+inc<q->ystart){ q->state=0; q->r.y=q->ystart;}
		else q->r.y+=inc;
	}
}
void desenhaLinha(int x,int y,int x1,int y1){
	printf("Desenho %d %d %d %d \n", x, y, x1, y1);
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0x00);
	SDL_RenderDrawLine(renderer, x, y, x1, y1);
}

void testClick(SDL_MouseButtonEvent* me,Quadrado q){
	if(
		(me->x>=q->r.x && me->x<=q->r.x+q->r.w)
		&&
		(me->y>=q->r.y && me->y<=q->r.y+q->r.h)
	){
		if(q->state>=0){
			q->prevState=q->state; q->state=-1;
		}
		else q->state=q->prevState;
	}
}

void draw_background(){
	SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0x00);
	SDL_RenderFillRect(renderer, NULL);
}
void draw_square(Quadrado a){
		SDL_SetRenderDrawColor(renderer,a->R,a->G,a->B,a->A);
		SDL_RenderFillRect(renderer, &(a->r));
}
int keyEvent(){
	if(SDL_PollEvent(&e)!=0){
		switch(e.type){
			case SDL_QUIT: {
				return 1;
			}
			case SDL_MOUSEBUTTONDOWN:{
				SDL_MouseButtonEvent* me = (SDL_MouseButtonEvent*) &e;
					desenhaLinha(0,0,me->x, me->y);
			}
			case SDL_MOUSEMOTION:{
				SDL_MouseMotionEvent* me = (SDL_MouseMotionEvent*) &e;
				desenhaLinha(0,0,me->x, me->y);
			}
		}
	}
	return 0;
}
void draw_circle(SDL_Point center, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
            }
        }
    }
}
int loop(){
	draw_background();
	if(keyEvent())return 0;
	now = SDL_GetTicks();
	if(now > last + delay){
		last = SDL_GetTicks();
		move(a);
		move(b);
	}
	draw_square(a);
	draw_square(b);
	SDL_Point center = {playerX,playerY};
	SDL_Color w = {255,255,0,255};
	draw_circle(center,50,w);

	SDL_RenderPresent(renderer);
	return 1;
}
int main (int argc, char* args[])
{
	/* INITIALIZATION */

	int err = SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("Input",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	640, 480, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window,-1,0);

	a = (Quadrado) malloc (sizeof (struct sQuadrado));
	b = (Quadrado) malloc (sizeof (struct sQuadrado));
	//quadrado,x,y,size,maxDesloc,inc, R,G,B,A
	criaQuadrado(a,200,200,50,50,1,0x02,0xA4,0xF0,0x00);
	criaQuadrado(b,100,100,35,75,5,0x34,0x9c,0x33,0x00);

	/* EXECUTION */

	delay = 16;

	while (loop());

	/* FINALIZATION */

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
