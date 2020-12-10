CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS=-g -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: testxycut

testxycut: ../../Tools/help4display.o ../../Tools/pixel_operations.o testxycut.o ../../Tools/matrix.o ../../Tools/tree.o ../../pré-traitement/binarisation/binarisation.o ../../segmentation/rlsa.o ../../segmentation/segmentationXY.o ../rebuilt.o

testxycut/.o:help4display.h pixel_operations.h textxycut.h matrix.h tree.h binarisation.h rlsa.h segmentationXY.h rebuilt.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} ../*.o
	${RM} ../*.d
	${RM} ../../Tools/*.o
	${RM} ../../Tools/*.d
	${RM} ../../segmentation/*.o
	${RM} ../../segmentation/*.d
	${RM} ../../pré-traitement/binarisation/*.o
	${RM} ../../pré-traitement/binarisation/*.d
	${RM} testxycut
