#include <iostream>
#include <string>
#include <iomanip>
#include "utils.hpp"
#include "grafo.hpp"

using namespace std;

typedef float NReal;

//le entrada, aloca matrizes e as preenche
void leEntrada(NReal**& mIncidencia, int*& pessoas, int& nVertices);

int main(){
    //matriz de incidencia do grafo das cidades
    NReal** mIncidencia;
    //tamanho da matriz de incidencia
    int nVertices;     

    //matriz do numero de pessoas por cidade
    int* pessoas;

    //note que o tamanho do vetor pessoas[] sera nVertices

    //entrada
    cout << "Insira a entrada:\n";
    try{

        //le entrada e preenche as matrizes
        leEntrada(mIncidencia, pessoas, nVertices);

    }catch( std::bad_alloc &ba ){
        throw ba;
    }

    //inicializa o grafo
    Grafo grafo(mIncidencia, pessoas, nVertices);

    //Area de testes:
    //
    //************************************

    //grafo.printMIncidencia();

    //grafo.printPessoas();

    //grafo.testaMatrizDeCaminhos();
    
    //************************************


    //imprime saida
    cout << "Saida:\n";
    cout << grafo.criterio1() << '\n';
    cout << grafo.criterio2() << '\n';

    //note que o grafo ja desaloca a matriz em seu destrutor
    return 0;
}

//le entrada, aloca matrizes e as preenche
void leEntrada(NReal**& mIncidencia, int*& pessoas, int& nVertices){
    //numero de estradas
    int nArestas;
    int i, j, k;
    NReal pesoNovo, pesoAtual;

    cin >> nVertices;
    cin >> nArestas;

    try{
        //aloca o vetor pessoas
        pessoas = new int[nVertices];

        //aloca matriz de incidencia
        alocaMatriz(mIncidencia, nVertices, nVertices);

    }catch( std::bad_alloc &ba ){
        throw ba;
    }

    //preenche pessoas[]
    for(i=0; i<nVertices; i++){
        cin >> pessoas[i];
    }
    
    //preenche a matriz de incidencia com zero em tudo
    for(i=0; i < nVertices * nVertices; i++){
        mIncidencia[0][i] = 0;
    }


    //preenche a matriz de incidencia
    for(k=0; k<nArestas; k++){
        cin >> i;
        cin >> j;
        cin >> pesoNovo;

        pesoAtual = mIncidencia[i][j];

        //se o peso atual ja foi inicializado
        if(pesoAtual){
            //compara os dois pesos e coloca o menor peso
            if(pesoAtual > pesoNovo){
                mIncidencia[i][j] = pesoNovo;
                mIncidencia[j][i] = pesoNovo;
            }
        //se o peso nao foi inicializada
        }else{
            //inicializa o peso
            mIncidencia[i][j] = pesoNovo;
            mIncidencia[j][i] = pesoNovo;
        }
    }
}

