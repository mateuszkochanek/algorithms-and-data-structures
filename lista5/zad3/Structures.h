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
    Node(int index, double d, Node* node): index(index), d(d), pi(node), rank(0),inQueue(true) {}
    int index;
    bool inQueue;
    double d;
    Node* pi;
    int rank;
};

struct Edge{
    Edge(Node* node1, Node* node2, double weight): node1(node1), node2(node2), weight(weight) {}
    Node* node1;
    Node* node2;
    double weight;

};

struct EdgeElement{
    EdgeElement(Edge* v, double p): v(v), p(p) {}
    Edge* v;
    double p;
};

struct NodeElement{
    NodeElement(Node* v, double p): v(v), p(p) {}
    Node* v;
    double p;
};


class EdgeQueue {
public:
    std::vector <EdgeElement*> heap;
    EdgeQueue();
    int parent(int i);
    int left(int i);
    int right(int i);
    void heapify(int i);
    void insert(Edge* x, double p);
    bool empty();
    Edge* pop();
    void priority(Edge* x, double p);
    void decreaseKey(int i);
};

class KruskalGraph {
public:
    Node* NIL = new Node(-1, std::numeric_limits<double>::infinity(), nullptr);
    std::vector <Node*> V;
    EdgeQueue* E;
    std::vector <std::vector <Edge*> > Adj;
    KruskalGraph(int n);
    void insertEdge(int index1, int index2, double weight);
    std::vector <Edge*> kruskal();
    Node *find(Node *x);
};

class NodeQueue {
public:
    std::vector <NodeElement*> heap;
    NodeQueue();
    int parent(int i);
    int left(int i);
    int right(int i);
    void heapify(int i);
    void insert(Node* x, double p);
    bool empty();
    Node* pop();
    void priority(Node* x, double p);
    void decreaseKey(int i);
};

class PrimGraph {
public:
    Node* NIL = new Node(-1, std::numeric_limits<double>::infinity(), nullptr);
    std::vector <Node*> V;
    std::vector <std::vector <Edge*> > Adj;
    PrimGraph(int n);
    void insertEdge(int index1, int index2, double weight);
    std::vector <Edge*> prim();
    Node *find(Node *x);

    std::vector<Edge *> createMTR();
};




#endif //ZAD1_STRUCTURES_H
