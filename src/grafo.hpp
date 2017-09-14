#ifndef GRAFO_HPP
#define GRAFO_HPP
#define MAXDISTANCE 9999
using namespace std;

typedef float NReal;


class Grafo{
    private:
        NReal** mIncidencia;
        int* pessoas;
        int nVertices;

    public:
        //sobrecarga de construtor
        Grafo(NReal**& mIncidencia, int*& pessoas, int& nVertices);

        //sobreescreve destrutor
        ~Grafo();

        //peso do caminho minimo entre dois vertices
        NReal** distanceMatrix();

        //Criterio 1
        int criterio1();

        //Criterio 2
        int criterio2();
};


//implementacao dos templates
#include "grafo.cpp"

#endif /* end of include guard: GRAFO_HPP */
