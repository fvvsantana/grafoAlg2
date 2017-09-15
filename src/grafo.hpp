#ifndef GRAFO_HPP
#define GRAFO_HPP
#define INFINITY -1
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

        /*calcula a matriz de pesos dos caminhos minimos entre os 
        vertices usando o algoritmo Floyd Marshall*/
        NReal** matrizDeCaminhos();

        //Criterio 1
        int criterio1();

        //Criterio 2
        int criterio2();


        //------------------------
        //funcoes de teste:

        //imprime matriz de caminhos correspondente a matriz de incidencia
        void testaMatrizDeCaminhos();

        //imprime a matriz de incidencia
        void printMIncidencia();

        //imprime a vetor de pessoas por cidade
        void printPessoas();

        //------------------------
};


//implementacao dos templates
#include "grafo.cpp"

#endif /* end of include guard: GRAFO_HPP */
