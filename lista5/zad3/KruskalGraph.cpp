//
// Created by erthax on 06.06.2020.
//
#include "Structures.h"

KruskalGraph::KruskalGraph(int n){
    for(int i = 1 ; i<=n; i++){
        V.push_back(new Node(i,std::numeric_limits<double>::infinity(),this->NIL));
    }
    this->Adj = std::vector <std::vector <Edge*> > (n);
    E = new EdgeQueue();
}

void KruskalGraph::insertEdge(int index1, int index2, double weight){
    Edge* edge1 = new Edge(V[index1-1], V[index2-1], weight);
    Edge* edge2 = new Edge(V[index2-1], V[index1-1], weight);
    Adj[index1-1].push_back(edge1);
    Adj[index2-1].push_back(edge2);
    E->insert(edge1,weight);
}

std::vector <Edge*> KruskalGraph::kruskal(){
    std::vector <Edge*> result;
    Edge* e;
    Node* x, *y;
    for(int i = 0 ; i<V.size(); i++){
        V[i]->pi = V[i];
    }
    while(!E->empty()){
        e = E->pop();
        if(find(e->node1) != find(e->node2)){
            result.push_back(e);
            x=find(e->node1);
            y=find(e->node2);
            if(x->rank > y->rank)
                y->pi = x->pi;
            else{
                x->pi = y;
                if(x->rank == y->rank){
                    y->rank = y->rank+1;
                }
            }

        }
    }
    return result;
}

Node* KruskalGraph::find(Node* x){
    Node* y = x;
    while(y != y->pi){
        y = y->pi;
    }
}

