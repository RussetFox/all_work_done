#include "djikstra.h"
#include "graph.h"
#include <iostream>

int minDistance(int dist[], bool sptSet[], int vertnum)
{

    // Inicjalizacja wartości minimalnej
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertnum; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(matrixgraph &gr, int src)//Djikstra dla pojedynczego wierzcholka, najkrotsza droga do reszty
{
    int vert = gr.getnumofvert();
    int *dist = new int[vert]; //Tablica najkrótszych drog

    bool *sptSet = new bool[vert]; //Tablica prawdy, czy dany wierzchołek został należy do najkrótszej ścieżki

    // Ustawienie dystansów na nieskończoność oraz sptSet na fałsz
    for (int i = 0; i < vert; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < vert - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        // Wybór minimalnego dystansu od wierzchołków nieprzetworzonych, u równe odl. od źródła dla pierw. iteracji
        int u = minDistance(dist, sptSet, vert);

        sptSet[u] = true;

        for (int v = 0; v < vert; v++)

            //Aktualizuje dist[v] tylko dla nieodwiedzonych wierzcholkow, jesli jest krawedz i odleglosc do wierzcholka od krawedzi
            //jest mniejsza od zapisanej wartości przebytej drogi
            if (!sptSet[v] && gr.areadjacent(u, v) && dist[u] != INT_MAX
                && dist[u] + gr.getedgelength(u, v) < dist[v])
                dist[v] = dist[u] + gr.getedgelength(u, v);
    }
    delete[] dist;
    delete[] sptSet;
}
