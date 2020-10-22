#include <iostream>
#include "Structures.h"
int main(int argc, char *argv[]) {
    std::string sett[argc-1];
    for(int i = 1, j=0; i<argc; i++, j++){
        sett[j] = argv[i];
    }

    double weightSum = 0;
    std::vector <Edge*> E;
    int verticesCount, edgeCount, node1, node2, start,i;
    double weight;
    std::cin>>verticesCount>>edgeCount;

    if(sett[0] == "-k"){
        KruskalGraph* graph = new KruskalGraph(verticesCount);
        for(i = 0; i<edgeCount; i++){
            std::cin>>node1>>node2>>weight;
            graph->insertEdge(node1,node2,weight);
        }
        E = graph->kruskal();
        for(i = 0; i<E.size(); i++){
            std::cout<<"("<<E[i]->node1->index<<", "<<E[i]->node2->index<<", "<<E[i]->weight<<")"<<" | ";
            weightSum+=E[i]->weight;
        }
        std::cout<<std::endl;
        std::cout<<"Suma wag: "<<weightSum<<std::endl;
    } else if(sett[0] == "-p"){
        PrimGraph* graph = new PrimGraph(verticesCount);
        for(i = 0; i<edgeCount; i++){
            std::cin>>node1>>node2>>weight;
            graph->insertEdge(node1,node2,weight);
        }
        E = graph->prim();
        for(i = 0; i<E.size(); i++){
            std::cout<<"("<<E[i]->node1->index<<", "<<E[i]->node2->index<<", "<<E[i]->weight<<")"<<" | ";
            weightSum+=E[i]->weight;
        }
        std::cout<<std::endl;
        std::cout<<"Suma wag: "<<weightSum<<std::endl;
    } else{
        std::cout<<"złe parametry"<<std::endl;
    }
    return 0;
}
