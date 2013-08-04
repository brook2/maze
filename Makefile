all: maze

maze: main.o quaternion.o
	gcc -o maze `sdl-config --libs` `pkg-config --libs gl glu` main.o quaternion.o

main.o: main.c
	gcc `sdl-config --cflags` `pkg-config --cflags gl glu` -c main.c

quaternion.o: quaternion.h quaternion.c
	gcc -c quaternion.c
