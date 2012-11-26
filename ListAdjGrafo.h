#ifndef ListAdjGrafo_
#define ListAdjGrafo_

#include "Vertice.h"
#include "Ramo.h"
#include "Stack.h"

#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
using namespace std;


template<class TV,class TR>
class ListAdjGrafo
{
	
private:
	int nvertices;
	int nramos;
	Vertice<TV,TR>* graf;
	
	void visita_profundidade(Vertice<TV,TR>* apinicio, vector<bool> &vVisitados) const;
	
	//void conta_caminhos (Vertice<TV,TR> *vinicio, Vertice<TV,TR> *vfim, int *vector, int& n) const;
	void Caminho(Vertice<TV,TR>* pInicio, Vertice<TV,TR>* pFim, vector<bool> &vVisitados, stack<TV> &caminho) const;
	bool Caminho(Vertice <TV,TR>*v1,Vertice <TV,TR>*v2) const;
	bool Caminho(Vertice <TV,TR>*v1,Vertice <TV,TR>*v2, int *vec) const;
	
	
public:
	ListAdjGrafo();
	ListAdjGrafo(const ListAdjGrafo<TV,TR>& G);
	~ListAdjGrafo();
	
	Vertice<TV,TR>* encvert_conteudo(const TV& v) const;
	Vertice<TV,TR>* encvert_key(int numvert) const;
	Vertice<TV,TR>* encvert_keyPosto(int numvert) const;
	
	int NumVert() const;
	int NumRamos() const;
	
	TR MaxConteudoRamo() const;
	
	void juntar_vertice(const TV& vert);
	void juntar_ramo(const TR& rcont, const TV& vorigem, const TV& vdestino);
	
	int grau_entrada (const TV& vert) const;
	int grau_saida (const TV& vert) const;
	
	void escreve_grafo() const;
	
	void visita_largura(const TV & vinicio) const;
	void visita_profundidade(const TV& vinicio) const;
	
	void Caminho(const TV& vinicio, const TV& vfim) const;
	bool Conexo() const;
	
	void Escreve_Caminho(vector<TV> path, const TV &vinicio, const TV &vfim) const;
	void Dijkstra(Vertice<TV,TR>* apvinic, Vertice<TV,TR>* apvfim, vector<TV> &antecessor, vector<TR> &distancia) const;
	void Dijkstra(const TV &vinicio, const TV &vfim) const;

	void caminhoSimples(const TV &inicio,const TV &fim);
	void caminhoSimples2(Vertice<TV,TR> *vinicio,Vertice<TV,TR> *vfim, int * vector,Stack<TV> caminho);

	bool caminhoMinimoPesado(const TV &inicio,const TV &fim);
	void mostrarCaminho(int origem,int destino, const int * caminho);
	float distanciaMinimoVertice(float * distancia, bool * processados); 
	bool caminhoMinimoPesadoAut(const TV &inicio,const TV &fim);
	bool caminhoMinimoPesadoArm(const TV &inicio,const TV &fim);
	float tempoMinimoVertice(float * tempo, bool * processados); 

	
};

template<class TV,class TR>
ListAdjGrafo<TV,TR>::ListAdjGrafo()
{
	nvertices=0;
	nramos=0;
	graf=NULL;
}


