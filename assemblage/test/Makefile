
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: test

test:  test.o ../assemblage.o 

test/.o: assemblage.h 

clean:
	${RM} *.o
	${RM} *.d
	${RM} ../*.o
	${RM} ../*.d
	${RM} test
	${RM} new
