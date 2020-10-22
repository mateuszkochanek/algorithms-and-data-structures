#include <iostream>
#include "Structures.h"
int main() {
    clock_t start_t, end_t;
    double timeSec;
    int verticesCount, edgeCount, node1, node2, start;
    double weight;
    start_t = clock();
    std::cin>>verticesCount>>edgeCount;
    Graph* graph = new Graph(verticesCount);
    for(int i = 0; i<edgeCount; i++){
        std::cin>>node1>>node2>>weight;
        graph->insertEdge(node1,node2,weight);
    }
    std::cin>>start;
    graph->dijikstra(start);
    end_t = clock();
    timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    graph->printResults();
    std::cerr<<"Czas to:" << timeSec << std::endl;
    return 0;
}