template<class TV,class TR>
ListAdjGrafo<TV,TR>::ListAdjGrafo(const ListAdjGrafo<TV,TR>& G)
{
	Vertice<TV,TR>* apv=G.graf;
	Vertice<TV,TR>* v;
	Vertice<TV,TR>* ant;
	Ramo<TV,TR>* apr;
	Ramo<TV,TR>* prev;
	Ramo<TV,TR>* r;
	graf=NULL;
	int numvert=0;
	
	while (apv)		//adiciona os vertices
	{
		numvert++;
		Vertice<TV,TR>* vert=new Vertice<TV,TR>(apv->vconteudo,numvert);
		if (graf == NULL)
			graf = vert;
		else
		{
			v = graf;
			while (v) 
			{
				ant = v;
				v = v->apvertice;
			}
			ant->apvertice = vert;
		} 
		apv = apv->apvertice;
	}
	nvertices = G.nvertices;
	
	apv=G.graf;
	while (apv)		 	//adiciona os ramos  
	{
		Vertice<TV,TR>* vorig = encvert_conteudo(apv->vconteudo);
		apr = apv->apramo;		
		while (apr)			 
		{
			Ramo<TV,TR>* ramo = new Ramo<TV,TR>(apr->rconteudo,apr->apv);
			
			if (vorig->apramo == NULL)
				vorig->apramo=ramo;
			else
			{
			  r = vorig->apramo;
			  while (r) 
			  {
					prev = r;
					r = r->apr;
			  }
			  prev->apr = ramo;
			}
			apr = apr->apr;
		} 
		apv = apv->apvertice;
	}
	nramos = G.nramos;
}


template<class TV,class TR>
ListAdjGrafo<TV,TR>::~ListAdjGrafo()
{
	Vertice<TV,TR>* apv=graf;
	Vertice<TV,TR>* tempv;
	Ramo<TV,TR>* tempr;
	Ramo<TV,TR>* temp;
	
	while (apv)
	{
	  tempr = apv->apramo;
	  while (tempr)
	  {
		  temp = tempr;
		  tempr = tempr->apr;
		  delete temp;
	  }
	  tempv = apv;
		apv = apv->apvertice;
	  delete tempv;
	}
	graf = NULL;
	nvertices=0;
	nramos=0;
}

template<class TV,class TR>
int ListAdjGrafo<TV,TR>::NumVert() const
{
	return nvertices;
}

template<class TV,class TR>
int ListAdjGrafo<TV,TR>::NumRamos() const
{
	return nramos;
}

template<class TV,class TR>
TR ListAdjGrafo<TV,TR>::MaxConteudoRamo() const
{
	Vertice<TV,TR>* ap = graf;
	Ramo<TV,TR>* aprmax;
	
	if (ap->apramo) //inicializa com o conteudo do 1º ramo 
	  aprmax = ap->apramo;
	
	while (ap != NULL)
	{
	  if (ap->apramo)   //percorre todos os ramos do vertice 
	  {
			Ramo<TV,TR>* tempr = ap->apramo;
			while (tempr)
			{
				if (tempr->rconteudo > aprmax->rconteudo)
					aprmax = tempr;
				
				tempr = tempr->apr;
			}
	  }
	  ap = ap->apvertice;
	}
	
	return aprmax->rconteudo;
}

template<class TV,class TR>
bool ListAdjGrafo<TV,TR>::Conexo() const
{
	if (graf==NULL) return true;

	Vertice <TV,TR> *v1, *v2;
	v1 = graf;

	while (v1->apvertice != NULL)
	{
		v2 = v1->apvertice;
		while (v2 != NULL)
		{
			if (!Caminho(v1,v2) && !Caminho(v2,v1))
				return false;
			v2 = v2->apvertice;
		}
		v1=v1->apvertice;
	}

	return true;
}

// Método Caminho privado de pesquisa em profundidade recursivo
template<class TV,class TR>
bool ListAdjGrafo<TV,TR>::Caminho(Vertice <TV,TR>*v1,	Vertice <TV,TR>*v2, int *vec) const
{
	vec[v1->key] = 1;
	if (v1==v2) return true;

	Ramo <TV,TR> *ramo = v1->apramo;
	while (ramo !=NULL)
	{
		if ((vec[ramo->apv->key]==0) && Caminho(ramo->apv, v2,vec)) return true;
		ramo = ramo->apr;
	}
	return false;
}

