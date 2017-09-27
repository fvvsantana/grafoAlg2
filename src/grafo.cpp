#include "utils.hpp"

//sobrecarga de construtor
Grafo::Grafo(NReal**& mAdjacencia, int*& pessoas, int& nVertices){
    this->mAdjacencia = mAdjacencia;
    this->pessoas = pessoas;
    this->nVertices = nVertices;
}

//sobreescreve destrutor
Grafo::~Grafo(){
    //deleta vetor pessoas
    if(pessoas) delete pessoas;
    pessoas = NULL;
    //deleta a matriz de adjacencia
    deletaMatriz(mAdjacencia);
}

        /*calcula a matriz de pesos dos caminhos minimos entre os 
        vertices usando o algoritmo Floyd Marshall*/
NReal** Grafo::matrizDeCaminhos(){
    //Coloque seu algoritmo aqui:
    int i,j,k,min1,min2;


    NReal **copyM;
    try{

        alocaMatriz(copyM,nVertices,nVertices);

    }catch( std::bad_alloc &ba ){
        throw ba;
    }

    //Inicializa a c�pia da matriz para o algor�tmo
    for (j=0;j<nVertices;j++){
            for (k=0;k<nVertices;k++){
                //Se existe a estrada, atualiza a dist�ncia
                if (mAdjacencia[j][k]) copyM[j][k] = mAdjacencia[j][k];
                //Se for loop dist�ncia � zero
                else if (j==k) copyM[j][k] = 0;
                //Se n�o for nenhum dos casos a dist�ncia inicial � infinita
                else copyM[j][k]= INFINITY;
            }
    }

    //Algor�timo Floyd Marshall  O(n�) ='(
    for (i=0;i<nVertices;i++){
        for (j=0;j<nVertices;j++){
            for (k=0;k<nVertices;k++){
                //Inicializa min1
                min1 = copyM[j][k];
                //Inicializa min2
                if (copyM[j][i]==INFINITY || copyM[i][k]==INFINITY) min2 = INFINITY;
                else min2 = copyM[j][i]+copyM[i][k];

                //Compara a menor dist�ncia e atualiza a matriz
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



//------------------------
//funcoes de teste:

//imprime matriz de caminhos correspondente a matriz de adjacencia
void Grafo::testaMatrizDeCaminhos(){
    cout << "-------------------\n";
    cout << "Teste\nMatriz de caminhos:\n";
    //pega matriz de caminhos
    NReal** aux = matrizDeCaminhos();
    //imprime matriz
    printMatriz(aux, nVertices, nVertices);
    //deleta matriz
    deletaMatriz(aux);
    cout << "-------------------\n";
}

//------------------------
