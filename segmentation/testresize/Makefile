
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: testresize

testresize: ../../Tools/pixel_operations.o testresize.o ../../Tools/matrix.o ../../pré-traitement/binarisation/binarisation.o ../resizeMatrix.o ../../Tools/image_operations.o

testrlsa/.o: pixel_operations.h matrix.h binarisation.h resizeMatrix.h image_operations.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} ../*.o
	${RM} ../*.d
	${RM} ../../Tools/*.o
	${RM} ../../Tools/*.d
	${RM} ../../pré-traitement/binarisation/*.o
	${RM} ../../pré-traitement/binarisation/*.d
	${RM} testresize
	${RM} line
	${RM} para