// Método Caminho privado para inicializar o vector (que evita ciclos) em cada chamada ao método de pesquisa em profundidade recursivo
template<class TV,class TR>
bool ListAdjGrafo<TV,TR>::Caminho(Vertice <TV,TR>*v1, Vertice <TV,TR>*v2) const
{
	int *vec = new int[nvertices+1];
	for (int i =1; i <=nvertices; i++) vec[i]=0;
	return Caminho(v1,v2,vec);
}

template<class TV,class TR>
Vertice<TV,TR>* ListAdjGrafo<TV,TR>::encvert_conteudo(const TV& v) const
{
	Vertice<TV,TR>* ap=graf;
	
	while (ap != NULL)
	{
		if (ap->vconteudo == v)
			return ap;
		else 
			ap=ap->apvertice;
	}
	return ap;
}

template<class TV,class TR>
Vertice<TV,TR>* ListAdjGrafo<TV,TR>::encvert_key(int numvert) const
{
	Vertice<TV,TR>* ap=graf;
	
	while (ap != NULL)
	{
		if (ap->key == numvert)
			return ap;
		else 
			ap=ap->apvertice;
	}
	return ap;
}

template<class TV,class TR>
Vertice<TV,TR>* ListAdjGrafo<TV,TR>::encvert_keyPosto(int k ) const{
	Vertice<TV,TR>* ap=graf;
	while(ap!=NULL){
		if(ap->vconteudo->getKey() == k)
			return ap;
		else
			ap=ap->apvertice;
	}
	return ap;
}


template<class TV,class TR>
void ListAdjGrafo<TV,TR>::juntar_vertice(const TV& vert)
{
	if (nvertices == 0)
	{
		nvertices++;
		Vertice<TV,TR>* vertice = new Vertice<TV,TR>(vert,nvertices);
		graf = vertice;
	}
	else
	{
		Vertice<TV,TR>* ap=graf;
		Vertice<TV,TR>* ant=graf;
		bool enc=false;
		
		while (ap != NULL && !enc)
		{
			if (ap->vconteudo == vert)
				enc=true;
			else
			{
				ant = ap;
				ap=ap->apvertice;
			}
		}
		if (!enc) //vertice nao existe
		{
			nvertices++;	
			Vertice<TV,TR>* vertice=new Vertice<TV,TR>(vert,nvertices);
			ant->apvertice = vertice;
		}
	}
}



template<class TV,class TR>
void ListAdjGrafo<TV,TR>::juntar_ramo(const TR& rcont, const TV& vorig, const TV& vdest)
{
	Ramo<TV,TR>* tempramo=NULL;
	Ramo<TV,TR>* ant;
	Vertice<TV,TR>* vertorig;
	Vertice<TV,TR>* vertdest=NULL;
 	
	vertorig=encvert_conteudo(vorig);
	if (vertorig == NULL)
	{
		juntar_vertice(vorig);
		vertorig=encvert_conteudo(vorig);
	}
	vertdest=encvert_conteudo(vdest);
	if (vertdest == NULL)
	{
		juntar_vertice(vdest);
		vertdest=encvert_conteudo(vdest);
	}
	
	tempramo=vertorig->apramo;			//insere no fim da lista de ramos
	ant = tempramo;
	while (tempramo != NULL)
	{
		ant = tempramo;
		tempramo=tempramo->apr;
	}
	if (tempramo == NULL)							 
	{
		tempramo = new Ramo<TV,TR>(rcont,vertdest);
		tempramo->apr= NULL;
		if (ant)
		  ant->apr = tempramo;
		else
			vertorig->apramo = tempramo;
 		
		nramos++;
	}
}



template<class TV,class TR>
int ListAdjGrafo<TV,TR>::grau_entrada (const TV& vert) const 
{
	int grau = 0;
	Vertice<TV,TR>* ap=graf;
	Ramo<TV,TR>* ap1;
	
 	while(ap)
	{
		ap1=ap->apramo;
		while(ap1)
		{
			if (vert == ap1->apv->vconteudo) 
			  grau++;
			
			ap1=ap1->apr;
		}
		ap=ap->apvertice;
	}
	return grau;
}


