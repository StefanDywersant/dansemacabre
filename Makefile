
# Linux (default)
CC=gcc
CCFLAGS=-I/usr/X11R6/include/
LDFLAGS=-L/usr/X11R6/lib -lX11 -lXi -lXmu -lglut -lGL -lGLU
EXE=DanseMacabre

ifeq ($(OS),Windows_NT)
	EXE = DanseMacabre.exe
	LDFLAGS = -lopengl32 -lglu32 -lglut32
	CCFLAGS =
	
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LDFLAGS = -framework OpenGL -framework GLUT
		CCFLAGS = -Wno-deprecated-declarations
	endif
endif

all:  $(EXE)

$(EXE): main.c load.c maths.c
	${CC} ${CCFLAGS} ${LDFLAGS} main.c load.c maths.c -o DanseMacabre

clean:
	rm ${EXE}
