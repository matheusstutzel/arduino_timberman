gcc *.c -o game  -I . -I/usr/include/SDL/  -D_GNU_SOURCE=1 -D_REENTRANT -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL  -std=c99
./game 
