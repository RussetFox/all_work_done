#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#include <iostream>
#include <array>

class matrixvertex{
        int index;
        //bool ifvisisted;
        matrixvertex *adress;
    public:
        matrixvertex();
        void initializevert(int ind, matrixvertex *adr);
        int returnindex();
        void setadress(matrixvertex *ad);
        void showmatrixvertex();
        ~matrixvertex();
};

class matrixedge{
        int index;
        int matrixedgelength;
        matrixedge *adress;
        matrixvertex *vertex1;
        matrixvertex *vertex2;
    public:
        matrixedge();
        void initializeedge(int ind, matrixedge *adr, matrixvertex *adr1, matrixvertex *adr2, int weigh);
        void setadress (matrixedge *adressofmatrixedge);
        int edgelenght();
        void showmatrixedges();
        ~matrixedge();
};

class matrixgraph {
        int numberofvert;
        int numberofed;
        matrixvertex *vertarr;
        matrixedge *edgearr;
        matrixedge*** adjmatrix;
    public:
        matrixgraph();
        matrixvertex getvertex(int index);
        matrixedge getedge(int index1);
        void initialize(int numv, int density);
        int getnumofvert();
        int getnumofed();
        int getedgelength(int index1, int index2);
        bool areadjacent(int ind1, int ind2); // prawda jesli sasiadujace
        void showvertices(); // wszystkie wierzcholki w grafie
        void showmatrixedges(); // wszystkie krawedzie w grafie
        void showadjacencymatrix();
        ~matrixgraph();

};

#endif //GRAPH_GRAPH_H
