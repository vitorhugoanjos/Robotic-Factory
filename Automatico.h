/* Projecto ESINF - 2� ano LEI -ISEP
 * Outubro 2012
 *
 * File:   Posto.h
 *
 * Created on October 16, 2012, 1:02 PM
 */

#ifndef AUTOMATICO_H
#define	AUTOMATICO_H

#include <iostream>
#include "Posto.h"
using namespace std;

/*
 * Subclasse AUTOMATICO: derivada de POSTO, permite instanciar objectos do tipo AUTOMATICO, que representa
 * objectos dos postos autom�tico de trabalho; herda os atributos key e stock de POSTO.
 * @author Jo�o Carreira, Vitor Hugo Anjos
 * @version: 1.0 (Oct 2012)
 */
class Automatico : public Posto{

private:
    /* quantidade de mat�ria-prima a requisitar (representa unidades em kg) */
    double request;
    /* velocidade de opera��o (representa unidades em kg/min) */
    double procSpeed;

public:
    /* prot�tipos de construtores e destrutor */
    Automatico();
    Automatico(int kp, double sp, double rp, double pSp);
    Automatico(const Automatico &a);
    ~Automatico();

    /* prot�tipos de GETS e SETS */
    double getRequest();
    double getProcSpeed();
    void setRequest(double rp);
    void setProcSpeed(double pSp);

    /* sobrecarga de operadores de compara��o */
    bool operator == (const Automatico &a) const;
    bool operator > (const Automatico &a) const;

    /* sobrecarga do operadtor de atribui��o */
    const Automatico &operator = (const Automatico &a);

    /* sobrecarga do operador de stream out */
    void write(ostream &ostr) const;

};

/**
 * Construtor sem par�metros, cria um posto AUTOMATICO com mat�ria-prima a requisitar
 * e velocidade de opera��o a zero; invoca o construtor sem par�metros da superclasse POSTO
 */
Automatico::Automatico():Posto(){
    setRequest(0);
    setProcSpeed(0);
}


/**
 * Construtor com par�metros: cria um objecto do tipo AUTOMATICO, com os par�metros key e
 * stock (herdados de POSTO), request e procSpeed; invoca o construtor com par�metros de
 * POSTO
 * @param kp    � a chave a atribuir ao posto autom�tico (herdado de POSTO)
 * @param sp    � a quantidade de mat�ria-prima que o posto autom�tico disp�e (herdado de POSTO)
 * @param rp    � a quantidade de mat�ria-prima que o posto autom�tico requisita
 * @param pSp   � a velocidade de opera��o do posto autom�tico
 */
Automatico::Automatico(int kp, double sp, double rp, double pSp):Posto(kp, sp){
    setRequest(rp);
    setProcSpeed(pSp);
}


/**
 * Construtor c�pia: cria uma c�pia de um objecto do tipo AUTOMATICO, passado por
 * refer�ncia
 * @param a     � a refer�ncia do objecto do tipo AUTOMATICO (declarada como const de
 *              forma a que o objecto copiado n�o sofra altera��es)
 */
Automatico::Automatico(const Automatico &a):Posto(a){
    request = a.request;
    procSpeed = a.procSpeed;
}


/**
 * Destrutor para objectos do tipo POSTO (sem defini��o)
 */
Automatico::~Automatico(){
}


/**
 * M�todo de acesso p�blico � quantidade de mat�ria-prima requisitada pelo posto
 * autom�tico
 * @return      quantidade de mat�ria-prima requisitada
 */
double Automatico::getRequest(){
    return request;
}


/**
 * M�todo de acesso p�blico � velocidade de opera��o do posto autom�tico
 * @return      velocidade de opera��o
 */
double Automatico::getProcSpeed(){
    return procSpeed;
}


/**
 * M�todo p�blico de modifica��o da quantidade de mat�ria-prima requisitada pelo
 * posto autom�tico
 * @param rp    quantidade de mat�ria-prima requisitada
 */
void Automatico::setRequest(double rp){
    /* valida se request > 0, caso contr�rio request = 0 */
    rp > 0 ? request = rp : request = 0;
}


/**
 * M�todo p�blico de modifica��o da velocidade de opera��o do posto autom�tico
 * @param pSp   velocidade de opera��o do posto autom�tico
 */
void Automatico::setProcSpeed(double pSp){
    /* valida se procSpeed > 0, caso contr�rio procSpeed = 0 */
    pSp > 0 ? procSpeed = pSp : procSpeed = 0;
}


/**
 * M�todo de escrita, imprime no ecr� toda a informa��o sobre o posto autom�tico,
 * nomeadamente a sua chave de identica��o e quantidade de mat�ria-prima
 * em stock (invocando o m�todo de escrita da superclasse POSTO), a quantidade
 * de mat�ria-prima requisitada e a sua velocidade de opera��o
 * @param out
 */
void Automatico::write(ostream &out) const{
    cout << "\nTipo de Posto: Automatico" << endl;
    Posto::write(out);
    cout << "Materia prima requisitada: " << request << " kg" << endl;
    cout << "Velocidade de operacao: " << procSpeed << " kg/min" << endl;
}


/**
 * sobrecarga de operador de compara��o, para verificar se dois postos autom�ticos
 * s�o iguais em termos de quantidade de mat�ria-prima em stock; invoca o operador
 * sobrecarregado == da superclasse POSTO
 * @param a     � a refer�ncia para um objecto do tipo AUTOMATICO
 * @return      TRUE se tiverem a mesma quantidade de mat�ria-prima em stock, caso
                contr�rio devolve FALSE
 */
bool Automatico::operator == (const Automatico &a) const{
    return Posto::operator ==(a);
}


/**
 * sobrecarga do operador >, para verificar se o stock de mat�ria-prima de um
 * posto armaz�m � maior do que a de outro; invoca o operador sobrecarregado >
 * da superclasse POSTO
 * @param a     � a refer�ncia para um objecto do tipo AUTOMATICO
 * @return      TRUE se a quantidade de met�ria-prima em stock f�r superior, caso
                contr�rio devolve FALSE
 */
bool Automatico::operator > (const Automatico &a) const{
    return Posto::operator >(a);
}


/**
 * sobrecarga do operador de atribui��o = para atribuir, directamente, um objecto
 * do tipo AUTOMATICO a outro; invoca o operador sobrecarregado = da superclasse
 * POSTO de forma a que os atributos da superclasse sejam tamb�m atribu�dos
 * @param a     � a refer�ncia para um objecto do tipo AUTOMATICO
 * @return      apontador para o objecto corrente
 */
const Automatico & Automatico::operator = (const Automatico &a){
    Posto::operator =(a);
    setRequest(a.request);
    setProcSpeed(a.procSpeed);
    return *this;
}


/**
 * Sobrecarga do operador de stream out
 * @param out   refer�ncia do standard output
 * @param a     refer�ncia de um objecto do tipo AUTOMATICO
 * @return      refer�ncia do standard output
 */
ostream &operator << (ostream &out, const Automatico &a){
    a.write(out);
    return out;
}


#endif	/* AUTOMATICO_H */

