all: maze

clean:
	rm main.o
	rm quaternion.o
	rm maze.o
	rm maze

maze: main.o quaternion.o maze.o
	gcc -o maze `sdl-config --libs` `pkg-config --libs gl glu` main.o quaternion.o maze.o

main.o: main.c
	gcc `sdl-config --cflags` `pkg-config --cflags gl glu` -c main.c

quaternion.o: quaternion.h quaternion.c
	gcc -c quaternion.c

maze.o: maze.h maze.c
	gcc -c maze.c