template<class TV,class TR>
int ListAdjGrafo<TV,TR>::grau_saida (const TV& vert) const
{
	Vertice<TV,TR>* ap=encvert_conteudo(vert);
	Ramo<TV,TR>* ap1;
	int grau = 0;
	
	if (ap)
	{
		ap1=ap->apramo;
		while (ap1)  
		{
			grau++;
			ap1=ap1->apr;
		}
	}
	return grau;
}


template<class TV,class TR>
void ListAdjGrafo<TV,TR>::escreve_grafo() const 
{
Vertice<TV,TR>* v=graf;
Vertice<TV,TR>* temp = graf;
Ramo<TV,TR>* r ;
Ramo<TV,TR>* r_temp;

if (v == NULL)
 cout << "Grafo nao definido !" << endl ; 
else
{
 cout << "\nNumero de vertices: " << nvertices  << endl ; 
 cout << "Numero de ramos " << nramos << "\n"  << endl ; 

 while(v) 
 {
  r_temp= v->apramo;
  if(r_temp != NULL){
   temp = r_temp->apv->apvertice;
   if(temp!= NULL)
    cout << "O posto " << v->vconteudo->getKey() << " liga-se ao(s) posto(s):\n";
  }/*else{
    cout << "O posto " << v->vconteudo->getKey() << " nao tem ligacao a nenhum posto\n";
  }*/
  r=v->apramo;
  while (r)
  {
   r_temp = r->apr;
   // cout << "\n";
   cout << r->apv->vconteudo->getKey();
   cout <<" --> Distancia(m)/tempo(min): "<< r->rconteudo;
   /*if(r_temp)
    cout << ", ";
   else
    cout << "." << endl;*/
   r=r->apr;
  }   
  cout<<endl;
  v=v->apvertice;
 }
}
}



template<class TV,class TR>
void ListAdjGrafo<TV,TR>::visita_largura (const TV & vinicio) const
{
	Vertice<TV, TR> *pInicio = encvert_conteudo(vinicio);
	
	cout << "VISITA EM LARGURA:\n";
	
	if (pInicio == NULL) {
		return;
	}
	
	vector<bool> vVisitados(nvertices+1, false);
	
	queue<Vertice<TV, TR> *> qProcessar;
	
	
	qProcessar.push(pInicio);
	vVisitados[pInicio->key] = true;
	
	while (!qProcessar.empty()) {
		Vertice<TV,TR> *pVertice;
		
		pVertice= qProcessar.front();
		qProcessar.pop();
		
		cout << pVertice->vconteudo << endl;
		
		Ramo<TV,TR> *pRamo = pVertice->apramo;
		
		while (pRamo != NULL) {
			if (vVisitados[pRamo->apv->key] == false) {
				qProcessar.push(pRamo->apv);
				vVisitados[pRamo->apv->key] = true;
			}
			pRamo = pRamo->apr;
		}
	}
}


template<class TV,class TR>
void ListAdjGrafo<TV,TR>::visita_profundidade(const TV& vinicio) const
{
	cout << "VISITA EM PROFUNDIDADE:\n";
	
	Vertice<TV, TR> *pInicio = encvert_conteudo(vinicio);
	
	if (pInicio != NULL) {
		vector<bool> vVisitados(nvertices+1, false);
		
		visita_profundidade(pInicio, vVisitados);
	}
	
}


template<class TV,class TR>
void ListAdjGrafo<TV,TR>::visita_profundidade(Vertice<TV,TR>* apinicio, vector<bool> &vVisitados) const
{
	vVisitados[apinicio->key] = 1;
	
	cout << apinicio->vconteudo << endl;
		
	Ramo<TV,TR> *pRamo = apinicio->apramo;
	
	while (pRamo != NULL) {
		if (vVisitados[pRamo->apv->key] == 0) {
			visita_profundidade(pRamo->apv, vVisitados);
		}
		pRamo = pRamo->apr;
	}
}



