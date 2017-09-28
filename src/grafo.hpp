#ifndef GRAFO_HPP
#define GRAFO_HPP
#define INFINITY -1
using namespace std;

typedef float NReal;


class Grafo{
    private:
        NReal** mAdjacencia;
        NReal** mCaminhos;
        int* pessoas;
        int nVertices;

    public:
        // Sobrescreve o construtor
        Grafo(NReal**& mAdjacencia, int*& pessoas, int& nVertices);

        // Sobrescreve o destrutor
        ~Grafo();

        // Calcula a matriz de menores caminhos
        void calcularCaminhos();

        // Retorna a cidade escolhida de acordo com o critério 1
        int criterio1();

        // Retorna a cidade escolhida de acordo com o critério 2
        int criterio2();


        //------------------------
        // Funções para teste do programa:

        // Imprime matriz de caminhos 
        void testaMatrizDeCaminhos();

        // Imprime a matriz de adjacencia
        void printMAdjacencia();

        // Imprime a vetor de pessoas por cidade
        void printPessoas();

        //------------------------
};


// Implementacao dos templates
#include "grafo.cpp"

#endif /* end of include guard: GRAFO_HPP */
