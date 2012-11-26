 /* Projecto ESINF - 2� ano LEI -ISEP
 * Outubro 2012
 *
 * File:   DynArray.h
 *
 * Created on October 23, 2012, 1:51 AM
 */

#ifndef DYN2DARRAY_H
#define DYN2DARRAY_H

#include <iostream>
using namespace std;

/*
 * Class DYN2DARRAY: permite criar um array bidimensional din�mico, para objectos de
 * qualquer tipo visto tratar-se basear-se numa fun��o template
 * @author Jo�o Carreira, Vitor Hugo Anjos
 * @version: 2.0 (Oct 2012)
 */
template <class T>
class Dyn2DArray{

private:
	/* dimens�o do array 2D (n� linhas = n� colunas = cap) */
	int cap;
	/* �ndice do vector 2D (pode indicar colunas OU linhas) */
	int maxRC;
	/* array 2D */
	T **vec;

public:
	/* prot�tipos de construtores e destrutor */
	Dyn2DArray();
	Dyn2DArray(int dim);
	Dyn2DArray(const Dyn2DArray &d);
	~Dyn2DArray();

	/* prot�tpos de GETS */
	int getCap();
	T getVec(){
		return vec;
	}

	/* prot�tipos de outros m�todos */
	bool insert(const T &elem, int row, int col);
	void write(ostream &out) const;


	void returnElem(int r, int c, T &elem) const{
		cout << vec[r][c];
		// cout << "done";
		cout << elem;

		elem = vec[r][c];
	}

	T returnElem(int a, int b){
		return vec[a][b];
	}


};


/**
 * Construtor sem par�metros: cria um array 2D com dimens�o "default" de 2*2
 */
template <class T>
Dyn2DArray<T>::Dyn2DArray(){
	cap = 12;
	vec = new T *[cap];
	for(int i = 0; i < cap; i++)
		vec[i] = new T[cap];
	maxRC = cap;
}


/**
 * Construtor com par�metros: cria um array 2D com dimens�o n*n, em que n
 * � passado por par�metro
 * @param dim 	dimens�o a atribuir ao array 2D
 */
template <class T>
Dyn2DArray<T>::Dyn2DArray(int dim){
	cap = dim;
	vec = new T *[cap];
	for(int i = 0; i < cap; i++)
		vec[i] = new T[cap];
	maxRC = cap;
}


/**
 * Construtor c�pia
 */
template <class T>
Dyn2DArray<T>::Dyn2DArray(const Dyn2DArray &d){
	cap = d.cap;
	vec = new T *[cap];
	for(int i = 0; i < cap; i++)
		vec[i] = new T[cap];
	for(int i = 0; i < cap; i++)
		for(int j = 0; i < cap; j++)
			if(d.vec[i][j] != NULL)
				vec[i][j] = d.vec[i][j] -> clone();
}


/**
* Destrutor de objectos do tipo DYN2DARRAY
*/
template <class T>
Dyn2DArray<T>::~Dyn2DArray(){
 	for(int i = 0; i < cap; i++)
 		delete [] vec[i];
 	delete [] vec;
}

/**
 * M�todo p�blico de acesso � capacidade do array2D
 * return	capacidade de array2D (ou seja, o n� m�ximo de linhas e
 *			colunas que possui) */
template <class T>
int Dyn2DArray<T>::getCap(){
	return cap;
}