//void conta_caminhos (Vertice<TV,TR> *vinicio, Vertice<TV,TR> *vfim, int *vector, int& n) const;

template<class TV,class TR>
void ListAdjGrafo<TV,TR>::Caminho(Vertice<TV,TR> *pInicio,
																	Vertice<TV,TR> *pFim,
																	vector<bool> &vVisitados,
																	stack<TV> &sCaminho) const
{
	vVisitados[pInicio->key] = true;
	
	sCaminho.push(pInicio->vconteudo);
	
	Ramo<TV,TR> * pRamo = pInicio->apramo;
	
	while (pRamo != NULL)
	{
		if (pRamo->apv->vconteudo == pFim->vconteudo)
		{
			// Mostrar o caminho
			sCaminho.push(pRamo->apv->vconteudo);
			
			cout << "Caminho simples encontrado:\n";
			stack<TV> sCaminhoCopia = sCaminho;
			stack<TV> sAuxiliar;
			while (!sCaminhoCopia.empty()) {
				sAuxiliar.push(sCaminhoCopia.top());
				sCaminhoCopia.pop();
			}
			
			while (!sAuxiliar.empty()) {
				cout << sAuxiliar.top() << endl;
				sAuxiliar.pop();
			}
			
			sCaminho.pop();
		}
		else
			if (vVisitados[pRamo->apv->key] == false)
				Caminho(pRamo->apv, pFim, vVisitados, sCaminho);
		
		// Seguir para o próximo vértice adjacente
		pRamo = pRamo->apr;
	}
	
	sCaminho.pop();
	vVisitados[pInicio->key] = false;
}



template<class TV,class TR>
void ListAdjGrafo<TV,TR>::Caminho(const TV& vinicio, const TV& vfim) const
{
	Vertice<TV,TR> *pInicio, *pFim;
	
	pInicio = encvert_conteudo(vinicio);
	pFim = encvert_conteudo(vfim);
	
	if (pInicio == NULL || pFim == NULL)
	{
		cout << "[ERRO] TODOS OS CAMINHOS: pelo menos um dos vértices não existe!\n\n";
		return;
	}
	
	vector<bool> vVisitados(nvertices+1, false);
		
	stack<TV> sCaminho;
	
	Caminho(pInicio, pFim, vVisitados, sCaminho);
}


//bool Conexo() const;


template<class TV,class TR>
void ListAdjGrafo<TV,TR>::Escreve_Caminho(vector<TV> path,
																					const TV &vinicio,
																					const TV &vfim) const
{
	// Estabelecer o caminho mínimo entre os dois vértices, a partir do destino.
	// Verifica-se primeiro se o vértice final é alcançavel a partir do vertice
	// inicial.
	
	Vertice<TV,TR> *pInicio, *pFim;
	
	pInicio = encvert_conteudo(vinicio);
	pFim = encvert_conteudo(vfim);
	
	if (pInicio == NULL || pFim == NULL)
	{
		cout << "[ERRO] ESCREVE CAMINHO: Pelo menos um dos vértices não existe!!\n\n";
		return;
	}
	
	
	Vertice<TV,TR> * pAnterior = encvert_conteudo(path[pFim->key]);
	
	if (pAnterior != NULL)
	{
		int keyActual = pFim->key;
		stack<TV> sCaminho;
		
		sCaminho.push(pFim->vconteudo);
		
		while (pAnterior != NULL) {
			sCaminho.push(pAnterior->vconteudo);
			keyActual = pAnterior->key;
			pAnterior = encvert_conteudo(path[keyActual]);
		}
		
		cout << "Caminho mínimo pesado (Dijkstra):\n";		
		// Escreve o caminho mínimo (primeiro->último).
		while (!sCaminho.empty())
		{
			cout << sCaminho.top() << endl;
			sCaminho.pop();
		}
	}
	else {
		cout << "Não existe um caminho possível entre os dois vértices!\n";
	}
}


