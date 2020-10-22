//
// Created by erthax on 06.06.2020.
//
#ifndef ZAD1_STRUCTURES_H
#define ZAD1_STRUCTURES_H
#include <iostream>
#include <vector>
#include <cmath>
struct Node{
    Node(int index, int val): index(index), val(val) {}
    int index;
    int val;
};

struct Element{
    Element(int val, int p): value(val), p(p) {}
    int value;
    int p;
};

class Queue {
public:
    std::vector <Element*> heap;
    Queue();
    int parent(int i);
    int left(int i);
    int right(int i);
    void heapify(int i);
    void insert(int x, int p); // działa na intach, po prostu mam je już w Nodzie żeby było przygotowane do pracy z grafami, nic to nie zmienia w praktyce
    bool empty();
    void top();
    void pop();
    void priority(int x, int p);
    void decreaseKey(int i);
    void print();
};

class Graph {
    //zostanei zalmplementowany w przyszłych zadaniach
};


#endif //ZAD1_STRUCTURES_H
