//aloca matriz de tipo T
template<class T>
    void alocaMatriz(T**& m, int linhas, int colunas){
        //alocacao:
        try{
            m = new T*[linhas];
            m[0] = new T[linhas*colunas];
        }catch( std::bad_alloc &ba ){ //if new fails
            throw ba;
        }

        //lincando:
        int i;
        for (i = 1; i < linhas; i++) {
            m[i] = m[0] + i * colunas;
        }
    }

//deleta matriz alocada com a funcao alocaMatriz
template<class T>  
    void deletaMatriz(T**& m){ 
        if(m){
            if(m[0]) delete[] m[0]; //deleta o bloco maior, do tipo T
            m[0] = NULL;
            delete[] m; //deleta o vetor de ponteiros 
            m = NULL;
        }
    }

//imprime vetor
template<class T>
    void printVetor(T* &m, int size, int eLength, int ePrecision){
        int i;
        for (i = 0; i < size; i++) {
            std::cout << std::setw(eLength) << std::setprecision(ePrecision) << m[i];
        }
        cout << '\n';
    }

//imprime matriz
template<class T>
    void printMatriz(T** &m, int rows, int cols, int eLength, int eHeight, int ePrecision){
        int i, j;
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                std::cout << std::setw(eLength) << std::setprecision(ePrecision) << m[i][j];

            }
            std::cout << std::string(eHeight, '\n');

        }

    }
