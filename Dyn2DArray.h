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
 * @version: 2.0 (Oct 2012)
 */
template <class T>
class Dyn2DArray{

private:
	/* dimensão do array 2D (nº linhas = nº colunas = cap) */
	int cap;
	/* índice do vector 2D (pode indicar colunas OU linhas) */
	int maxRC;
	/* array 2D */
	T **vec;

public:
	/* protótipos de construtores e destrutor */
	Dyn2DArray();
	Dyn2DArray(int dim);
	Dyn2DArray(const Dyn2DArray &d);
	~Dyn2DArray();

	/* protótpos de GETS */
	int getCap();
	T getVec(){
		return vec;
	}

	/* protótipos de outros métodos */
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
 * Construtor sem parâmetros: cria um array 2D com dimensão "default" de 2*2
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
 * Construtor com parâmetros: cria um array 2D com dimensão n*n, em que n
 * é passado por parâmetro
 * @param dim 	dimensão a atribuir ao array 2D
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
 * Construtor cópia
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
 * Método público de acesso à capacidade do array2D
 * return	capacidade de array2D (ou seja, o nº máximo de linhas e
 *			colunas que possui) */
template <class T>
int Dyn2DArray<T>::getCap(){
	return cap;
}


/**
* Insere um elemento, passado por parâmetro, no array; altera, se necessário,
* a capacidade do vector; este método permite a inserção de um elemento numa
* posição específica da matriz, logo a função inclui como parâmetros a linha
* e coluna onde introduzir o elemento; notar que este método produz uma matriz
* quadrada, em que um elemento introduzido na posição (a,b) vai ser também
* introduzido na (b,a); caso já exista um elemento diferente do tipo não
* inicializado na posição (a,b) ou (b,a) da matriz não ocorre introdução desse
* elemento
* @param elem 		é a referência do elemento a introduzir no array
* @param row		é o número da linha onde introduzir o elemento
* @param col 		é o número da coluna onde introduzir o elemento
* @return 			true, caso inserção do elemento seja bem sucedida; false,
					no caso contrário
*/
template <class T>
bool Dyn2DArray<T>::insert(const T &elem, int row, int col){
	/* verifica o máximo entre row e col e atribui esse máximo a maxTemp */
	int maxTemp;
	if(row > col)
		maxTemp = row;
	else
		maxTemp = col;
	/* verifica se array 2D tem capacidade para guardar novo elemento, com
	base no maxTemp */
	if(maxTemp > cap){
		/* guarda capacidade anterior do vector (para ser usado no momento
		da cópia */
		int prevCap = cap;
		/* nova capacidade do array passa a ser maxTemp+1 */
		cap = maxTemp + 1;
		/* array2D temporário com dimensão actualizada */
		T **newVec = new T *[cap];
		for(int i = 0; i < cap; i++)
			newVec[i] = new T[cap];
		/* copiar array 2D para array 2D temporário */
		for(int i = 0; i < prevCap; i++)
			for(int j = 0; j < prevCap; j++)
				newVec[i][j] = vec[i][j];
		/* libertar recursos do array copiado */
		for(int i = 0; i < prevCap; i++)
			delete [] vec[i];
		delete [] vec;
		/* atribuir array temporário a vec */
		vec = newVec;
	}
	/* introdução do elemento na posição indicada (originando um array 2D
	simétrico relativamente à diagonal principal) */
	/* apontator para new T, necessário para comparação com tipos não inicializados */
	T *blank = new T;
	/* se elemento na posição [row][col] for igual a um tipo não inicializado, então
	pode-se introduzir o elemento */
	if((vec[row][col] == *blank) || (vec[col][row] == *blank)){
		vec[row][col] = elem;
		vec[col][row] = elem;
		/* retorna true indiciado que inserção foi bem sucedida*/
		return true;
	}
	else
		/* retorna false para indicar inserção não foi bem sucedida*/
		return false;

}


/**
 * Método de escrita, imprime no ecrã toda a informação sobre cada um dos
 * elementos que existem no vector 2D; como o array 2D representa uma matriz
 * simétrica apenas é mostrado no ecrã os elementos da parte superior (incluindo
 * a diagonal principal)
 * @param out
 */
template <class T>
void Dyn2DArray<T>::write(ostream &out) const {
	/* apontator para new T, necessário para comparação com tipos não inicializados */
	T *blank = new T;
	for(int i = 0; i < cap; i++){
		/* linha seguinte apenas serve para visualizar as linhas da matriz,
		deverá ser comentada ou eliminada no programa final */
		// cout << "****Linha " << i << "*****" << endl;
		/* com j=i garante-se que apenas são mostrados os elementos a partir
		da diagonal principal em diante; para mostrar a matriz 2D inteira basta
		substituir j=i por j=0 */
		for(int j = i; j < cap; j++)
			/* apenas imprime o elemento do array2D se fôr diferente de um tipo não
			inicializado */
			if(vec[i][j] != *blank){
				cout << "Distancia do posto " << i << " ao posto " << j << endl;
				cout << vec[i][j] << endl;
			}
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