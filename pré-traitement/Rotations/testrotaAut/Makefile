#Makefile Geoffroy
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

all:
	make testrota
	mkdir rsltTst

save:
	cp *.bmp ../testr/rsltTst

testrota: ../../../Tools/pixel_operations.o testrota.o ../../../Tools/matrix.o ../../binarisation/binarisation.o ../rotationMAN.o ../../../Tools/image_operations.o #../rotationAUTO.o

testrota/.o: pixel_operations.h matrix.h binarisation.h rotationMAN.h image_operations.h #rotationAUTO.h

trash:
	${RM} *.o
	${RM} *.d
	#${RM} *.bmp
	${RM} ../*.o
	${RM} ../*.d
	${RM} ../../../Tools/*.o
	${RM} ../../../Tools/*.d
	${RM} ../../../pré-traitement/binarisation/*.o
	${RM} ../../../pré-traitement/binarisation/*.d
	${RM} testrota

clean:
	#make save
	make trash

clean_all:
	make trash
	${RM} ../testresize/rsltTst/*.bmp
	rmdir rsltTst
