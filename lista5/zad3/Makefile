# Makefile

all: main clean

main: main.o NodeQueue.o EdgeQueue.o PrimGraph.o KruskalGraph.o
	g++ -std=c++17 -o main main.o NodeQueue.o EdgeQueue.o PrimGraph.o KruskalGraph.o

main.o: main.cpp Structures.h
	g++ -c main.cpp  Structures.h

NodeQueue.cpp: NodeQueue.cpp Structures.h
	g++ -c -o NodeQueue.o NodeQueue.cpp Structures.h

PrimGraph.cpp: PrimGraph.cpp Structures.h
	g++ -c -o PrimGraph.o PrimGraph.cpp Structures.h

EdgeQueue.cpp: EdgeQueue.cpp Structures.h
	g++ -c -o EdgeQueue.o EdgeQueue.cpp Structures.h

KruskalGraph.cpp: KruskalGraph.cpp Structures.h
	g++ -c -o KruskalGraph.o KruskalGraph.cpp Structures.h


clean:
	rm -f *.o



