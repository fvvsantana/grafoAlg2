#include <iostream>
#include "utils.hpp"
#include "grafo.hpp"

using namespace std;

typedef float NReal;

// Lê a entrada, aloca as matrizes e as preenche
void leEntrada(NReal**& mAdjacencia, int*& pessoas, int& nVertices);

// Função principal do programa
int main(){

    // Cria a matriz de adjacencia do grafo de cidades
    NReal** mAdjacencia;

    // Tamanho da matriz de adjacencia
    int nVertices;

    // Vetor do numero de pessoas por cidade
    int* pessoas;

    // Lê a entrada e preenche as matrizes
    try{

        leEntrada(mAdjacencia, pessoas, nVertices);

    } catch( std::bad_alloc &ba ){
        throw ba;
    }

    // Inicializa o grafo
    Grafo grafo(mAdjacencia, pessoas, nVertices);

    // Calcula e imprime as saídas
    cout << "\nResultado do Criterio 1:\n";
    cout << grafo.criterio1() << endl;
    cout << "\nResultado do Criterio 2:\n";
    cout << grafo.criterio2() << endl;

    // Note que o grafo ja desaloca a matriz em seu destrutor

    return 0;
}

// Lê a entrada, aloca as matrizes e as preenche
void leEntrada(NReal**& mAdjacencia, int*& pessoas, int& nVertices){

    // Número de estradas
    int nArestas;

    // Variáveis para o algoritmo
    int i, j, k;
    NReal pesoNovo, pesoAtual;

    // Pergunta o número de cidades e estradas
    cout << "Digite o numero de cidades e a quantidade de estradas:\n";
    cin >> nVertices;
    cin >> nArestas;

    // verifica se a entrada é um int e se está dentro dos valores esperados
    while (cin.fail() || nVertices < 2 || nVertices > 50 || nArestas < 1 || nArestas > (nVertices*nVertices)) {
        cin.clear();
        cin.ignore(256,'\n');
    	cout << "Entrada invalida, insira novamente\n";
    	cin >> nVertices;
    	cin >> nArestas;
    }

    // Tenta alocar na memória
    try{
        // Aloca o vetor pessoas
        pessoas = new int[nVertices];

        // Aloca matriz de adjacencia
        alocaMatriz(mAdjacencia, nVertices, nVertices);

    }catch( std::bad_alloc &ba ){
        throw ba;
    }

    // Preenche o vetor pessoas
    cout << "Digite o numero de pessoas por cidade:\n";
    for(i=0; i<nVertices; i++){
        cin >> pessoas[i];

        // Verifica se a entrada está correta
        while (cin.fail() || pessoas[i] < 0 || pessoas[i] > 50) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "Quantidade invalida, insira novamente\n";
            cin >> pessoas[i];
        }
    }

    // Preenche a matriz de adjacencia com zero em todas posições
    for(i=0; i < nVertices * nVertices; i++){
        mAdjacencia[0][i] = 0;
    }


    // Preenche a matriz de adjacencias
    cout << "Digite as arestas e suas distancias:\n";
    for(k=0; k<nArestas; k++){
        cin >> i;
        cin >> j;
        cin >> pesoNovo;

        // Verifica se a entrada está correta
        while (cin.fail() || i < 0 || i > nVertices || j < 0 || j > nVertices || pesoNovo <= 0 || pesoNovo > 100) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "Valores invalidos, insira novamente\n";
            cin >> i;
            cin >> j;
            cin >> pesoNovo;
        }

        pesoAtual = mAdjacencia[i][j];

        // Se o peso atual ja foi inicializado
        if(pesoAtual){
            // Compara os dois pesos e coloca o menor peso
            if(pesoAtual > pesoNovo){
                mAdjacencia[i][j] = pesoNovo;
                mAdjacencia[j][i] = pesoNovo;
            }
        // Se o peso nao foi inicializado
        } else{
            // Inicializa o peso
            mAdjacencia[i][j] = pesoNovo;
            mAdjacencia[j][i] = pesoNovo;
        }
    }
}
