all: main

main: segmentationXY.o main.o
	gcc -o main segmentationXY.o main.o

segmentationXY.o: segmentationXY.c
	gcc -c segmentationXY.c

main.o: main.c segmentationXY.h
	gcc -c main.c