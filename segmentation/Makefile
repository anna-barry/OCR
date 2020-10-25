all: main

main: segmentationXY.o main.o
	gcc -o main segmentationXY.o main.o

segmentationXY.o: segmentationXY.c
	gcc -c segmentationXY.c
	gcc -IC segmentation.c

main.o: main.c segmentationXY.h
	gcc -c main.c
	gcc -IC main.c

clean:
	rm -f *.o
	rm -f ${DEP}
	rm -f ${PRG}
