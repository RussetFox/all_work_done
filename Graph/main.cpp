#include <iostream>
#include "graph.h"
#include "djikstra.h"
#include <ctime>

int main() {
    matrixgraph g[100];
    for (int i = 0; i < 100; i++) g[i].initialize(10,75);
    std:: cout << "Startuje\n";
    std::clock_t start;
    double duration;
    start = std::clock();
    for (int i = 0; i < 100; i++) dijkstra(g[i], 5);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<< duration <<'\n';
}