template<class TV,class TR>
void ListAdjGrafo<TV,TR>::Dijkstra(Vertice<TV,TR>* pInicio,
																	 Vertice<TV,TR>* pFim,
																	 vector<TV> &antecessor,
																	 vector<TR> &distancia) const
{
	if (pInicio == NULL || pFim == NULL)
	{
		cout << "[ERRO] DIJKSTRA: Pelo menos um dos vértices não existe!!\n\n";
		return;
	}
	
	vector<bool> distanciaValida(nvertices+1, false);
	vector<bool> processado(nvertices+1, false);
	
	// Garantir que os vectores recebidos têm as características necessárias para
	// a execução do algoritmo do Dijkstra!
	distancia = vector<TR>(nvertices+1);
	antecessor = vector<TV>(nvertices+1);
	
	
	distancia[pInicio->key] = 0;  // PERIGO!!!
	distanciaValida[pInicio->key] = true;
	
	Vertice<TV,TR> * pActual = pInicio;
	
	// Enquanto houver vértices alcançáveis...
	while(pActual != NULL)
	{
		processado[pActual->key] = true;  // Vértice processado.
		
		Ramo<TV,TR> * pRamo = pActual->apramo;
		
		// Enquanto houver vértices adjacentes...
		while(pRamo != NULL)
		{
			// Se o vértice ainda não tiver sido considerado processado...
			if (processado[pRamo->apv->key] == false)
			{
				if (distanciaValida[pRamo->apv->key] == false ||
						distancia[pRamo->apv->key] > distancia[pActual->key]+pRamo->rconteudo)
				{
					distancia[pRamo->apv->key] = distancia[pActual->key] + pRamo->rconteudo;
					distanciaValida[pRamo->apv->key] = true;
					antecessor[pRamo->apv->key] = pActual->vconteudo;
				}
			}
			// Para o próximo ramo adjacente.
			pRamo = pRamo->apr;
		}
		
		// Qual o nó por processar com menor distância à origem?
		int imin = 0;
		for(int i = 1; i <= nvertices; i++)
		{
			if (processado[i] == false && distanciaValida[i] == true)
				if (imin == 0 || distancia[i] < distancia[imin])
				{
					imin = i;
				}
		}
		
		// Segue a partir do vértice mais próximo da origem, por processar.
		pActual = encvert_key(imin);
		
	}
	
	// Já se visitaram todos os vértices alcançáveis...
	
	// NOTA: NESTE MOMENTO OS VECTORES antecessor[] E distancia[] JÁ CONTÊM AS
	//       DISTÂNCIAS MÍNIMAS DA ORIGEM A QUALQUER VÉRTICE ALCANÇÁVEL E OS
	//       CAMINHOS RELATIVOS A ESSAS DISTÃNCIAS MÍNIMAS!
	
	Escreve_Caminho(antecessor, pInicio->vconteudo, pFim->vconteudo);
	
	
	
}

// Método de pesquisa do caminho mínimo pesado (Dijkstra).
template<class TV,class TR>
void ListAdjGrafo<TV,TR>::Dijkstra(const TV &vinicio, const TV &vfim) const
{
	Vertice<TV,TR> *pInicio, *pFim;
	
	pInicio = encvert_conteudo(vinicio);
	pFim = encvert_conteudo(vfim);
	
	if (pInicio == NULL || pFim == NULL)
	{
		cout << "[ERRO] DIJKSTRA: Pelo menos um dos vértices não existe!!\n\n";
		return;
	}
	
	vector<TR> distancia(nvertices+1);
	
	vector<TV> antecessor(nvertices+1, pInicio->vconteudo);
	
	Dijkstra(pInicio, pFim, antecessor, distancia);
}


