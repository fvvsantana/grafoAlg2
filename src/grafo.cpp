#include "utils.hpp"

//sobrecarga de construtor
Grafo::Grafo(NReal**& mIncidencia, int*& pessoas, int& nVertices){
    this->mIncidencia = mIncidencia;
    this->pessoas = pessoas;
    this->nVertices = nVertices;
}

//sobreescreve destrutor
Grafo::~Grafo(){
    //deleta vetor pessoas
    if(pessoas) delete pessoas;
    pessoas = NULL;
    //deleta a matriz de incidencia
    deletaMatriz(mIncidencia);
}

//peso do caminho minimo entre dois vertices
int Grafo::pesoCaminhoMinimo(int origem, int destino){
    //Coloque seu algoritmo aqui:

    return 0;
}

//Criterio 1
int Grafo::criterio1(){
    //Coloque seu algoritmo aqui:

    return 0;
}

//Criterio 2
int Grafo::criterio2(){
    //Coloque seu algoritmo aqui:

    return 0;
}
