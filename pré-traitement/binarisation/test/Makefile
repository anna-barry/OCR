
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: test

test: ../../../Tools/pixel_operations.o ../../../Tools/image_operations.o test.o ../../../Tools/matrix.o ../binarisation.o 

test/.o: pixel_operations.h matrix.h image_operations.h binarisation.h 

clean:
	${RM} *.o
	${RM} *.d
	${RM} ../*.o
	${RM} ../*.d
	${RM} ../../../Tools/*.o
	${RM} ../../../Tools/*.d
	${RM} test
	${RM} new
