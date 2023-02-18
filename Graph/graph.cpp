#include "graph.h"


//__________________________________WIERZCHOLKI_______________________________________
matrixvertex:: matrixvertex() = default;

void matrixvertex::initializevert(int ind, matrixvertex *adr)
{
    this -> index = ind;
    this -> adress = adr;
}

void matrixvertex:: setadress (matrixvertex *ad)
{
    this -> adress = ad;
}

int matrixvertex::returnindex()
{
    return index;
}

void matrixvertex::showmatrixvertex()
{
    std:: cout << "Adres: " << adress << std::endl;
    std:: cout << "Numer: " << index << std:: endl;
}

matrixvertex:: ~matrixvertex() = default;



//_________________________________Krawedzie___________________________________
matrixedge::matrixedge()=default;

void matrixedge:: initializeedge(int ind, matrixedge *adr, matrixvertex *adr1, matrixvertex *adr2, int weigh)
{
    this -> index = ind;
    this -> adress = adr;
    this -> vertex1 = adr1;
    this -> vertex2 = adr2;
    this -> matrixedgelength = weigh;
}

void matrixedge::setadress(matrixedge *adressofmatrixedge)
{
    adress = adressofmatrixedge;
}

void matrixedge:: showmatrixedges()
{
    //std:: cout  << index << " ";
    std:: cout << "Dlugosc: " << matrixedgelength << std:: endl;
    //std:: cout << "Sasiadujace wierzcholki: " << vertex1->returnindex() << ' ' << vertex2->returnindex()
    //<< std::endl;
}

int matrixedge::edgelenght()
{
    return matrixedgelength;
}
matrixedge:: ~matrixedge()=default;
//_______________________________________GRAF___________________________________-
matrixgraph:: matrixgraph()
{
    this-> edgearr = NULL;
    this-> vertarr = NULL;
    this -> adjmatrix = NULL;
}

void matrixgraph::initialize(int vertnum, int density)
{
    this -> numberofvert = vertnum;
    float help = (vertnum*(vertnum-1)*0.5)*(density*0.01);
    this -> numberofed = (int) help;
    this-> edgearr = new matrixedge[numberofed];
    this-> vertarr = new matrixvertex[numberofvert];
    for (int i = 0; i < numberofvert; i++) vertarr[i].initializevert(i, &vertarr[i]);
    this -> adjmatrix = new matrixedge** [numberofvert];
    for (int i = 0; i < numberofvert; i++) {adjmatrix[i] = new matrixedge*[numberofvert];
        for (int j = 0; j < numberofvert; j++) adjmatrix[i][j] = NULL;};
    int counter = 0;
    while (counter < numberofed)
    {
        int rand1 ,rand2;
        rand1 = rand()%numberofvert; rand2 = rand()%numberofvert;
        if (adjmatrix[rand1][rand2] == NULL && rand1 != rand2)
        {
            edgearr[counter].initializeedge(counter, &edgearr[counter], &vertarr[rand1], &vertarr[rand2], rand()%250);
            adjmatrix[rand1][rand2] = &edgearr[counter]; adjmatrix[rand2][rand1] = &edgearr[counter];
            counter++;
        }
    }
}

void matrixgraph::showvertices()
{
    for (int i = 0; i < numberofvert; i++)
        vertarr[i].showmatrixvertex();
}

int matrixgraph:: getnumofvert()
{
    return this->numberofvert;
}

int matrixgraph:: getnumofed()
{
    return this->numberofed;
}

void matrixgraph:: showmatrixedges()
{
    for (int i = 0; i < numberofed; i++)
        edgearr[i].showmatrixedges();
}

void matrixgraph::showadjacencymatrix()
{
    for (int i = 0; i < numberofvert; i++) {
        for (int j = 0; j < numberofvert; j++) {
            if (adjmatrix[i][j] != NULL) adjmatrix[i][j]->showmatrixedges();
            else std::cout << "NULL ";
        }
        std::cout << std::endl;
    }
}

int matrixgraph::getedgelength(int index1, int index2)
{
    return adjmatrix[index1][index2]->edgelenght();
}

bool matrixgraph::areadjacent(int ind1, int ind2)
{
    if (adjmatrix[ind1][ind2] != NULL) return true;
    return false;
}

matrixvertex matrixgraph::getvertex(int index)
{
    return vertarr[index];
}

matrixedge matrixgraph::getedge(int index)
{
    return edgearr[index];
}

matrixgraph:: ~matrixgraph()
{
    for (int i = 0; i < numberofvert; i++) {
        for (int j = 0; j < numberofvert; j++) {
            adjmatrix[i][j] = NULL;
        }
        delete[] adjmatrix[i];
    }
    delete [] adjmatrix;
    delete[] edgearr;
    delete[] vertarr;
}