# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: binarisation

binarisation: pixel_operations.o binarisation.o matrix.o

binarisation/.o: pixel_operations.h matrix.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} binarisation

# END
