//
// Created by erthax on 06.06.2020.
//
#include "Structures.h"

Graph::Graph(int n){
    for(int i = 1 ; i<=n; i++){
        V.push_back(new Node(i,std::numeric_limits<double>::infinity(),this->NIL));
    }
    this->Adj = std::vector <std::vector <Edge*> > (n);
    for(int i = 0 ; i<n; i++){
        Adj[i].push_back(new Edge(V[i],V[i],0));
    }
}
void Graph::printResults(){
    for(int i = 0; i<V.size(); i++)
        std::cout<<"("<<V[i]->index<<", "<<V[i]->d<<")"<<" | ";
    std::cout<<std::endl;
    for(int i = 0; i<V.size(); i++){
        std::cerr<<i+1<<" ---> Path: "<<std::endl;
        printNodePath(i);
        std::cerr<<std::endl;
    }

}

void Graph::printNodePath(int i){
    if(this->V[i]->pi == this->NIL){
        std::cerr<<i+1<<" has no path";
        return;
    }
    if(this->V[i]->pi == this->V[i]){
        std::cerr<<"("<<i+1<<", "<<this->V[i]->d<<")";
        return;
    }
    std::cerr<<"("<<i+1<<", "<<this->V[i]->d<<")"<<" | ";
    printNodePath((this->V[i]->pi->index)-1);
}

void Graph::insertEdge(int index1, int index2, double weight){
    Edge* edge = new Edge(V[index1-1], V[index2-1], weight);
    Adj[index1-1].push_back(edge);
}

void Graph::dijikstra(int index){
    int i;
    Node* u;
    for(i=0; i<this->V.size(); i++){
        V[i]->d = std::numeric_limits<double>::infinity();
        V[i]->pi = this->NIL;
    }
    V[index-1]->d = 0;
    V[index-1]->pi = V[index-1];

    std::vector <Node*> S;
    Queue* q = new Queue();
    for(i=0; i<this->V.size(); i++){
        q->insert(V[i],V[i]->d);
    }
    Node* v;
    while(!q->empty()){
        u = q->pop();
        S.push_back(u);
        for(i=0; i<this->Adj[u->index-1].size(); i++){
            v = Adj[u->index-1][i]->node2;
            if(v->d > u->d + Adj[u->index-1][i]->weight){
                v->d = u->d + Adj[u->index-1][i]->weight;
                q->priority(v,u->d + Adj[u->index-1][i]->weight);
                v->pi = u;
            }
        }
    }

}