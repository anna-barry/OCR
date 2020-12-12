#Makefile Geoffroy
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all:
	make testresize
	mkdir rsltTst

save:
	cp *.bmp ../testresize/rsltTst

testresize: ../../Tools/pixel_operations.o testresize.o ../../Tools/matrix.o ../../pré-traitement/binarisation/binarisation.o ../../Tools/minifunc.o ../resizeMatrix.o ../../Tools/image_operations.o

testresize/.o: pixel_operations.h matrix.h binarisation.h resizeMatrix.h image_operations.h minifunc.h

trash:
	${RM} *.o
	${RM} *.d
	${RM} *.bmp
	${RM} ../*.o
	${RM} ../*.d
	${RM} ../../Tools/*.o
	${RM} ../../Tools/*.d
	${RM} ../../pré-traitement/binarisation/*.o
	${RM} ../../pré-traitement/binarisation/*.d
	${RM} testresize

clean:
	make save
	make trash

clean_all:
	make trash
	${RM} ../testresize/rsltTst/*.bmp
	rmdir rsltTst
