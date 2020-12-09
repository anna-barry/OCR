# Makefile

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3
LDLIBS = `pkg-config --libs gtk+-3.0`

all: editeurdetexte


editeurdetexte: callback.o error.o premierepage.o

editeurdetexte/.o: callback.h error.h premierepage.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} editeurdetexte


# END
