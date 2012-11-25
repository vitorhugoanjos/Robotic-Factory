#ifndef GrafoFabrica_
#define GrafoFabrica_

#include "ListAdjGrafo.h"
#include "Posto.h"
#include "Automatico.h"
#include "Armazem.h"
#include "Robot.h"
#include "DstTime.h"
using namespace std;

/*
 * Classe GrafoFabrica permite criar o grafo que simula a fábrica, em que
 * os vértices do grafo serão postos (autmáticos ou armazém) e os ramos
 * são objectos DstTime (que indicam as distâncias e tempos entre cada
 * posto da fábrica)
 * @author João Carreira, Vitor Hugo Santos
 * @version: 5.0 (Nov 2012)
 */
class GrafoFabrica:public ListAdjGrafo<Posto,DstTime>{
public:
	/* protótipos dos métodos de classe */ 
	GrafoFabrica();
	GrafoFabrica(const GrafoFabrica &gf);
	void adicionarPosto(const Posto &p);
	void adicionarDstTime(const DstTime &dt, const Posto &p1, const Posto &p2);

};

/**
 * Construtor sem parâmetros: cria um grafo vazio
 */
GrafoFabrica::GrafoFabrica():ListAdjGrafo<Posto,DstTime>(){
}

/**
 * Construtor cópia: cria uma cópia do grafo
 * @param &gf 	é o endereço de um objecto do tipo GrafoFabrica 	  
 */
GrafoFabrica::GrafoFabrica(const GrafoFabrica &gf):ListAdjGrafo<Posto,DstTime>(gf){
}

/**
 * Adiciona um posto ao grafo, recorrendo ao método juntar_vertice da classe Lista de 
 * adjacências
 * @param &p 	é o endereço de um objecto do tipo posto
 */
void GrafoFabrica::adicionarPosto(const Posto &p){
	this -> juntar_vertice(p);
}

void GrafoFabrica::adicionarDstTime(const DstTime &dt, const Posto &p1, const Posto &p2){
	this -> juntar_ramo(dt, p1, p2);
	this -> juntar_ramo(dt, p2, p1);
}













#endif