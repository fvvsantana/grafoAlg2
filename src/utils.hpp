#ifndef UTILS_HPP
#define UTILS_HPP

using namespace std;

//aloca matriz de tipo T
template<class T>
    void alocaMatriz(T**& m, int linhas, int colunas);

//deleta matriz alocada com a funcao alocaMatriz
template<class T>  
    void deletaMatriz(T**& m);

//imprime vetor
template<class T>
    void printVetor(T* &m, int size, int eLength = 4, int ePrecision = 3);

//imprime matriz
template<class T>
    void printMatriz(T** &m, int rows, int cols, int eLength = 4, int eHeight = 2, int ePrecision = 3);

//copia a matriz m2 para uma ja alocada matriz m1
template<class T, class U>  
    void copiaMatriz(T** &m1, U** m2, int rows, int cols);

//implementacao dos templates
#include "utilsTemplates.hpp"

#endif /* end of include guard: UTILS_HPP */
