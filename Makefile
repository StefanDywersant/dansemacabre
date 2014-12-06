CC=gcc
CCFLAGS=-I/usr/X11R6/include/ -L/usr/X11R6/lib -lX11 -lXi -lXmu -lglut -lGL -lGLU

all:  DanseMacabre

DanseMacabre: main.c load.c maths.c
	${CC} ${CCFLAGS} main.c load.c maths.c -o DanseMacabre

clean:
	rm DanseMacabre
