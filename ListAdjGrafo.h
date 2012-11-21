#ifndef ListAdjGrafo_
#define ListAdjGrafo_

#include "Vertice.h"
#include "Ramo.h"
#include "Queue.h"
#include "Stack.h"

template<class TV,class TR>
class ListAdjGrafo
{

private:
	int nvertices;
	int nramos;
	Vertice<TV,TR>* graf;
	void visita_profundidade(Vertice<TV,TR>* apinicio, int *vector) const;
	void mostra_Cam(Vertice<TV,TR>* apinicio, Vertice<TV,TR>* apfim, int *vector, Stack<TV> st);
	void mostraCaminho(int origem, int destino, const int *caminho);
	int distanciaMinimoVertice(int *distancia, bool *processado) const;
	void caminhominimoP(Vertice<TV,TR> *inicio, Vertice<TV,TR> *fim);
	void mostracaminhos(Vertice<TV,TR> *apinicio,Vertice<TV,TR> *apfim, int *vector, Stack<TV>s, TR &custo, TR &custlim);
public:
	ListAdjGrafo();
	ListAdjGrafo(const ListAdjGrafo<TV,TR>& G) ;
	~ListAdjGrafo() ; 

	Vertice<TV,TR>* encvert_conteudo(const TV& v) const;
	Vertice<TV,TR>* encvert_key(int numvert) const;

	int NumVert() const ;
	int NumRamos() const ;

	TR MaxConteudoRamo() const ; 

	void juntar_vertice(const TV& vert);
	void juntar_ramo(const TR& rcont, const TV& vorigem, const TV& vdestino);

	int grau_entrada (const TV& vert) const ;
	int grau_saida (const TV& vert) const;

	void escreve_grafo() const ;

	void visita_Largura(const TV& vinicio) const;
	void visita_Prof(const TV& vinicio) const;

	void mostra_caminhos(const TV& vinicio, const TV& vfim);
	void caminhoMinimoPesado(const TV &inicio, const TV &fim);
	int tempovisitatodassalas()const;
	void mostraCaminhosPossiveis(const TV &inicio,const TV &fim);
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

