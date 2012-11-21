#ifndef ListAdjGrafo_
#define ListAdjGrafo_

#include "Vertice.h"
#include "Ramo.h"


template<class TV,class TR>
class ListAdjGrafo
{

private:
	int nvertices;
	int nramos;
	Vertice<TV,TR>* graf;

	bool Caminho(Vertice <TV,TR>*v1,Vertice <TV,TR>*v2) const;
	bool Caminho(Vertice <TV,TR>*v1,Vertice <TV,TR>*v2, int *vec) const;
public:
	ListAdjGrafo();
	ListAdjGrafo(const ListAdjGrafo<TV,TR>& G) ;
	~ListAdjGrafo() ; 

	Vertice<TV,TR>* encvert_conteudo(const TV& v) const;
	Vertice<TV,TR>* encvert_key(int numvert) const;
	Vertice<TV,TR>* encvert_keyPosto(int k) const;

	int NumVert() const ;
	int NumRamos() const ;

	TR MaxConteudoRamo() const ; 

	void juntar_vertice(const TV& vert);
	void juntar_ramo(const TR& rcont, const TV& vorigem, const TV& vdestino);

	int grau_entrada (const TV& vert) const ;
	int grau_saida (const TV& vert) const;

	void escreve_grafo() const ;

	bool Caminho(const TV &v1,const TV &v2) const;
	bool Conexo() const;
};



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



// Método existeCaminho público, recebe os vértices em TV, converte-os em apontadores de vertice e chama o método privado
template<class TV,class TR>
bool ListAdjGrafo<TV,TR>::Caminho(const TV &v1,const TV &v2) const
{
	Vertice <TV,TR> *apv1, *apv2;
	apv1 = encvert_conteudo(v1);
	apv2 = encvert_conteudo(v2);

	return Caminho(apv1,apv2);
}


// Método conexo, gera todos os pares de vértices e aplica a definição de conexidade
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
	Vertice<TV,TR>* apv=G.graf ;
	Vertice<TV,TR>* v ; 
	Vertice<TV,TR>* ant ; 
	Ramo<TV,TR>* apr;
	Ramo<TV,TR>* prev ;
	Ramo<TV,TR>* r ;
	graf=NULL;
	int numvert=0;

	while (apv)		//adiciona os vertices
	{
		numvert++ ;
		Vertice<TV,TR>* vert=new Vertice<TV,TR>(apv->vconteudo,numvert); 
		if (graf == NULL)
			graf = vert ;
		else
		{
			v = graf ;
			while (v) 
			{
				ant = v ;
				v = v->apvertice ;
			}
			ant->apvertice = vert ;
		} 
		apv = apv->apvertice ; 
	}
	nvertices = G.nvertices ;

	apv=G.graf;
	while (apv)		 	//adiciona os ramos  
	{
		Vertice<TV,TR>* vorig = encvert_conteudo(apv->vconteudo) ;
		apr = apv->apramo ;		
		while (apr)			 
		{
			Ramo<TV,TR>* ramo = new Ramo<TV,TR>(apr->rconteudo,apr->apv);

			if (vorig->apramo == NULL)
				vorig->apramo=ramo ;
			else
			{
				r = vorig->apramo ;
				while (r) 
				{
					prev = r ;
					r = r->apr ;
				}
				prev->apr = ramo ; 
			}
			apr = apr->apr ;
		} 
		apv = apv->apvertice ; 
	}
	nramos = G.nramos ;
}


template<class TV,class TR>
ListAdjGrafo<TV,TR>::~ListAdjGrafo()
{
	Vertice<TV,TR>* apv=graf;
	Vertice<TV,TR>* tempv ; 
	Ramo<TV,TR>* tempr ;
	Ramo<TV,TR>* temp ;

	while (apv)
	{
		tempr = apv->apramo ; 
		while (tempr)
		{
			temp = tempr ; 
			tempr = tempr->apr ;
			delete temp ; 
		}
		tempv = apv ; 
		apv = apv->apvertice ;
		delete tempv ; 
	}
	graf = NULL ;
	nvertices=0 ;
	nramos=0;
}

template<class TV,class TR>
int ListAdjGrafo<TV,TR>::NumVert() const
{
	return nvertices ;
}

template<class TV,class TR>
int ListAdjGrafo<TV,TR>::NumRamos() const
{
	return nramos ;
}

