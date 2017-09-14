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
NReal** Grafo::distanceMatrix(){
    //Coloque seu algoritmo aqui:
    int i,j,k,min1,min2;


    NReal **copyM;
    alocaMatriz(copyM,nVertices,nVertices);

    //Inicializa a cópia da matriz para o algorítmo
    for (j=0;j<nVertices;j++){
            for (k=0;k<nVertices;k++){
                //Se existe a estrada, atualiza a distância
                if (mIncidencia[j][k]) copyM[j][k] = mIncidencia[j][k];
                //Se for loop distância é zero
                else if (j==k) copyM[j][k] = 0;
                //Se não for nenhum dos casos a distância inicial é infinita
                else copyM[j][k]= INFINITY;
            }
    }

    //Algorítimo Floyd Marshall  O(n³) ='(
    for (i=0;i<nVertices;i++){
        for (j=0;j<nVertices;j++){
            for (k=0;k<nVertices;k++){
                //Inicializa min1
                min1 = copyM[j][k];
                //Inicializa min2
                if (copyM[j][i]==INFINITY || copyM[i][k]==INFINITY) min2 = INFINITY;
                else min2 = copyM[j][i]+copyM[i][k];

                //Compara a menor distância e atualiza a matriz
                if (min1==INFINITY) copyM[j][k] = min2;
                else if (min2==INFINITY) copyM[j][k] = min1;
                else min1>min2 ? copyM[j][k]=min2 : copyM[j][k]=min1;
            }
        }
    }

    return copyM;
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
