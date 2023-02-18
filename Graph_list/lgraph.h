
#ifndef GRAPHLIST_LGRAPH_H
#define GRAPHLIST_LGRAPH_H

#include <iostream>
class ledge;


class lvertex
{
    int index;
    int numofconn;
    lvertex *adress;
    ledge **adjlist;

    public:
    lvertex();
    void increaseconn();
    int getnumofconn();
    lvertex* getadress();
    void initializevertex(int ind, lvertex *adr);
    ~lvertex();
};

class ledge
{
    int index;
    int weight;
    ledge *adress;
    lvertex *vert1;
    lvertex *vert2;
    ledge *adjle1;
    ledge *adjle2;

    public:
    ledge ();
    int returnindex();
    lvertex* getadress1()
    {
        return vert1;
    }
    lvertex* getadress2()
    {
        return vert2;
    }

    int returnweight();
    void setconnection(lvertex *v1, lvertex *v2);
    void initializeledge(int ind, int wei, lvertex *v1, lvertex *v2, ledge *adr);
    ~ledge();
};

class lgraph
{
    int vertnum;
    int edgenum;
    ledge *edgearr;
    lvertex *vertarr;
    ledge ***adjlist;

    public:
    int getweight(int i);
    lgraph();
    void initializelgraph(int numv, int density);
    void showgraph();
    ~lgraph();
};



#endif //GRAPHLIST_LGRAPH_H
