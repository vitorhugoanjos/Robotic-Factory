/* Projecto ESINF - 2� ano LEI -ISEP
 *
 * Outubro 2012
 *
 * File:   Posto.h
 * Authors: Jo�o Carreira
 *
 * Created on October 16, 2012, 1:02 PM
 */

 #ifndef DSTTIME_H
 #define DSTTIME_H

 #include <iostream>
 using namespace std;

 /**
 * Class DstTime: classe que cria objectos do tipo DSTTIME, que caracteriza o tempo e
 * a dist�ncias que separam dois postos (tanto autom�ticos como armaz�m)
 */
 class DstTime{

 private:
 	/* dist�ncia, em metros, entre dois postos */
 	double dst;
 	/* dist�ncia, em minutos, entre dois postos */
 	double time;

public:
	/* prot�tipos de construtores e destrutores */
	DstTime();
	DstTime(double dp, double tp);
	DstTime(const DstTime &dt);
	~DstTime();

	/* prot�tipos do m�todo clone */
	DstTime *clone() const;

	/* prot�tipos de GETS e SETS */
	double getDst();
	double getTime();
	void setDst(double dp);
	void setTime(double tp);

	/* sobrecarga de operadores de comapara��o */
	bool operator == (const DstTime &dt) const;
	bool operator > (const DstTime &dt) const;
	bool operator != (const DstTime &dt) const;

	/* sobrecarga do operador de atribui��o */
	const DstTime &operator = (const DstTime &dt);

	/* sobrecarga do operador de stream out */
	void write(ostream &ostr) const;

 };


 /**
 * Construtor sem par�metros, cria um objecto DSTTIME com dist�ncia e tempo a zero
 */
 DstTime::DstTime(){
 	setDst(0);
 	setTime(0);
 }


 /**
 * Construtor com par�metros, cria um objecto DSTTIME, com os par�metros dist�ncia
 * e tempo
 * @param dp		� a dist�ncia que separa dois postos
 * @param tp 		� o tempo entre dois postos
 */
 DstTime::DstTime(double dp, double tp){
 	setDst(dp);
 	setTime(tp);
 }


 /**
 * Construtor c�pia, cria uma c�pia do objecto do tipo DSTTIME, passado por refer�ncia
 * @param dt 	� a refer�ncia do objecto do tipo DSTTIME (declarado como const de forma
 *				a que o objecto n�o seja modificado
 */
 DstTime::DstTime(const DstTime &dt){
 	dst = dt.dst;
 	time = dt.time;
 }


 /**
 * Destrutor para objectos do tipo DSTTIME (sem defini��o)
 */
 DstTime::~DstTime(){
 }


/**
* M�todo clone, necess�rio para a matriz din�mica
*/
DstTime * DstTime::clone() const{
	return new DstTime(*this);
}


 /**
 * M�todo de acesso p�blico � dist�ncia entre dois postos
 * @return 		dist�ncia, em metros, que separa dois postos
 */
 double DstTime::getDst(){
 	return dst;
 }


 /**
 * M�todo de acesso p�blico ao tempo entre dois postos
 * @return 		tempo, em minutos, que separa dois postos
 */
 double DstTime::getTime(){
 	return time;
 }


 /**
 * M�todo p�blico de modifica��o da dist�ncia entre dois postos
 * @param dp	dist�ncia entre dois postos (em metros)
 */
 void DstTime::setDst(double dp){
 	/* valida��o da dist�ncia, tem que ser um valor positivo, caso contr�rio atribui -1;
 	-1 fica como valor indicativo de uma dist�ncia inv�lida */
 	dp > 0 ? dst = dp : dst = -1;
 }


/**
 * M�todo p�blico de modifica��o do tempo entre dois postos
 * @param tp	tempo entre dois postos (em minutos)
 */
 void DstTime::setTime(double tp){
 	/* valida��o do tempo, tem que ser um valor positivo, caso contr�rio atribui -1;
 	-1 fica como valor indicativo de um tempo inv�lido */
 	tp > 0 ? time = tp : time = -1;
 }


/**
 * M�todo de escrita, imprime no ecr� a dist�ncia e o tempo que separam dois postos
 * @param out
 */
void DstTime::write(ostream &out) const{
    cout << dst << " metros" << endl;
    cout << time << " minutos" << endl;
}


/**
 * sobrecarga de operador de compara��o, permite verificar se a dist�ncia que separa
 * dois postos � a mesma
 * @param dt    � a refer�ncia de um objecto do tipo DSTTIME
 * @return      TRUE, caso a dist�ncia seja igual; FALSE, no caso oposto
 */
bool DstTime::operator == (const DstTime &dt) const{
    return(dst == dt.dst && time == dt.time);
}


/**
 * sobrecarga de operador >, permite verificar se uma dist�ncia � maior do que
 * outra
 * @param dt    � a refer�ncia de um objecto do tipo DSTTIME
 * @return      TRUE, caso a dist�ncia seja maior; FALSE, no caso oposto
 */
bool DstTime::operator > (const DstTime &dt) const{
    return (dst > dt.dst);
}


/**
 * sobrecarga do opereador !=, permite verificar se um objecto DstTime �
 * diferente de outro (m�todo necess�rio para determinadas fun��es do
 * array din�mico, do ficheiro Dyn2DArray.h)
 */
bool DstTime::operator != (const DstTime &dt) const{
	if(dst != dt.dst || dst != dt.time)
		return true;
	else
		return false;
}


/**
 * sobrecarga do operador de atribui��o =, para atribuir, de forma directa, um
 * objecto do tipo DSTTIME a outro
 * @param dt    refer�ncia para um objecto do tipo DSTTIME
 * @return      apontador para o objecto corrente
 */
const DstTime & DstTime::operator = (const DstTime &dt){
	setDst(dt.dst);
	setTime(dt.time);
	return *this;
}


/**
 * Sobrecarga do operador de stream out
 * @param out   refer�ncia do standard output
 * @param dt    refer�ncia de um objecto do tipo DSTTIME
 * @return      refer�ncia do standard output
 */
ostream &operator << (ostream &out, const DstTime &dt){
    dt.write(out);
    return out;
}

#endif /* DSTTIME_H */