	if (ap)
	{
		ap1=ap->apramo;
		while (ap1)  
		{
			grau++ ;
			ap1=ap1->apr ; 
		}
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
		cout << "Num vertices " << nvertices  << endl ; 
		cout << "Num ramos " << nramos  << endl ; 

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

template<class TV, class TR>
void ListAdjGrafo<TV,TR>::visita_Largura(const TV& vinicio) const
{
	Vertice<TV,TR>* apinicio = encvert_conteudo(vinicio);
	int *vetor=new int [nvertices+1];
	for (int i = 0; i <= nvertices; i++)
	{
		vetor[i]=0;
	}
	if(apinicio!=NULL){
		Queue<Vertice<TV,TR>*> q;
		Ramo<TV,TR> *apramo;
		cout << apinicio->vconteudo;
		vetor[apinicio->key]=1;

		q.insere(apinicio);
		while(!q.vazia())
		{
			q.retira(apinicio);
			apramo=apinicio->apramo;
			while(apramo!=NULL)
			{
				int outrovert=apramo->apv->key;
				if(vetor[outrovert] == 0)
				{
					vetor[outrovert]=1;
					cout << apramo->apv->vconteudo;
					q.insere(apramo->apv);
				}
				apramo=apramo->apr;
			}	
		}
	}else
	{
		cout << "Vertice nao encontrado";
	}
	cout << endl;
}

template<class TV, class TR>
void ListAdjGrafo<TV,TR>::visita_Prof(const TV& vinicio) const
{
	Vertice<TV,TR> *apinicio = encvert_conteudo(vinicio);
	if(apinicio!=NULL)
	{
		int *vector=new int[nvertices+1];
		for (int i = 0; i <= nvertices; i++)
		{
			vector[i]=0;
		}
		visita_profundidade(apinicio, vector);
	}else
		cout << "Vertice nao encontrado";
	cout << endl;
}

template<class TV, class TR>
void ListAdjGrafo<TV,TR>::visita_profundidade(Vertice<TV,TR>* apinicio, int *vector) const
{
	Ramo<TV,TR> *apramo;
	vector[apinicio->key]=1;
	cout << apinicio->vconteudo;
	apramo=apinicio->apramo;
	while(apramo!=NULL)
	{
		int outrovert=apramo->apv->key;
		if(vector[outrovert]==0)
			visita_profundidade(apramo->apv,vector);
		apramo=apramo->apr;
	}
}

template <class TV, class TR>
void ListAdjGrafo<TV,TR>::mostra_caminhos(const TV& vinicio,const TV& vfim)
{
	Vertice<TV,TR> *apinicio = encvert_conteudo(vinicio);
	Vertice<TV,TR> *apfim = encvert_conteudo(vfim);
	if(apinicio!=NULL && apfim!=NULL)
	{
		int *vector=new int[nvertices+1];
		for (int i= 0; i<=nvertices; i++)
			vector[i]=0;
		Stack<TV> st;
		mostra_Cam(apinicio,apfim,vector,st);	
	}else
		cout << "Vertice nao encontrado";
	cout << endl;


}

template<class TV, class TR>
void ListAdjGrafo<TV,TR>::mostra_Cam(Vertice<TV,TR>* apinicio, Vertice<TV,TR>* apfim, int *vector, Stack<TV> st)
{
	vector[apinicio->key]=1;
	st.push(apinicio->vconteudo);
	Ramo<TV,TR> *apramo=apinicio->apramo;
	TV vert;
	while(apramo!=NULL)
	{
		if (apramo->apv->vconteudo == apfim->vconteudo)
		{
			st.push(apramo->apv->vconteudo);
			//inverter
			Stack<TV> aux;
			while(!st.vazia())
			{
				st.pop(vert);
				aux.push(vert);
			}
			cout << aux;
			cout << endl;
			while(!aux.vazia())
			{
				aux.pop(vert);
				st.push(vert);
			}
			st.pop(vert);
		}else if(vector[apramo->apv->key]==0)
			mostra_Cam(apramo->apv,apfim,vector,st);
		apramo=apramo->apr;
	}
	vector[apinicio->key]=0;
	st.pop(vert);
}

template<class TV, class TR>
int ListAdjGrafo<TV,TR>::distanciaMinimoVertice(int *distancia, bool *processado) const 
{
	int minimo=INT_MAX,indvertice=-1;
	for (int i = 1; i < nvertices; i++)
	{
		if(!processado[i]&&distancia[i]<minimo)
		{
			minimo=distancia[i];
			indvertice=i;
		}
	}
	return indvertice;
}

template<class TV, class TR>
void ListAdjGrafo<TV,TR>::mostraCaminho(int origem, int destino, const int *caminho)
{
	if(origem!=destino){
		mostraCaminho(origem,caminho[destino],caminho);
		cout << "--";
	}
	Vertice<TV,TR>* apvert=encvert_key(destino);
	cout << apvert->vconteudo;
}

template<class TV,class TR>
void ListAdjGrafo<TV,TR>::caminhoMinimoPesado(const TV &inicio, const TV &fim)
{
	Vertice<TV,TR>* apvini=encvert_conteudo(inicio);
	Vertice<TV,TR>* apvfim=encvert_conteudo(fim);
	if(apvini==NULL || apvfim==NULL)
		cout << "Vertices nao encontrados" << endl;
	else
	{
		caminhominimoP(apvini, apvfim);	
		cout << endl;
	}
}

template<class TV, class TR>
void ListAdjGrafo<TV,TR>::caminhominimoP(Vertice<TV,TR> *inicio,Vertice<TV,TR> *fim){
	bool *processados=new bool[nvertices+1];
	int *distancia = new int [nvertices+1];
	int *caminho= new int [nvertices+1];
	Vertice<TV,TR> *ini=inicio;
	Vertice<TV,TR> *f=fim;
	for (int i = 1; i <= nvertices;++i)
	{
		processados[i]=false;
		caminho[i]=0;
		distancia[i]=9999;
	}
	int indOrg=inicio->key;
	distancia[inicio->key]=0;
	while(indOrg!=-1){
		processados[indOrg]=true;
		inicio=encvert_key(indOrg);
		Ramo<TV,TR>* apramo=inicio->apramo;
		while(apramo!=NULL){
			int indDest=apramo->apv->key;
			if(!processados[indDest]&&distancia[indDest]>distancia[indOrg]+apramo->rconteudo){
				distancia[indDest]=distancia[indOrg]+apramo->rconteudo;
				caminho[indDest]=indOrg;
			}
			apramo=apramo->apr;
		}
		indOrg=distanciaMinimoVertice(distancia,processados);
	}
	if(distancia[f->key]==9999){
		cout << "nao existe caminho entre " << ini->vconteudo << " e " << f->vconteudo<< endl;
	}else{
		mostraCaminho(ini->key, f->key, caminho);
	}
}

template<class TV,class TR>
int ListAdjGrafo<TV,TR>::tempovisitatodassalas()const
{
	Vertice<TV,TR>	*ap=graf;
	int temptot=0;
	while(ap!=NULL)
	{
		temptot+=ap->vconteudo.getTempo();
		ap=ap->apvertice;	
	}
	return temptot;
}

template<class TV,class TR>
void ListAdjGrafo<TV,TR>::mostracaminhos(Vertice<TV,TR> *apinicio,Vertice<TV,TR> *apfim, int *vector, Stack<TV>s, TR &custo, TR &custlim)
{
	TV nvdest;
	Ramo<TV,TR> *apramo;
	Stack <TV> cam;
	
	if(vector[apinicio->vconteudo.getNum()==0])
		vector[apinicio->vonteudo.getNum()]=1;
	s.push(apinicio->vconteudo.getNum());
	apramo=apinicio->apramo;
	while(apramo!=NULL)
	{
		nvdest=apramo->apv->vonteudo.getNum();
		if(nvdest==apfim->vconteudo.getNum())
		{
			custo+=apfim->vconteudo->getTempo();
			s.push(nvdest);
			if(custo<=custolim
			{
				cam=s;
				cam.inverte();
				cout<<cam<<":"<<custo<<endl;
			}
			s.pop(nvdest);
			custo-=apfim->vconteudo.getTempo();
		}else if(vector[nvdest]==0)
		{
			custo+=apramo->apv->vconteudo.getTempo();
			vector[nvdest]=apramo->apv->vconteudo.getTempo();
			mostracaminhos(apramo->apv,apfim,vector,s,custo,custolim);		
		}
		apramo=apramo->apr;	
	}
	custo-=vector[apinicio->vconteudo.getTempo()];
	vector[apinicio->vconteudo.getNum()]=0;	
}

template<class TV,class TR>
void ListAdjGrafo<TV,TR>::mostraCaminhosPossiveis(const TV &inicio,const TV &fim)
{
	Vertice<TV,TR> *apinicio = encvert_conteudo(

}

#endif