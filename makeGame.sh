gcc main.c maze.c player.c map.c enemy.c -o game  -I . -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -lSDL2 -lSDL2_image -std=c99
./game 
