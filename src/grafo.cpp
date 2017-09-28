#include "utils.hpp"

// Sobrescreve o construtor
Grafo::Grafo(NReal**& mAdjacencia, int*& pessoas, int& nVertices){
    this->mAdjacencia = mAdjacencia;
    this->pessoas = pessoas;
    this->nVertices = nVertices;
    mCaminhos = NULL;
}

// Sobrescreve o destrutor
Grafo::~Grafo(){
    // Deleta vetor pessoas
    if(pessoas) delete pessoas;
    pessoas = NULL;
    // Deleta a matriz de adjacencia
    deletaMatriz(mAdjacencia);
    // Deleta a matriz de caminhos
    deletaMatriz(mCaminhos);
}

//Calcular caminhos:
// Calcula o menor caminho entre todos vértices do grafo e salva na matriz mCaminhos
void Grafo::calcularCaminhos(){

    // Cria variáveis para o algoritmo
    int i,j,k,min1,min2;

    // Aloca a matriz, caso necessário
    if (!mCaminhos) {
        try{
            alocaMatriz(mCaminhos, nVertices, nVertices);

        } catch( std::bad_alloc &ba ){
            throw ba;
        }
    }

    // Inicia a matriz de menores caminhos
    for (j=0; j<nVertices; j++){
            for (k=0; k<nVertices; k++){

                // Se for um self loop a distância é zero
                if (j==k) mCaminhos[j][k] = 0;

                // Se existe uma estrada, copia para a nova matriz
                else if (mAdjacencia[j][k]) mCaminhos[j][k] = mAdjacencia[j][k];

                // Se não for nenhum dos casos, a distância inicial é infinita
                else mCaminhos[j][k]= INFINITY;
            }
    }

    // Algoritmo Floyd Warshall  O(n³)
    for (i=0; i<nVertices; i++){
        for (j=0; j<nVertices; j++){
            for (k=0; k<nVertices; k++){

                // Inicializa min1 com o caminho atual
                min1 = mCaminhos[j][k];

                // Inicializa min2 com o caminho passando por i
                if (mCaminhos[j][i]==INFINITY || mCaminhos[i][k]==INFINITY) min2 = INFINITY;
                else min2 = mCaminhos[j][i]+mCaminhos[i][k];

                // Compara a menor distância e atualiza a matriz
                if (min1==INFINITY) mCaminhos[j][k] = min2;
                else if (min2==INFINITY) mCaminhos[j][k] = min1;
                else min1>min2 ? mCaminhos[j][k]=min2 : mCaminhos[j][k]=min1;
            }
        }
    }
}


//Criterio 1:
// Encontra a cidade com o menor custo de deslocamento total
// Para isso, multiplica-se cada coluna da matriz de caminhos pelo número de pessoas daquela cidade
// A cidade escolhida será aquela com a menor soma da coluna
int Grafo::criterio1(){

    // Calcula a matriz de caminhos, caso ainda esteja vazia
    if (!mCaminhos)
        calcularCaminhos();
    
    // Cria uma cópia da matriz de caminhos
    NReal** matrizCaminhos;
    try{
        alocaMatriz(matrizCaminhos, nVertices, nVertices);
        copiaMatriz(matrizCaminhos, mCaminhos, nVertices, nVertices);

    } catch( std::bad_alloc &ba ){
        throw ba;
    }

    // Multiplica as distancias pelas numero de pessoas da ciadade de partida
   	for (int linha = 0; linha < nVertices; linha++){
   		for(int coluna = 0; coluna < nVertices; coluna++){
   			matrizCaminhos[linha][coluna] = matrizCaminhos[linha][coluna] * pessoas[linha];
   		}
   	}

   	// Variáveis para armazenar a cidade com menor distancia e o valor da dist?cia.
   	int cidadeMenorDistancia = 0;
   	NReal menorDistancia = 0;
   	

	// Percorre a matriz de caminhos procurando a cidade de destino com o menor
	//  somatório de distâcias a percorrer
   	for(int coluna = 0; coluna < nVertices; coluna++){
   		for(int linha = 1; linha < nVertices; linha++){
   			matrizCaminhos[0][coluna] = matrizCaminhos[0][coluna] + matrizCaminhos[linha][coluna];
   		}
   		// Verifica se é a primeira distâcia calculada para inicalizar o menor corretamente
   		//  a varirável menorDistancia
   		if(coluna == 0){
   			menorDistancia = matrizCaminhos[0][0];
   		}
   		// Verifica se o a distancia calculada é menor que a anterior
   		else if(menorDistancia > matrizCaminhos[0][coluna]){
   			menorDistancia = matrizCaminhos[0][coluna];
   			cidadeMenorDistancia = coluna;
   		}
   	}

    // Deleta a matriz criada
    deletaMatriz(matrizCaminhos);

    return cidadeMenorDistancia;
}


//Criterio 2:
// Algoritmo Floyd Marshall adaptado para gerar uma matriz com o vértice anterior a cada passo
// Essa matriz será utilizada para encontrar o vértice por onde passam mais menores caminhos, ou seja,
//  o vértice com maior valor de Betweenness centrality
int Grafo::criterio2(){

    // Cria variáveis para o algoritmo
    int i,j,k,min1,min2;

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
                else if (mAdjacencia[j][k]) matrizCaminhos[j][k] = mAdjacencia[j][k];

                // Se não for nenhum dos casos a distância inicial é infinita
                else matrizCaminhos[j][k]= INFINITY;

                // Inicia a matriz de anteriores (inicialmente serão todos -1)
                matrizAnterior[j][k] = -1;
            }
    }

    // Algoritmo Floyd Warshall adaptado
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

    // Caso a matriz de caminhos do grafo ainda não tenha sido calculada, aproveita o resultado
    //  deste algoritmo e salva para uso futuro
    if (!mCaminhos)
        mCaminhos = matrizCaminhos;
    else
        deletaMatriz(mCaminhos);

    // A cidade desejada será aquela que é intermediária para mais caminhos
    // O vetor vezes irá guardar na posição 'i' quantas vezes a cidade 'i' foi intermediária
    int vezes[nVertices];

    // Inicia todas posições com 0
    for (i=0; i<nVertices; i++) {
        vezes[i] = 0;
    }

    // Note que nVertices posições são suficientes, pois esse é o maior número possível de uma cidade

    // Conta quantas vezes cada cidade é atravessada
    int temp;
    for (i=0; i<nVertices; i++) {
        for (j=i+1; j<nVertices; j++) {
            temp = j;
            while (matrizAnterior[i][temp] != -1) {
                vezes[matrizAnterior[i][temp]]++;
                temp = matrizAnterior[i][temp];
            }
        }
    }

    // Acha a maior posição do vetor (que também será a cidade escolhida)
    int maior = 0;
    for (i=1; i<nVertices; i++) {
        if (vezes[i] > vezes[maior])
            maior = i;
    }

    // Deleta a matriz criada
    deletaMatriz(matrizAnterior);

    return maior;
}
