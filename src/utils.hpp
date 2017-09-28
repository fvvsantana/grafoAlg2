#ifndef UTILS_HPP
#define UTILS_HPP

using namespace std;

// Aloca matriz de tipo T
template<class T>
    void alocaMatriz(T**& m, int linhas, int colunas);

// Deleta matriz alocada com a funcao alocaMatriz
template<class T>
    void deletaMatriz(T**& m);

// Imprime um vetor
template<class T>
    void printVetor(T* &m, int size, int eLength = 4, int ePrecision = 3);

// Imprime uma matriz
template<class T>
    void printMatriz(T** &m, int rows, int cols, int eLength = 4, int eHeight = 2, int ePrecision = 3);

// Copia a matriz m2 para uma já alocada matriz m1
template<class T, class U>
    void copiaMatriz(T** &m1, U** m2, int rows, int cols);

// Implementacao dos templates
#include "utilsTemplates.hpp"

#endif /* end of include guard: UTILS_HPP */
