# Makefile

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3
LDLIBS = `pkg-config --libs gtk+-3.0`

all: main

main: callback.o error.o 

main/.o: callback.h error.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} main


# END
