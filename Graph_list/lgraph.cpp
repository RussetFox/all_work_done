#include "lgraph.h"

//________________________________________-VERTEX-_____________________
lvertex::lvertex() = default;

lvertex* lvertex:: getadress()
{
    return adress;
}
void lvertex:: initializevertex(int ind, lvertex *adr)
{
    this -> adress = adr;
    this -> index = ind;
    this -> numofconn = 0;
    this -> adjlist = NULL;
}
void lvertex::increaseconn() {this -> numofconn++;}

int lvertex::getnumofconn() {return this -> numofconn;}

lvertex:: ~lvertex() = default;


//______________________________________-EDGE-__________________________
ledge::ledge() = default;

void ledge:: initializeledge(int ind,int wei, lvertex *v1, lvertex *v2, ledge *adr) {
    this->index = ind;
    this->weight = wei;
    this->vert1 = v1;
    this->vert2 = v2;
    this->adress = adr;
}

int ledge::returnindex()
{
    return index;
}

int ledge:: returnweight()
{
    return weight;
}
void ledge:: setconnection(lvertex *v1, lvertex *v2)
{
    this -> vert1 = v1;
    this -> vert2 = v2;
}

ledge:: ~ledge() = default;



//__________________________________-GRAPH-____________________________

lgraph::lgraph() = default;

int lgraph::getweight(int i) {return edgearr[i].returnweight();}
void lgraph::initializelgraph(int numv, int density)
{
    this -> vertnum = numv;
    float help = (numv*(numv-1)*0.5)*(density*0.01);
    this -> edgenum = (int) help;
    this-> edgearr = new ledge[edgenum];
    for (int i = 0; i < edgenum; i++) edgearr[i].initializeledge(i,rand()%250, NULL, NULL, &edgearr[i]);
    this-> vertarr = new lvertex[vertnum];
    for(int i = 0; i < numv; i++) vertarr[i].initializevertex(i, &vertarr[i]);
    int help2 = 0;
    while (help2 < edgenum)
    {
        int rand1 = rand()%vertnum, rand2 = rand()%vertnum;
        if(edgearr[help2].getadress1() != vertarr[rand1].getadress() && edgearr[help2].getadress1() != vertarr[rand2].getadress()
        && edgearr[help2].getadress2() != vertarr[rand2].getadress() && edgearr[help2].getadress2() != vertarr[rand1].getadress())
        {
            vertarr[rand1].increaseconn();
            vertarr[rand2].increaseconn();
            edgearr[help2].setconnection(vertarr[rand1].getadress(), vertarr[rand2].getadress());
            std::cout << vertarr[rand1].getadress() << ' ' << vertarr[rand2].getadress() << '\n';
            std::cout << edgearr[help2].getadress1() << ' ' << edgearr[help2].getadress2() << '\n';
            help2++;
        }
    }
    ledge ***adjlist = new ledge**[numv];
    for (int i = 0; i < vertnum; i++)
    {
            adjlist[i] = new ledge*[vertarr[i].getnumofconn()+1];;
    }
    for (int i = 0; i < vertnum; i++)
    {
        for(int j = 0; j < vertarr[i].getnumofconn(); j++)
        {
            if (vertarr[i].getadress() == edgearr[j].getadress1() || vertarr[i].getadress() == edgearr[j].getadress2())
            {
                adjlist[i][j] = &edgearr[j];
            }
        }
    }
}

void lgraph::showgraph()
{
    for (int i = 0; i < vertnum; i++)
    {
        std:: cout << i <<": ";
        for (int j = 0; j < vertarr[i].getnumofconn(); j++) if (adjlist[i][j] != NULL) std:: cout << adjlist[i][j]->returnweight() << ' ';
        std:: cout << std:: endl;
    }
}

lgraph:: ~lgraph()
{
//    for (int i = 0; i < vertnum; i++) {
//        for (int j = 0; j < vertarr->getnumofconn(); j++) {
//            adjlist[i][j] = NULL;
//        }
//        delete[] adjlist[i];
//    }
//    delete [] adjlist;
    delete [] edgearr;
    delete [] vertarr;

}