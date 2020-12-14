CC=gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: traitement

traitement: testtraitement.o ../../Tools/matrix.o ../../Tools/pixel_operations.o ../../Tools/help4display.o traitement.o ../binarisation/binarisation.o

traitement/.o: testtreaitement.h matrix.h pixel_operations.h help4display.h traitement.h binarisation.h testtreaitement.h 
clean:
	${RM} *.o
	${RM} *.d
	${RM} traitement
	${RM} ../../Tools/*.o
	${RM} ../../Tools/*.d
	${RM} ../binarisation/*.o

# END
