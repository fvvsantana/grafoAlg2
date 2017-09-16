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
                if (mIncidencia[j][k]) copyM[j][k] = mIncidencia[j][k];
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
    
    //Calcula e armazena a matriz de caminhos
    NReal** matrizDeCaminhos = Grafo::matrizDeCaminhos();

    //Multiplica as distancias pelas numero de pessoas da ciadade de partida
   	for (int linha = 0; linha < nVertices; linha++){
   		for(int coluna = 0; coluna < nVertices; coluna++){
   			matrizDeCaminhos[linha][coluna] = matrizDeCaminhos[linha][coluna] * this->pessoas[linha];
   		}
   	}

   	//Vari�veis para armazenar a cidade com menor distancia e o valor da dist�ncia.
   	int cidadeMenorDistancia = -1;
   	NReal menorDistancia = 0;
   	

	//Percorre a matriz de caminhos procurando a cidade de destino com o menor
	// somat�rio de dist�ncia a percorrer.
   	for(int coluna = 0; coluna < nVertices; coluna++){
   		for(int linha = 1; linha < nVertices; linha++){
   			matrizDeCaminhos[0][coluna] = matrizDeCaminhos[0][coluna] + matrizDeCaminhos[linha][coluna];
   		}
   		//Verifica se � a primeira dist�ncia calculada para inicalizar a corretamente
   		// a varir�vel menorDist�ncia
   		if(coluna == 0){
   			menorDistancia = matrizDeCaminhos[0][0];
   		}
   		//Verifica se o a distancia calculada � menor que a anterior.
   		else if(menorDistancia > matrizDeCaminhos[0][coluna]){
   			menorDistancia = matrizDeCaminhos[0][coluna];
   			cidadeMenorDistancia = coluna;
   		}
   	}

    return cidadeMenorDistancia;
}

//Criterio 2
int Grafo::criterio2(){
    //Coloque seu algoritmo aqui:

    return 0;
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
