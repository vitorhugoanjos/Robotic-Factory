/* Projecto ESINF - 2º ano LEI -ISEP
 *
 * Outubro 2012
 *
 * File:   Posto.h
 * Authors: João Carreira
 *
 * Created on October 16, 2012, 1:02 PM
 */

 #ifndef DSTTIME_H
 #define DSTTIME_H

 #include <iostream>
 using namespace std;

 /**
 * Class DstTime: classe que cria objectos do tipo DSTTIME, que caracteriza o tempo e
 * a distâncias que separam dois postos (tanto automáticos como armazém)
 */
 class DstTime{

 private:
 	/* distância, em metros, entre dois postos */
 	double dst;
 	/* distância, em minutos, entre dois postos */
 	double time;

public:
	/* protótipos de construtores e destrutores */
	DstTime();
	DstTime(double dp, double tp);
	DstTime(const DstTime &dt);
	~DstTime();

	/* protótipos do método clone */
	DstTime *clone() const;

	/* protótipos de GETS e SETS */
	double getDst();
	double getTime();
	void setDst(double dp);
	void setTime(double tp);

	/* sobrecarga de operadores de comaparação */
	bool operator == (const DstTime &dt) const;
	bool operator > (const DstTime &dt) const;
	bool operator != (const DstTime &dt) const;

	/* sobrecarga do operador de atribuição */
	const DstTime &operator = (const DstTime &dt);

	/* sobrecarga do operador de stream out */
	void write(ostream &ostr) const;

 };


 /**
 * Construtor sem parâmetros, cria um objecto DSTTIME com distância e tempo a zero
 */
 DstTime::DstTime(){
 	setDst(0);
 	setTime(0);
 }


 /**
 * Construtor com parâmetros, cria um objecto DSTTIME, com os parâmetros distância
 * e tempo
 * @param dp		é a distância que separa dois postos
 * @param tp 		é o tempo entre dois postos
 */
 DstTime::DstTime(double dp, double tp){
 	setDst(dp);
 	setTime(tp);
 }


 /**
 * Construtor cópia, cria uma cópia do objecto do tipo DSTTIME, passado por referência
 * @param dt 	é a referência do objecto do tipo DSTTIME (declarado como const de forma
 *				a que o objecto não seja modificado
 */
 DstTime::DstTime(const DstTime &dt){
 	dst = dt.dst;
 	time = dt.time;
 }


 /**
 * Destrutor para objectos do tipo DSTTIME (sem definição)
 */
 DstTime::~DstTime(){
 }


/**
* Método clone, necessário para a matriz dinâmica
*/
DstTime * DstTime::clone() const{
	return new DstTime(*this);
}


 /**
 * Método de acesso público à distância entre dois postos
 * @return 		distância, em metros, que separa dois postos
 */
 double DstTime::getDst(){
 	return dst;
 }


 /**
 * Método de acesso público ao tempo entre dois postos
 * @return 		tempo, em minutos, que separa dois postos
 */
 double DstTime::getTime(){
 	return time;
 }


 /**
 * Método público de modificação da distância entre dois postos
 * @param dp	distância entre dois postos (em metros)
 */
 void DstTime::setDst(double dp){
 	/* validação da distância, tem que ser um valor positivo, caso contrário atribui -1;
 	-1 fica como valor indicativo de uma distância inválida */
 	dp > 0 ? dst = dp : dst = -1;
 }


/**
 * Método público de modificação do tempo entre dois postos
 * @param tp	tempo entre dois postos (em minutos)
 */
 void DstTime::setTime(double tp){
 	/* validação do tempo, tem que ser um valor positivo, caso contrário atribui -1;
 	-1 fica como valor indicativo de um tempo inválido */
 	tp > 0 ? time = tp : time = -1;
 }


/**
 * Método de escrita, imprime no ecrã a distância e o tempo que separam dois postos
 * @param out
 */
void DstTime::write(ostream &out) const{
    cout << dst << " metros" << endl;
    cout << time << " minutos" << endl;
}


/**
 * sobrecarga de operador de comparação, permite verificar se a distância que separa
 * dois postos é a mesma
 * @param dt    é a referência de um objecto do tipo DSTTIME
 * @return      TRUE, caso a distância seja igual; FALSE, no caso oposto
 */
bool DstTime::operator == (const DstTime &dt) const{
    return(dst == dt.dst && time == dt.time);
}


/**
 * sobrecarga de operador >, permite verificar se uma distância é maior do que
 * outra
 * @param dt    é a referência de um objecto do tipo DSTTIME
 * @return      TRUE, caso a distância seja maior; FALSE, no caso oposto
 */
bool DstTime::operator > (const DstTime &dt) const{
    return (dst > dt.dst);
}


/**
 * sobrecarga do opereador !=, permite verificar se um objecto DstTime é
 * diferente de outro (método necessário para determinadas funções do
 * array dinâmico, do ficheiro Dyn2DArray.h)
 */
bool DstTime::operator != (const DstTime &dt) const{
	if(dst != dt.dst || dst != dt.time)
		return true;
	else
		return false;
}


/**
 * sobrecarga do operador de atribuição =, para atribuir, de forma directa, um
 * objecto do tipo DSTTIME a outro
 * @param dt    referência para um objecto do tipo DSTTIME
 * @return      apontador para o objecto corrente
 */
const DstTime & DstTime::operator = (const DstTime &dt){
	setDst(dt.dst);
	setTime(dt.time);
	return *this;
}


/**
 * Sobrecarga do operador de stream out
 * @param out   referência do standard output
 * @param dt    referência de um objecto do tipo DSTTIME
 * @return      referência do standard output
 */
ostream &operator << (ostream &out, const DstTime &dt){
    dt.write(out);
    return out;
}

#endif /* DSTTIME_H */
