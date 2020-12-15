# Simple SDL mini Makefile
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

all: main

main= main.o 

clean:
	${RM} *.o
	${RM} *.d
	${RM} ../rotationMAN
	${RM} ../*.o
	${RM} ../*.d
	${RM} main

# END
