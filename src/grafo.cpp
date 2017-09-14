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

    //inicializa todos os caminhos com a dist�ncia m�xima
    for ( i = 0 ; i < nVertices ; i++ ){
        for ( j = 0 ; j < nVertices ; j++ ){
            copyM[i][j]= MAXDISTANCE;
        }
    }

    //Inicializa a c�pia da matriz para o altor�tmo
    for (j=0;j<nVertices;j++){
            for (k=0;k<nVertices;k++){
                //Se existe a estrada, atualiza a dist�ncia
                if (mIncidencia[j][k]) copyM[j][k] = mIncidencia[j][k];
                //Loops s�o de dist�ncia zero
                if (j==k) copyM[j][k] = 0;
            }
    }

    //Algor�timo Floyd Marshall
    for (i=0;i<nVertices;i++){
        for (j=0;j<nVertices;j++){
            for (k=0;k<nVertices;k++){
                min1 = copyM[j][k];
                min2 = copyM[j][i]+copyM[i][k];
                //Compara a menor dist�ncia e atualiza a matriz
                min1>min2 ? copyM[j][k]=min2 : copyM[j][k]=min1;
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
