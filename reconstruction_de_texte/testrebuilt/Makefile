CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS=-g -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: testrebuilt

testrebuilt: ../../Tools/help4display.o ../../Tools/pixel_operations.o testrebuilt.o ../../Tools/matrix.o ../../Tools/tree.o ../../pré-traitement/binarisation/binarisation.o ../../segmentation/rlsa.o ../rebuilt.o #../../segmentation/segmentationXY.o

testrebuilt/.o:help4display.h pixel_operations.h matrix.h binarisation.h rlsa.h rebuilt.h #segmentationXY.h

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
	${RM} testrebuilt
