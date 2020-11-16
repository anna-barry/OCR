# Simple SDL mini Makefile
IDIR =../../Tools/Matrix.h ../../Tools/pixel_operations.c
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: traitement

traitement= ../../../Tools/Matrix.o ../../../Tools/pixel_operationss.o ../../../Tools/help4display.o  main4trait.o  
traitement.o: ../../../Tools/Matrix.h ../../../Tools/pixel_operations.h ../../../Tools/help4display.h ../traitement.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} traitement


# END
