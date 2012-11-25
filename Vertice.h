#ifndef Vertice_
#define Vertice_

template<class TV,class TR>
class ListAdjGrafo;

template<class TV,class TR>
class Ramo;

template<class TV, class TR>	//Classe dos vertices do grafo
class Vertice
{
	friend class ListAdjGrafo<TV, TR>;
 
	private:
		TV vconteudo;
		int key ;
		Vertice<TV,TR>* apvertice;
		Ramo<TV,TR>* apramo;

	public:
		Vertice();
		Vertice(const TV& conteudo, int k);
		Vertice(const Vertice<TV,TR>& v);
		~Vertice();

		TV GetConteudo() const ;
		int GetKey() const ;
		Vertice<TV,TR>* GetVertice() const ;
		Ramo<TV,TR>* GetRamo() const ;

		void SetConteudo(const TV& conteudo) ;
		void SetKey(int k) ; 
		void SetVertice(const Vertice<TV,TR>* v) ;
		void SetRamo(const Ramo<TV,TR>* r) ; 

};

template<class TV,class TR>
Vertice<TV,TR>::Vertice()
{
	key = 0 ;
	apvertice=NULL;
	apramo=NULL;
}

template<class TV,class TR>
Vertice<TV,TR>::Vertice(const TV& conteudo, int k)
{
	vconteudo=conteudo;
	key = k ;
	apvertice=NULL;
	apramo=NULL;
}

template<class TV,class TR>
Vertice<TV,TR>::Vertice(const Vertice<TV,TR>& v)
{
	vconteudo=v.vconteudo ;
	key = v.key ;
	apvertice=v.apvertice ;
	apramo=v.apramo ;
}

template<class TV,class TR>
Vertice<TV,TR>::~Vertice()
{

}

template<class TV,class TR>
TV Vertice<TV,TR>::GetConteudo() const  
{
   return vconteudo ; 

}


template<class TV,class TR>
int Vertice<TV,TR>::GetKey() const  
{
   return key ; 
}


template<class TV,class TR>
Vertice<TV,TR>* Vertice<TV,TR>::GetVertice() const  
{
   return apvertice ; 
}


template<class TV,class TR>
Ramo<TV,TR>* Vertice<TV,TR>::GetRamo() const  
{
   return apramo ; 
}


template<class TV,class TR>
void Vertice<TV,TR>::SetConteudo(const TV& conteudo)   
{
   vconteudo=conteudo ; 
}


template<class TV,class TR>
void Vertice<TV,TR>::SetKey(int k)   
{
   key=k ; 
}

template<class TV,class TR>
void Vertice<TV,TR>::SetVertice(const Vertice<TV,TR>* v)    
{
   apvertice=v ; 
}

template<class TV,class TR>
void Vertice<TV,TR>::SetRamo(const Ramo<TV,TR>* r)   
{
   apramo=r ; 
}

#endif
