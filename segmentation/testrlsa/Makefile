# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: testrlsa

testrlsa: pixel_operations.o testrlsa.o matrix.o

testrlsa/.o: pixel_operations.h matrix.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} testrlsa

# END
