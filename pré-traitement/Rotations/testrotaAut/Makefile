#Makefile Geoffroy
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

all:
	make testrota

testrota: ../../../Tools/pixel_operations.o testrota.o ../../../Tools/matrix.o ../../binarisation/binarisation.o ../rotationAUTO.o ../../../Tools/image_operations.o 

testrota/.o: pixel_operations.h matrix.h binarisation.h rotationAUTO.h image_operations.h

trash:
	${RM} *.o
	${RM} *.d
	${RM} ../*.o
	${RM} ../*.d
	${RM} ../../../Tools/*.o
	${RM} ../../../Tools/*.d
	${RM} ../../../pré-traitement/binarisation/*.o
	${RM} ../../../pré-traitement/binarisation/*.d
	${RM} testrota

clean:
	make trash
