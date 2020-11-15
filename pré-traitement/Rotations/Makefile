# Simple SDL mini Makefile
IDIR =../../Tools/pixel_operations.h
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: rotationMAN

rotationMAN= ../../Tools/pixel_operations.o rotationMAN.o
rotationMAN.o: ../../Tools/pixel_operations.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} rotationMAN


# END