/**
* Insere um elemento, passado por par�metro, no array; altera, se necess�rio,
* a capacidade do vector; este m�todo permite a inser��o de um elemento numa
* posi��o espec�fica da matriz, logo a fun��o inclui como par�metros a linha
* e coluna onde introduzir o elemento; notar que este m�todo produz uma matriz
* quadrada, em que um elemento introduzido na posi��o (a,b) vai ser tamb�m
* introduzido na (b,a); caso j� exista um elemento diferente do tipo n�o
* inicializado na posi��o (a,b) ou (b,a) da matriz n�o ocorre introdu��o desse
* elemento
* @param elem 		� a refer�ncia do elemento a introduzir no array
* @param row		� o n�mero da linha onde introduzir o elemento
* @param col 		� o n�mero da coluna onde introduzir o elemento
* @return 			true, caso inser��o do elemento seja bem sucedida; false,
					no caso contr�rio
*/
template <class T>
bool Dyn2DArray<T>::insert(const T &elem, int row, int col){
	/* verifica o m�ximo entre row e col e atribui esse m�ximo a maxTemp */
	int maxTemp;
	if(row > col)
		maxTemp = row;
	else
		maxTemp = col;
	/* verifica se array 2D tem capacidade para guardar novo elemento, com
	base no maxTemp */
	if(maxTemp > cap){
		/* guarda capacidade anterior do vector (para ser usado no momento
		da c�pia */
		int prevCap = cap;
		/* nova capacidade do array passa a ser maxTemp+1 */
		cap = maxTemp + 1;
		/* array2D tempor�rio com dimens�o actualizada */
		T **newVec = new T *[cap];
		for(int i = 0; i < cap; i++)
			newVec[i] = new T[cap];
		/* copiar array 2D para array 2D tempor�rio */
		for(int i = 0; i < prevCap; i++)
			for(int j = 0; j < prevCap; j++)
				newVec[i][j] = vec[i][j];
		/* libertar recursos do array copiado */
		for(int i = 0; i < prevCap; i++)
			delete [] vec[i];
		delete [] vec;
		/* atribuir array tempor�rio a vec */
		vec = newVec;
	}
	/* introdu��o do elemento na posi��o indicada (originando um array 2D
	sim�trico relativamente � diagonal principal) */
	/* apontator para new T, necess�rio para compara��o com tipos n�o inicializados */
	T *blank = new T;
	/* se elemento na posi��o [row][col] for igual a um tipo n�o inicializado, ent�o
	pode-se introduzir o elemento */
	if((vec[row][col] == *blank) || (vec[col][row] == *blank)){
		vec[row][col] = elem;
		vec[col][row] = elem;
		/* retorna true indiciado que inser��o foi bem sucedida*/
		return true;
	}
	else
		/* retorna false para indicar inser��o n�o foi bem sucedida*/
		return false;

}


/**
 * M�todo de escrita, imprime no ecr� toda a informa��o sobre cada um dos
 * elementos que existem no vector 2D; como o array 2D representa uma matriz
 * sim�trica apenas � mostrado no ecr� os elementos da parte superior (incluindo
 * a diagonal principal)
 * @param out
 */
template <class T>
void Dyn2DArray<T>::write(ostream &out) const {
	/* apontator para new T, necess�rio para compara��o com tipos n�o inicializados */
	T *blank = new T;
	for(int i = 0; i < cap; i++){
		/* linha seguinte apenas serve para visualizar as linhas da matriz,
		dever� ser comentada ou eliminada no programa final */
		// cout << "****Linha " << i << "*****" << endl;
		/* com j=i garante-se que apenas s�o mostrados os elementos a partir
		da diagonal principal em diante; para mostrar a matriz 2D inteira basta
		substituir j=i por j=0 */
		for(int j = i; j < cap; j++)
			/* apenas imprime o elemento do array2D se f�r diferente de um tipo n�o
			inicializado */
			if(vec[i][j] != *blank){
				cout << "Distancia do posto " << i << " ao posto " << j << endl;
				cout << vec[i][j] << endl;
			}
	}
}


/**
 * Sobrecarga do operador de stream out
 * @param out   	refer�ncia do standard output
 * @param elemp		refer�ncia de um objecto do tipo T
 * @return      	refer�ncia do standard output
 */
template <class T>
ostream &operator << (ostream &out, const Dyn2DArray<T> &elemp){
	elemp.write(out);
	return out;
}


#endif /* DYN2DARRAY_H */