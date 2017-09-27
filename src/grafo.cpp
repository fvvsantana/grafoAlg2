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

        /*calcula a matriz de pesos dos caminhos minimos entre os 
        vertices usando o algoritmo Floyd Marshall*/
NReal** Grafo::matrizDeCaminhos(){
    //Coloque seu algoritmo aqui:
    int i,j,k,min1,min2;

    // Cria a matriz que guardará os menores caminhos
    NReal **copyM;

    // Tenta alocar a matriz
    try{
        alocaMatriz(copyM, nVertices, nVertices);

    } catch( std::bad_alloc &ba ){
        throw ba;
    }

    // Inicia a matriz de menores caminhos
    for (j=0; j<nVertices; j++){
            for (k=0; k<nVertices; k++){
                // Se for um self loop a distância é zero
                if (j==k) copyM[j][k] = 0;

                // Se existe uma estrada, copia para a de menores caminhos
                else if (mIncidencia[j][k]) copyM[j][k] = mIncidencia[j][k];

                // Se não for nenhum dos casos a distância inicial é infinita
                else copyM[j][k]= INFINITY;
            }
    }

    // Algorítimo Floyd Warshall  O(n³)
    for (i=0; i<nVertices; i++){
        for (j=0; j<nVertices; j++){
            for (k=0; k<nVertices; k++){

                //Inicializa min1 com o caminho atual
                min1 = copyM[j][k];

                //Inicializa min2 com o caminho passando por i
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

//Criterio 2:
// Algorítimo Floyd Marshall adaptado para gerar uma matriz com o vértice anterior a cada passo
// Essa matriz será utilizada para encontrar o betweenness centrality
int Grafo::criterio2(){

    int i,j,k,l,min1,min2;

    // Cria a matriz que guardará os menores caminhos
    NReal** matrizCaminhos;

    // Cria uma matriz para guardar o ponto intermediário entre dois vértices
    int** matrizAnterior;
    
    // Tenta alocar as matrizes
    try{
        alocaMatriz(matrizCaminhos, nVertices, nVertices);
        alocaMatriz(matrizAnterior, nVertices, nVertices);

    }catch( std::bad_alloc &ba ){
        throw ba;
    }

    // Inicia a matriz de menores caminhos e a matriz de anteriores
    for (j=0; j<nVertices; j++){
            for (k=0; k<nVertices; k++){

                // Se for um self loop a distância é zero
                if (j==k) matrizCaminhos[j][k] = 0;

                // Se existe uma estrada, copia para a de menores caminhos
                else if (mIncidencia[j][k]) matrizCaminhos[j][k] = mIncidencia[j][k];

                // Se não for nenhum dos casos a distância inicial é infinita
                else matrizCaminhos[j][k]= INFINITY;

                // Inicia a matriz de anteriores (inicialmente serão todos -1)
                matrizAnterior[j][k] = -1;
            }
    }

    // Algorítimo Floyd Warshall adaptado
    for (i=0; i<nVertices; i++){
        for (j=0; j<nVertices; j++){
            for (k=0; k<nVertices; k++){

                // Inicializa min1 com o caminho atual
                min1 = matrizCaminhos[j][k];

                // Inicializa min2 com o caminho passando por i
                if (matrizCaminhos[j][i]==INFINITY || matrizCaminhos[i][k]==INFINITY) min2 = INFINITY;
                else min2 = matrizCaminhos[j][i]+matrizCaminhos[i][k];

                // Verifica se vale a pena mudar e atualiza as matrizes
                if (min2!=INFINITY && (min1==INFINITY || min1>min2) ) {
                    matrizCaminhos[j][k] = min2;

                    // Neste momento a matriz de anteriores é atualizada:
                    matrizAnterior[j][k] = i;
                }
            }
        }
    }

    // A cidade desejada será aquela que aparece mais vezes na matriz de anteriores (moda da matriz)
    
    // Cria e inicia um vetor que irá contar quantas vezes cada valor aparece
    // > Só precisa ter nVertices posições, pois esse será o maior número no nosso caso
    int vezes[nVertices];
    for (i=0; i<nVertices; i++) {
        vezes[i] = 0;
    }

    // Conta quantas vezes cada número aparece
    for (i=0; i<nVertices; i++) {
        for (j=0; j<nVertices; j++) {
            if (matrizAnterior[i][j] != -1)
                vezes[matrizAnterior[i][j]]++;
        }
    }

    // Acha a maior posição do vetor (que também será a moda da matriz)
    int maior = 0;
    for (i=1; i<nVertices; i++) {
        if (vezes[i] > vezes[maior])
            maior = i;
    }

    return maior;
}



//------------------------
//funcoes de teste:

//imprime matriz de caminhos correspondente a matriz de incidencia
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


//imprime a matriz de incidencia
void Grafo::printMIncidencia(){
    cout << "-------------------\n";
    cout << "Teste\nMatriz de incidencia:\n";
    printMatriz(mIncidencia, nVertices, nVertices);
    cout << "-------------------\n";
}

//imprime a vetor de pessoas por cidade
void Grafo::printPessoas(){
    cout << "-------------------\n";
    cout << "Teste\nVetor de pessoas por cidade:\n";
    printVetor(pessoas, nVertices);
    cout << "-------------------\n";
}
//------------------------
