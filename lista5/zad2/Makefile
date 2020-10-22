# Makefile

all: main clean

main: main.o Queue.o Graph.o
	g++ -std=c++17 -o main main.o Queue.o Graph.o

main.o: main.cpp Structures.h
	g++ -c main.cpp  Structures.h

Queue.cpp: Queue.cpp Structures.h
	g++ -c -o Queue.o Queue.cpp Structures.h

Graph.cpp: Graph.cpp Structures.h
	g++ -c -o Graph.o Graph.cpp Structures.h


clean:
	rm -f *.o



