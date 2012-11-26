/* Projecto ESINF - 2� ano LEI -ISEP
 * Outubro 2012
 *
 * File:   Posto.h
 *
 * Created on October 16, 2012, 1:02 PM
 */

#ifndef ARMAZEM_H
#define	ARMAZEM_H

#include <iostream>
#include "Robot.h"
#include "Posto.h"
using namespace std;

/*
 * Subclasse ARMAZEM: derivada de POSTO, permite instanciar objectos do tipo ARMAZEM; herda os atributos
 * key e stock de posto. � composta por um objecto do tipo ROBOT
 * @author Jo�o Carreira, Vitor Hugo Anjos
 * @version: 1.0 (Oct 2012)
 */
class Armazem : public Posto{

private:
    /* quantidade de mat�ria prima de seguran�a (em kg) */
    double safety;
    /* robot associado ao posto armaz�m */
    Robot robot;

public:
    /* prot�tipos de construtopres e destrutor */
    Armazem();
    Armazem(int kp, double stp, double sap, Robot r);
    Armazem(const Armazem &a);
    ~Armazem();

    /* prot�tipos de GETS e SETS */
    double getSafety();
    Robot getRobot();
    void setSafety(double sap);
    void setRobot(Robot rp);
    void getSupplies();

    /* sobrecarga de operadores de compara��o */
    bool operator == (const Armazem &a) const;
    bool operator > (const Armazem &a) const;

    /* sobrecarga do operadtor de atribui��o */
    const Armazem &operator = (const Armazem &a);

    /* sobrecarga do operador de stream out */
    void write(ostream &ostr) const;

};


/**
 * Construtor sem par�metros, cria um posto armaz�m com mat�ria-prima a zero; invoca os
 * construtores sem par�metros da superclasse POSTO e da classe ROBOT
 */
Armazem::Armazem():Posto(){
    setSafety(0);
    Robot robot;
}


/**
 * Construtor com par�metros: cria um objecto do tipo ARMAZEM, com os par�metros key e
 * stock (herdados de POSTO), safety e robot; invoca construtores com par�metros de
 * POSTO e ROBOT
 * @param kp    � a chava a atribuir ao posto (herdado de POSTO)
 * @param stp   � a quantidade de mat�ria-prima que o posto disp�e (herdado de POSTO)
 * @param sap   � a quantidade de mat�ria-prima de seguran�a
 * @param rp    � o Robot associado ao posto armaz�m
 */
Armazem::Armazem(int kp, double stp, double sap, Robot rp):Posto(kp, stp), robot(rp){
    setSafety(sap);
}


/**
 * Construtor c�pia: cria uma c�pia de um objecto do tipo ARMAZEM, passado por
 * refer�ncia
 * @param a     � a refer�ncia do objecto do tipo ARMAZEM (declarada como const de
 *              forma a que o objecto copiado n�o sofra altera��es)
 */
Armazem::Armazem(const Armazem &a):Posto(a){
    safety = a.safety;
    robot = a.robot;
}


/**
 * Destrutor para objectos do tipo POSTO (sem defini��o)
 */
Armazem::~Armazem(){
}


/**
 * M�todo de acesso p�blico � quantidade de mat�ria-prima de seguran�a do armaz�m
 * @return      quantidade de mat�ria-prima de seguran�a
 */
double Armazem::getSafety(){
    return safety;
}


/**
 * M�todo de acesso p�blico ao robot associado ao armaz�m
 * @return      � o robot associado ao armaz�m
 */
Robot Armazem::getRobot(){
    return robot;
}


/**
 * M�todo p�blico de modifica��o da quantidade de mat�ria-prima de seguran�a
 * do posto armaz�m
 * @param sap       quantidade de mat�ria-prima de seguran�a
 */
void Armazem::setSafety(double sap){
    /* valida��o de safety: se < 0 fica a 0*/
    sap > 0 ? safety = sap: safety = 0;
}


/**
 * M�todo p�blico de modifica��o do robot do armaz�m
 * @param rp    � o robot a associar ao armaz�m
 */
void Armazem::setRobot(Robot rp){
    robot = rp;
}

/**
* M�todo p�blico que faz o abastecimento, a quantidade
* abastecida � tr�s vezes a quantidade de seguran�a do armaz�m.
*/
void Armazem::getSupplies(){
    Posto::setStock(safety*3);
}



/**
 * M�todo de escrita, imprime no ecr� toda a informa��o sobre o armaz�m,
 * nomeadamente a sua chave de identica��o e quantidade de mat�ria-prima
 * em stock (invocando o m�todo de escrita da superclasse POSTO), a quantidade
 * de mat�ria-prima de seguran�a e a informa��o referente ao robot associado
 * ao armaz�m
 * @param out
 */
void Armazem::write(ostream &out) const{
    cout << "\nTipo de Posto: Armazem" << endl;
    Posto::write(out);
    cout << "Limite seguranca: " << safety << " kg" << endl;
    cout << "Robot associado: " << robot << endl;
}


/**
 * sobrecarga de operador de compara��o, para verificar se dois postos armaz�m
 * s�o iguais em termos de quantidade de mat�ria-prima em stock; invoca o operador
 * sobrecarregado == da superclasse POSTO
 * @param a     � a refer�ncia para um objecto do tipo ARMAZEM
 * @return      TRUE se tiverem a mesma quantidade de mat�ria-prima em stock, caso
                contr�rio devolve FALSE
 */
bool Armazem::operator == (const Armazem &a) const{
    return Posto::operator ==(a);
}


/**
 * sobrecarga do operador >, para verificar se o stock de mat�ria-prima de um
 * posto armaz�m � maior do que a de outro; invoca o operador sobrecarregado >
 * da superclasse POSTO
 * @param a     � a refer�ncia para um objecto do tipo ARMAZEM
 * @return      TRUE se a quantidade de met�ria-prima em stock f�r superior, caso
                contr�rio devolve FALSE
 */
bool Armazem::operator > (const Armazem &a) const{
    return Posto::operator >(a);
}


/**
 * sobrecarga do operador de atribui��o = para atribuir, directamente, um objecto
 * do tipo ARMAZEM a outro; invoca o operador sobrecarregado = da superclasse
 * POSTO de forma a que os atributos da superclasse sejam tamb�m atribu�dos
 * @param a     � a refer�ncia para um objecto do tipo ARMAZEM
 * @return      apontador para o objecto corrente
 */
const Armazem & Armazem::operator = (const Armazem &a){
    Posto::operator =(a);
    setSafety(a.safety);
    setRobot(a.robot);
    return *this;
}


/**
 * Sobrecarga do operador de stream out
 * @param out   refer�ncia do standard output
 * @param a     refer�ncia de um objecto do tipo ARMAZEM
 * @return      refer�ncia do standard output
 */
ostream &operator << (ostream &out, const Armazem &a){
    a.write(out);
    return out;
}

#endif	/* ARMAZEM_H */

