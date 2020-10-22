//
// Created by erthax on 06.06.2020.
//
#include "Structures.h"

PrimGraph::PrimGraph(int n){
    for(int i = 1 ; i<=n; i++){
        V.push_back(new Node(i,std::numeric_limits<double>::infinity(),this->NIL));
    }
    this->Adj = std::vector <std::vector <Edge*> > (n);
}

void PrimGraph::insertEdge(int index1, int index2, double weight){
    Edge* edge1 = new Edge(V[index1-1], V[index2-1], weight);
    Edge* edge2 = new Edge(V[index2-1], V[index1-1], weight);
    Adj[index1-1].push_back(edge1);
    Adj[index2-1].push_back(edge2);
}

std::vector <Edge*> PrimGraph::prim(){
    int i, index = 1;
    Node* u;
    for(i=0; i<this->V.size(); i++){
        V[i]->d = std::numeric_limits<double>::infinity();
        V[i]->pi = this->NIL;
    }
    V[index-1]->d = 0;
    V[index-1]->pi = V[index-1];

    std::vector <Node*> S;
    NodeQueue* q = new NodeQueue();
    for(i=0; i<this->V.size(); i++){
        q->insert(V[i],V[i]->d);
    }
    Node* v;
    while(!q->empty()){
        u = q->pop();
        u->inQueue = false;
        for(i=0; i<this->Adj[u->index-1].size(); i++){
            v = Adj[u->index-1][i]->node2;
            if( v->inQueue && v->d > Adj[u->index-1][i]->weight){
                v->d = Adj[u->index-1][i]->weight;
                q->priority(v,Adj[u->index-1][i]->weight);
                v->pi = u;
            }
        }
    }
    return createMTR();
}

std::vector <Edge*> PrimGraph::createMTR(){
    int i,j;
    Node* pi;
    std::vector <Edge*> result;
    for(i=0; i<this->V.size(); i++){
        pi = V[i]->pi;
        for(j=0; j<this->Adj[i].size(); j++){
            if(Adj[i][j]->node1 == V[i] && Adj[i][j]->node2 == pi){
                result.push_back(Adj[i][j]);
            }
        }
    }
    return result;
}
