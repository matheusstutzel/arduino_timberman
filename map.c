#include <map.h>
int __mapc,__mapr;
void geraMap(int cols, int rows, int tile){
  cols = cols/tile;
  rows = rows/tile;
  __mapc=cols;
  __mapr=rows;
  Node *n = createMaze(cols,rows);
  //drawMaze(n,cols,rows);
  map = (int **)malloc(rows * sizeof(int*));
  for(int i = 0; i < rows; i++) map[i] = (int *)malloc(cols * sizeof(int));
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++){
      //printf("%d %d \n",i,j);
      map[i][j]= (n[j + i * cols].c ==' ')?0:1;
    }
  free(n);
}

void freeMap(){
  for(int i = 0; i < __mapr; i++) free(map[i]);
  free(map);
}
void convertTile(SDL_Renderer* renderer,int code, SDL_Rect* dest){
  if(code ==0)SDL_SetRenderDrawColor(renderer,255,0,0,0x00);//SDL_RenderCopy(renderer, texture, NULL, dest);
  if(code ==1)SDL_SetRenderDrawColor(renderer,0,0,0,0x00);
  SDL_RenderFillRect(renderer,dest);
  //SDL_RenderDrawPoint(renderer, j*10, i*10);
}
void drawMap(SDL_Renderer* renderer, int tile){
  SDL_Rect rect = {0,0,tile,tile};

  SDL_SetRenderDrawColor(renderer,255,0,0,0x00);
  for(int i = 0; i < __mapr; i++)for(int j = 0; j < __mapc; j++){
    rect.x=j*tile;
    rect.y=i*tile;
    convertTile(renderer,map[i][j],&rect);
  }
} 
