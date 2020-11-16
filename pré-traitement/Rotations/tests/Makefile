# Simple SDL mini Makefile
IDIR =../../Tools/pixel_operations.h
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: rotationMAN

rotationMAN= ../../../Tools/pixel_operations.o ../../../Tools/help4display.o  main4man.o  
rotationMAN.o: ../../../Tools/pixel_operations.h ../../../Tools/help4display.h ../rotationMAN.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} rotationMAN


# END