/* Caminhos simples entre 2 vértices (AMD) */
template<class TV,class TR>
void ListAdjGrafo<TV,TR>::caminhoSimples(const TV &inicio,const TV &fim)
{
       Vertice<TV,TR> *vinicio=encvert_conteudo(inicio);
       Vertice<TV,TR> *vfim=encvert_conteudo(fim);
       int *vector=new int[nvertices+1];
       for (int i=1; i<=nvertices; i++)        vector[i]=0;
       Stack<TV> caminho;
       if(vinicio!=NULL && vfim!=NULL){
             caminhoSimples(vinicio,vfim,vector,caminho);
	   }
}


template<class TV,class TR>
void ListAdjGrafo<TV,TR>::caminhoSimples2(Vertice<TV,TR> *vinicio, Vertice<TV,TR> *vfim, int *vector, Stack<TV> caminho)
{      TV vert;
		vector[vinicio->GetKey()]=1;
       caminho.push(vinicio->vconteudo);
       Ramo<TV,TR> *apramo=vinicio->apramo;
             while(apramo!=NULL)
             {
                    if(apramo->apv->vconteudo==vfim->vconteudo)
                    {
                           caminho.push(apramo->apv->vconteudo);
                           cout<<endl<<"Percurso tomado pelo robot:"<<endl;
                           caminho.inverte();
                           //cout << caminho<<endl;    
                           caminho.pop(vert);
                    }else
                    {
                           if(vector[apramo->apv->key==0])
                           caminhoSimples2(apramo->apv,vfim,vector,caminho);
                    }
                           apramo=apramo->apr;
             }
			 vector[vinicio->GetKey()]=0;
       caminho.pop(vert);
}


//- Caminho minimo Pesado - Algoritmo Pesado Dijkstra --- para as distancias

template<class TV,class TR>
bool ListAdjGrafo<TV,TR>::caminhoMinimoPesado(const TV &inicio,const TV &fim)
{   float somadist=0;
bool *processados=new bool[nvertices+1];
int *caminho=new int[nvertices+1];
float *distancia=new float[nvertices+1];
for (int i=1; i<=nvertices; i++)
{      processados[i]=false;
caminho[i]=0;
distancia[i]=9999;
}
Vertice<TV,TR> *apvert=encvert_conteudo(inicio);
Vertice<TV,TR> *apvertfim=encvert_conteudo(fim);
if(apvert==NULL || apvertfim==NULL)
	return false;
int indOrigem=apvert->key;
distancia[apvert->key]=0;
//Este algoritmo calcula o caminho mínimo entre o vertice inicio e todos os outros
while(indOrigem!=-1)
{     
	processados[indOrigem]=true;
	apvert=encvert_key(indOrigem);
	Ramo<TV,TR> *apramo=apvert->apramo;           
	while(apramo!=NULL)
	{
		int indDestino=apramo->apv->key;
		if(!processados[indDestino] && distancia[indDestino] > distancia[indOrigem] + apramo->rconteudo->getDist())
		{
			distancia[indDestino]=distancia[indOrigem]+apramo->rconteudo->getDist();
			caminho[indDestino]=indOrigem;
		}
		apramo=apramo->apr;
	}
	indOrigem=distanciaMinimoVertice(distancia,processados);
}
apvert=encvert_conteudo(inicio);
apvertfim=encvert_conteudo(fim);
mostrarCaminho(apvert->key,apvertfim->key,caminho);
return true;
}


template<class TV,class TR>
void ListAdjGrafo<TV,TR>::mostrarCaminho(int origem,int destino, const int * caminho)
{
	if(origem!=destino)
	{     
		mostrarCaminho(origem,caminho[destino],caminho);
	
	}
	Vertice<TV,TR> *apvert=encvert_key(destino);
	cout << apvert-> vconteudo -> getKey() << "  ";

}

template<class TV,class TR>
float ListAdjGrafo<TV,TR>::distanciaMinimoVertice(float * distancia, bool * processados) 
{
	int minimo=INT_MAX, indVertice=-1;
	for(int i=1; i<=nvertices; i++)
		if(!processados[i] && distancia[i]<minimo)
		{
			minimo=distancia[i];
			indVertice=i;
		}
		return indVertice;
}

