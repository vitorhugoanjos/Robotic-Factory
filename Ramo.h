#ifndef Ramo_
#define Ramo_

template<class TV,class TR>
class ListAdjGrafo;

template<class TV,class TR>
class Vertice;


template<class TV, class TR>   //Class representativa dos ramos que ligam vertices do grafo
class Ramo
{
	friend class ListAdjGrafo<TV,TR>;

	private:
		TR rconteudo;
		Vertice<TV,TR>* apv;
		Ramo<TV,TR>* apr;
	
	public:
		Ramo();
		Ramo(const TR& rcont, Vertice<TV,TR>* pv);
		Ramo(const Ramo<TV,TR>& r);
		~Ramo();

		TR GetConteudo() const ;
        Vertice<TV,TR>* GetVertice() const ;
		Ramo<TV,TR>* GetRamo() const ;

		void SetConteudo(const TR& conteudo) ;
		void SetVertice(const Vertice<TV,TR>* v) ;
		void SetRamo(const Ramo<TV,TR>* r) ; 

};

template<class TV,class TR>
Ramo<TV,TR>::Ramo()
{
	apv=NULL;
	apr=NULL;
}

template<class TV,class TR>
Ramo<TV,TR>::Ramo(const TR& rcont, Vertice<TV,TR>* pv)
{
	rconteudo=rcont;
	apv=pv;
	apr=NULL;
}

template<class TV,class TR>
Ramo<TV,TR>::Ramo(const Ramo<TV,TR>& r)
{
	rconteudo=r.rconteudo;
	apv=r.apv;
	apr=r.apr;
}

template<class TV,class TR>
Ramo<TV,TR>::~Ramo()
{

}

template<class TV,class TR>
TR Ramo<TV,TR>::GetConteudo() const  
{
   return rconteudo ; 
}


template<class TV,class TR>
Vertice<TV,TR>* Ramo<TV,TR>::GetVertice() const  
{
   return apv ; 
}

template<class TV,class TR>
Ramo<TV,TR>* Ramo<TV,TR>::GetRamo() const  
{
   return apr ; 
}

template<class TV,class TR>
void Ramo<TV,TR>::SetConteudo(const TR& conteudo)  
{
   rconteudo=conteudo ; 
}

template<class TV,class TR>
void Ramo<TV,TR>::SetVertice(const Vertice<TV,TR>* v)    
{
   apv=v ; 
}

template<class TV,class TR>
void Ramo<TV,TR>::SetRamo(const Ramo<TV,TR>* r)  
{
   apr=r ; 
}

#endif