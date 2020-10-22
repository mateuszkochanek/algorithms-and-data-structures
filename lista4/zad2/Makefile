# Makefile

all: main clean

main: main.o RedBlackTree.o LinkedList.o BinarySearchTree.o HashMap.o
	g++ -o main main.o RedBlackTree.o LinkedList.o BinarySearchTree.o HashMap.o

main.o: main.cpp
	g++ -c main.cpp 

decode.o: decode.cpp
	g++ -c decode.cpp

RedBlackTree.cpp: RedBlackTree.cpp DataStructure.h
	g++ -c -o RedBlackTree.o RedBlackTree.cpp DataStructure.h

LinkedList.cpp: LinkedList.cpp DataStructure.h
	g++ -c -o LinkedList.o LinkedList.cpp DataStructure.h

BinarySearchTree.cpp: BinarySearchTree.cpp DataStructure.h
	g++ -c -o BinarySearchTree.o BinarySearchTree.cpp DataStructure.h

HashMap.cpp: HashMap.cpp DataStructure.h
	g++ -c -o HashMap.o HashMap.cpp DataStructure.h


clean:
	rm -f *.o
	rm -f UniversalCoder/*.o



