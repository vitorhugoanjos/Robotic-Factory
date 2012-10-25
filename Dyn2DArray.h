 /* Projecto ESINF - 2º ano LEI -ISEP
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
 * Class DYN2DARRAY: permite criar um array bidimensional dinâmico, para objectos de
 * qualquer tipo visto tratar-se basear-se numa função template
 * @author João Carreira, Vitor Hugo Anjos
 * @version: 1.0 (Oct 2012)
 */
template <class T>
class Dyn2DArray{

private:
	/* dimensão do array 2D (nº linhas = nº colunas = cap) */
	int cap;
	/* índice do vector 2D (pode indicar colunas OU linhas) */
	int index;
	/* array 2D */
	T **vec;

public:
	/* protótipos de construtores e destrutor */
	Dyn2DArray();
	Dyn2DArray(int dim);
	~Dyn2DArray();

	/* protótipos de outros métodos */
	void insert(const T &elem);
	void insertRC(const T &elem, int row, int col);
	void write(ostream &out) const;

};


template <class T>
Dyn2DArray<T>::Dyn2DArray(){
	vec = NULL;
	cap = index = 0;
}

/**
 * Construtor com parâmetros: cria um array com dimensão passada por parâmetro
 * @param dim 		é a dimensão do array
 */
template <class T>
Dyn2DArray<T>::Dyn2DArray(int dim){
	cap = dim;
	vec = new T *[cap];
	for(int i = 0; i < cap; i++)
		vec[i] = new T[cap];
	index = 0;
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
* Insere um elemento, passado por parâmetro, no array; altera, se necessário,
* a capacidade do vector; NOTA IMPORTANTE: este método de inserção apenas
* introduz elementos na DIAGONAL PRINCIPAL do array2D, são necessárias
* alterações ou mesmo um método diferente para introduzir elementos num local
* específico da matriz
* @param elem 		é a referência do elemento a introduzir no array
*/
template <class T>
void Dyn2DArray<T>::insert(const T &elem){
	if(cap == 0){
		Dyn2DArray(1);
	}
	/* verifica se array 2D está cheio */
	if(index == cap){
		/* duplica a capacidade do array 2D */
		cap *= 2;
		/* array2D temporário */
		T **newVec = new T *[cap];
		for(int i = 0; i < cap; i++)
			newVec[i] = new T[cap];
		/* copiar para vec temporário */
		for(int i = 0; i < index; i++)
			for(int j = 0; j < index; j++)
				newVec[i][j] = vec[i][j];
		delete [] vec;
		vec = newVec;
	}
	/* introdução do elemento numa dada posição da diagonal principal */
	vec[index][index] = elem;
	index++;
}


/**
* Insere um elemento, passado por parâmetro, no array; altera, se necessário,
* a capacidade do vector; este método permite a inserção de um elemento numa
* posição específica da matriz, logo a função inclui como parâmetros a linha
* e coluna onde introduzir o elemento; notar que este método produz uma matriz
* quadrada, em que um elemento introduzido na posição (a,b) vai ser também
* introduzido na (b,a)
* @param elem 		é a referência do elemento a introduzir no array
* @param row		é o número da linha onde introduzir o elemento
+ @param col 		é o número da coluna onde introduzir o elemento
*/
template <class T>
void Dyn2DArray<T>::insertRC(const T &elem, int row, int col){
	if(cap == 0){
		Dyn2DArray(1);
	}
	/* verifica se array 2D está cheio */
	if(index == cap){
		/* duplica a capacidade do array 2D */
		cap *= 2;
		/* array2D temporário */
		T **newVec = new T *[cap];
		for(int i = 0; i < cap; i++)
			newVec[i] = new T[cap];
		/* copiar para vec temporário */
		for(int i = 0; i < index; i++)
			for(int j = 0; j < index; j++)
				newVec[i][j] = vec[i][j];
		delete [] vec;
		vec = newVec;
	}
	/* introdução do elemento na posição indicada */
	vec[row][col] = elem;
	vec[col][row] = elem;
	/* atribuir o valor máximo de row ou col a index, para controlar o
	tamanho do array dinâmico */
	if(row > col)
		index = row;
	else
		index = col;
	index++;
}


/**
 * Método de escrita, imprime no ecrã toda a informação sobre cada um dos
 * elementos que existem no vector 2D
 * @param out
 */
template <class T>
void Dyn2DArray<T>::write(ostream &out) const {
	for(int i = 0; i < index; i++){
		/* linha seguinte apenas serve para visualizar as linhas da matriz,
		deverá ser comentada ou eliminada no programa final */
		cout << "new line" << endl;
		for(int j = 0; j < index; j++)
			cout << vec[i][j] << endl;
	}
}


/**
 * Sobrecarga do operador de stream out
 * @param out   	referência do standard output
 * @param elemp		referência de um objecto do tipo T
 * @return      	referência do standard output
 */
template <class T>
ostream &operator << (ostream &out, const Dyn2DArray<T> &elemp){
	elemp.write(out);
	return out;
}


#endif /* DYN2DARRAY_H */