//- Caminho minimo Pesado - Algoritmo Pesado Dijkstra --- para as distancias
template<class TV,class TR>
bool ListAdjGrafo<TV,TR>::caminhoMinimoPesadoAut(const TV &inicio,const TV &fim)
{   float somadist=0;
bool *processados=new bool[nvertices+1];
int *caminho=new int[nvertices+1];
float *tempo=new float[nvertices+1];
for (int i=1; i<=nvertices; i++)
{      processados[i]=false;
caminho[i]=0;
tempo[i]=9999;
}
Vertice<TV,TR> *apvert=encvert_conteudo(inicio);
Vertice<TV,TR> *apvertfim=encvert_conteudo(fim);
if(apvert==NULL || apvertfim==NULL)
	return false;
int indOrigem=apvert->key;
tempo[apvert->key]=0;

//Este algoritmo calcula o caminho mínimo entre o vertice inicio e todos os outros
while(indOrigem!=-1)
{     
	processados[indOrigem]=true;
	apvert=encvert_key(indOrigem);
	Ramo<TV,TR> *apramo=apvert->apramo;           
	while(apramo!=NULL)
	{
		int indDestino=apramo->apv->key;
		if(!processados[indDestino] && tempo[indDestino] > tempo[indOrigem] + apramo->rconteudo.getTime())
		{
			tempo[indDestino]=tempo[indOrigem]+apramo->rconteudo.getTime();
			caminho[indDestino]=indOrigem;
		}
		apramo=apramo->apr;
	}
	indOrigem=tempoMinimoVertice(tempo,processados);
}
apvert=encvert_conteudo(inicio);
apvertfim=encvert_conteudo(fim);
mostrarCaminho(apvert->key,apvertfim->key,caminho);
return true;
}

//- Caminho minimo Pesado - Algoritmo Pesado Dijkstra --- para as distancias
template<class TV,class TR>
bool ListAdjGrafo<TV,TR>::caminhoMinimoPesadoArm(const TV &inicio,const TV &fim)
{   float somadist=0;
bool *processados=new bool[nvertices+1];
int *caminho=new int[nvertices+1];
float *tempo=new float[nvertices+1];
for (int i=1; i<=nvertices; i++)
{      processados[i]=false;
caminho[i]=0;
tempo[i]=9999;
}
Vertice<TV,TR> *apvert=encvert_conteudo(inicio);
Vertice<TV,TR> *apvertfim=encvert_conteudo(fim);
if(apvert==NULL || apvertfim==NULL)
	return false;
int indOrigem=apvert->key;
tempo[apvert->key]=0;

//Este algoritmo calcula o caminho mínimo entre o vertice inicio e todos os outros
while(indOrigem!=-1)
{     
	processados[indOrigem]=true;
	apvert=encvert_key(indOrigem);
	Ramo<TV,TR> *apramo=apvert->apramo;           
	while(apramo!=NULL)
	{
		int indDestino=apramo->apv->key;
		if(!processados[indDestino] && tempo[indDestino] > tempo[indOrigem] + apramo->rconteudo.getDst())
		{
			tempo[indDestino]=tempo[indOrigem]+apramo->rconteudo.getDst();
			caminho[indDestino]=indOrigem;
		}
		apramo=apramo->apr;
	}
	indOrigem=tempoMinimoVertice(tempo,processados);
}
apvert=encvert_conteudo(inicio);
apvertfim=encvert_conteudo(fim);
mostrarCaminho(apvert->key,apvertfim->key,caminho);
return true;
}



template<class TV,class TR>
float ListAdjGrafo<TV,TR>::tempoMinimoVertice(float * tempo, bool * processados) 
{
	int minimo=INT_MAX, indVertice=-1;
	for(int i=1; i<=nvertices; i++)
		if(!processados[i] && tempo[i]<minimo)
		{
			minimo=tempo[i];
			indVertice=i;
		}
		return indVertice;
}





#endif