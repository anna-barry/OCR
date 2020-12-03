# Simple SDL mini Makefile
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: main4man

main4man=  ../../../Tools/pixel_operations.o  ../rotationMAN.o  main4man.o -lm 
main4man/.o: pixel_operations.h rotationMAN.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} ../rotationMAN
	${RM} ../*.o
	${RM} ../*.d
	${RM} ../../../Tools/*.o
	${RM} ../../../Tools/*.d
	${RM} ../../pré-traitement/binarisation/*.o
	${RM} ../../pré-traitement/binarisation/*.d
	${RM} main4man

# END