template<class TV,class TR>
TR ListAdjGrafo<TV,TR>::MaxConteudoRamo() const
{
	Vertice<TV,TR>* ap = graf ; 
	Ramo<TV,TR>* aprmax ; 

	if (ap->apramo) //inicializa com o conteudo do 1º ramo 
		aprmax = ap->apramo ; 

	while (ap != NULL)
	{
		if (ap->apramo)   //percorre todos os ramos do vertice 
		{
			Ramo<TV,TR>* tempr = ap->apramo ; 
			while (tempr)
			{
				if (tempr->rconteudo > aprmax->rconteudo)
					aprmax = tempr ; 

				tempr = tempr->apr ; 
			}
		}
		ap = ap->apvertice ; 
	}

	return aprmax->rconteudo ;
}

template<class TV,class TR>
Vertice<TV,TR>* ListAdjGrafo<TV,TR>::encvert_conteudo(const TV& v) const
{
	Vertice<TV,TR>* ap=graf;

	while (ap != NULL)
	{
		if (ap->vconteudo == v)
			return ap ;
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
			return ap ;
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
		Vertice<TV,TR>* ap=graf ;
		Vertice<TV,TR>* ant=graf ;
		bool enc=false ; 

		while (ap != NULL && !enc)
		{
			if (ap->vconteudo == vert)
				enc=true ;
			else
			{
				ant = ap ; 
				ap=ap->apvertice;
			}
		}
		if (!enc) //vertice nao existe
		{
			nvertices++;	
			Vertice<TV,TR>* vertice=new Vertice<TV,TR>(vert,nvertices);
			ant->apvertice = vertice ;
		}
	}
}



template<class TV,class TR>
void ListAdjGrafo<TV,TR>::juntar_ramo(const TR& rcont, const TV& vorig, const TV& vdest)
{
	Ramo<TV,TR>* tempramo=NULL ; 
	Ramo<TV,TR>* ant;
	Vertice<TV,TR>* vertorig ;
	Vertice<TV,TR>* vertdest=NULL;

	vertorig=encvert_conteudo(vorig);
	if (vertorig == NULL)
	{
		juntar_vertice(vorig) ;
		vertorig=encvert_conteudo(vorig);
	}
	vertdest=encvert_conteudo(vdest);
	if (vertdest == NULL)
	{
		juntar_vertice(vdest) ;
		vertdest=encvert_conteudo(vdest);
	}

	tempramo=vertorig->apramo;			//insere no fim da lista de ramos
	ant = tempramo ; 
	while (tempramo != NULL)
	{
		ant = tempramo ; 
		tempramo=tempramo->apr ; 
	}
	if (tempramo == NULL)							 
	{
		tempramo = new Ramo<TV,TR>(rcont,vertdest);
		tempramo->apr= NULL ;
		if (ant)
			ant->apr = tempramo ;
		else
			vertorig->apramo = tempramo ; 

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
				grau++ ;

			ap1=ap1->apr ; 
		}
		ap=ap->apvertice ;
	}
	return grau ;
}


template<class TV,class TR>
int ListAdjGrafo<TV,TR>::grau_saida (const TV& vert) const
{
	Vertice<TV,TR>* ap=encvert_conteudo(vert) ;
	Ramo<TV,TR>* ap1;
	int grau = 0 ;

	if (ap->vconteudo == vert)
	{
		ap1=ap->apramo;
		while (ap1)  
		{
			grau++ ;
			ap1=ap1->apr ; 
		}
		ap=ap->apvertice ;
	}
	return grau ;
}

template<class TV,class TR>
void ListAdjGrafo<TV,TR>::escreve_grafo() const 
{
	Vertice<TV,TR>* v=graf;
	Ramo<TV,TR>* r ;

	if (v == NULL)
		cout << "Grafo nao definido !" << endl ; 
	else
	{
		cout << "Numero de vertices: " << nvertices  << endl ; 
		cout << "Numero de ramos " << nramos  << endl ; 

		while (v != NULL)
		{
			cout << "O vertice " << v->vconteudo << " liga-se a: " << endl;
			r=v->apramo;
			while (r)
			{
				cout << r->apv->vconteudo << "  " ;
				cout <<" Conteudo -> "<< r->rconteudo << endl;	
				r=r->apr;
			}   
			cout<<endl;
			v=v->apvertice;
		}
	}
}



#endif