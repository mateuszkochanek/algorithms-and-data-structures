//
// Created by erthax on 06.06.2020.
//
#ifndef ZAD1_STRUCTURES_H
#define ZAD1_STRUCTURES_H
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

struct Node{
    Node(int index, double d, Node* node): index(index), d(d), pi(node) {}
    int index;
    double d;
    Node* pi;
};

struct Edge{
    Edge(Node* node1, Node* node2, double weight): node1(node1), node2(node2), weight(weight) {}
    Node* node1;
    Node* node2;
    double weight;

};

struct Element{
    Element(Node* v, double p): v(v), p(p) {}
    Node* v;
    double p;
};

class Queue {
public:
    std::vector <Element*> heap;
    Queue();
    int parent(int i);
    int left(int i);
    int right(int i);
    void heapify(int i);
    void insert(Node* x, double p); // działa na intach, po prostu mam je już w Nodzie żeby było przygotowane do pracy z grafami, nic to nie zmienia w praktyce
    bool empty();
    Node* pop();
    void priority(Node* x, double p);
    void decreaseKey(int i);
    void print();
};

class Graph {
public:
    Node* NIL = new Node(-1, std::numeric_limits<double>::infinity(), nullptr);
    std::vector <Node*> V;
    std::vector <std::vector <Edge*> > Adj;
    Graph(int n);
    void insertEdge(int index1, int index2, double weight);
    void dijikstra(int index);
    void printResults();
    void printNodePath(int i);
};


#endif //ZAD1_STRUCTURES_H
