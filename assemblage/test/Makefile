CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

all: test

test:../../réseau_de_neurones/CNN/LeNet.o ../../réseau_de_neurones/CNN/RecogniseASCII.o ../../pré-traitement/Rotations/rotationAUTO.o ../../pré-traitement/Rotations/rotationMAN.o test.o ../assemblage.o  ../../Tools/help4display.o ../../Tools/pixel_operations.o  ../../Tools/matrix.o  ../../Tools/tree.o ../../pré-traitement/binarisation/binarisation.o ../../segmentation/rlsa.o  ../../segmentation/segmentationXY.o ../../Tools/minifunc.o ../../segmentation/resizeMatrix.o

test/.o: RecogniseASCII.h rotationAUTO.h LeNet.h rotationMAN.h assemblage.h help4display.h pixel_operations.h image_operations.h matrix.h tree.h binarisation.h rlsa.h segmentationXY.h minifunc.h resizeMatrix.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} ../*.o
	${RM} ../*.d
	${RM} ../../Tools/*.o
	${RM} ../../Tools/*.d
	${RM} ../../réseau_de_neurones/CNN/*.o
	${RM} ../../réseau_de_neurones/CNN/*.o
	${RM} ../../pré-traitement/binarisation/*.o
	${RM} ../../pré-traitement/binarisation/*.d
	${RM} ../../segmentation/*.o
	${RM} ../../segmentation/*.d
	${RM} ../../segmentation/testxycut/*.o
	${RM} ../../segmentation/testxycut/*.d
	${RM} ../pré-traitement/Rotations/*.o
	${RM} ../pré-traitement/Rotations/*.d
	${RM} test
	${RM} new
	${RM} testOCR
