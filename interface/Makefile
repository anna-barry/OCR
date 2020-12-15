# Makefile


CC = gcc
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl` -Wall -O3
LDLIBS = `pkg-config --libs gtk+-3.0`  `pkg-config --libs sdl` -lSDL_image -lm


all: main

main: ../pré-traitement/Rotations/rotationMAN.o ../pré-traitement/Rotations/rotationAUTO.o callback.o error.o  ../assemblage/assemblage.o ../Tools/help4display.o ../Tools/pixel_operations.o  ../Tools/matrix.o  ../Tools/tree.o ../pré-traitement/binarisation/binarisation.o ../segmentation/rlsa.o  ../segmentation/segmentationXY.o ../Tools/minifunc.o ../segmentation/resizeMatrix.o  ../pré-traitement/traitement/testtraitement.o ../pré-traitement/traitement/traitement.o ../réseau_de_neurones/CNN/LeNet.o ../réseau_de_neurones/CNN/RecogniseASCII.o

Main/.o: rotationMAN.h rotationAUTO.h callback.h error.h assemblage.h help4display.h pixel_operations.h image_operation.o matrix.h tree.h binarisation.h rlsa.h segmentationXY.h minifunc.h resizeMatrix.h testtraitement.h traitement.h LeNet.h RecogniseASCII.h
clean:
	${RM} *.o
	${RM} *.d
	${RM} ../Tools/*.o
	${RM} ../Tools/*.d
	${RM} ../réseau_de_neurones/CNN/*.o
	${RM} ../réseau_de_neurones/CNN/*.d
	${RM} ../pré-traitement/binarisation/*.o
	${RM} ../pré-traitement/binarisation/*.d
	${RM} ../pré-traitement/Rotations/*.o
	${RM} ../pré-traitement/Rotations/*.d
	${RM} ../pré-traitement/traitement/*.o
	${RM} ../pré-traitement/traitement/*.d
	${RM} ../segmentation/*.o
	${RM} ../segmentation/*.d
	${RM} ../segmentation/testxycut/*.o
	${RM} ../segmentation/testxycut/*.d
	${RM} traitement_image.bmp
	${RM} smooth.bmp
	${RM} contrast.bmp
	${RM} last*
	${RM} main
	${RM} textOCR


# END
