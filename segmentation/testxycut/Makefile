CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS=-g -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: testxycut

testxycut:../../réseau_de_neurones/CNN/LeNet.o ../../réseau_de_neurones/CNN/RecogniseASCII.o ../../Tools/minifunc.o ../resizeMatrix.o ../../Tools/help4display.o ../../Tools/pixel_operations.o testxycut.o ../../Tools/matrix.o ../../Tools/tree.o ../../pré-traitement/binarisation/binarisation.o ../rlsa.o ../segmentationXY.o

testxycut/.o: LeNet.h RecogniseASCII.h minifunc.h resizeMatrix.h help4display.h pixel_operations.h textxycut.h matrix.h tree.h binarisation.h rlsa.h segmentationXY.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} *.o
	${RM} *.d
	${RM} ../../Tools/*.o
	${RM} ../../Tools/*.d
	${RM} ../../pré-traitement/binarisation/*.o
	${RM} ../../pré-traitement/binarisation/*.d
	${RM} testxycut
	${RM} last*
	${RM} textOCR
	${RM} ../*.o
	${RM} ../*.d
	${RM} ../../réseau_de_neurones/CNN/*.o
	${RM} ../../réseau_de_neurones/CNN/*.d
