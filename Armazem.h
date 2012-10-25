/* Projecto ESINF - 2º ano LEI -ISEP
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
 * key e stock de posto. É composta por um objecto do tipo ROBOT
 * @author João Carreira, Vitor Hugo Santos
 * @version: 1.0 (Oct 2012)
 */
class Armazem : public Posto{

private:
    /* quantidade de matéria prima de segurança (em kg) */
    double safety;
    /* robot associado ao posto armazém */
    Robot robot;

public:
    /* protótipos de construtopres e destrutor */
    Armazem();
    Armazem(int kp, double stp, double sap, Robot r);
    Armazem(const Armazem &a);
    ~Armazem();

    /* protótipos de GETS e SETS */
    double getSafety();
    Robot getRobot();
    void setSafety(double sap);
    void setRobot(Robot rp);

    /* sobrecarga de operadores de comparação */
    bool operator == (const Armazem &a) const;
    bool operator > (const Armazem &a) const;

    /* sobrecarga do operadtor de atribuição */
    const Armazem &operator = (const Armazem &a);

    /* sobrecarga do operador de stream out */
    void write(ostream &ostr) const;

};


/**
 * Construtor sem parâmetros, cria um posto armazém com matéria-prima a zero; invoca os
 * construtores sem parâmetros da superclasse POSTO e da classe ROBOT
 */
Armazem::Armazem():Posto(){
    setSafety(0);
    Robot robot;
}


/**
 * Construtor com parâmetros: cria um objecto do tipo ARMAZEM, com os parâmetros key e
 * stock (herdados de POSTO), safety e robot; invoca construtores com parâmetros de
 * POSTO e ROBOT
 * @param kp    é a chava a atribuir ao posto (herdado de POSTO)
 * @param stp   é a quantidade de matéria-prima que o posto dispõe (herdado de POSTO)
 * @param sap   é a quantidade de matéria-prima de segurança
 * @param rp    é o Robot associado ao posto armazém
 */
Armazem::Armazem(int kp, double stp, double sap, Robot rp):Posto(kp, stp), robot(rp){
    setSafety(sap);
}


/**
 * Construtor cópia: cria uma cópia de um objecto do tipo ARMAZEM, passado por
 * referência
 * @param a     é a referência do objecto do tipo ARMAZEM (declarada como const de
 *              forma a que o objecto copiado não sofra alterações)
 */
Armazem::Armazem(const Armazem &a):Posto(a){
    safety = a.safety;
    robot = a.robot;
}


/**
 * Destrutor para objectos do tipo POSTO (sem definição)
 */
Armazem::~Armazem(){
}


/**
 * Método de acesso público à quantidade de matéria-prima de segurança do armazém
 * @return      quantidade de matéria-prima de segurança
 */
double Armazem::getSafety(){
    return safety;
}


/**
 * Método de acesso público ao robot associado ao armazém
 * @return      é o robot associado ao armazém
 */
Robot Armazem::getRobot(){
    return robot;
}


/**
 * Método público de modificação da quantidade de matéria-prima de segurança
 * do posto armazém
 * @param sap       quantidade de matéria-prima de segurança
 */
void Armazem::setSafety(double sap){
    /* validação de safety: se < 0 fica a 0*/
    sap > 0 ? safety = sap: safety = 0;
}


/**
 * Método público de modificação do robot do armazém
 * @param rp    é o robot a associar ao armazém
 */
void Armazem::setRobot(Robot rp){
    robot = rp;
}


/**
 * Método de escrita, imprime no ecrã toda a informação sobre o armazém,
 * nomeadamente a sua chave de identicação e quantidade de matéria-prima
 * em stock (invocando o método de escrita da superclasse POSTO), a quantidade
 * de matéria-prima de segurança e a informação referente ao robot associado
 * ao armazém
 * @param out
 */
void Armazem::write(ostream &out) const{
    cout << "\nTipo de Posto: Armazém" << endl;
    Posto::write(out);
    cout << "Limite segurança (kg): " << safety << endl;
    cout << "Robot associado: " << robot << endl;
}


/**
 * sobrecarga de operador de comparação, para verificar se dois postos armazém
 * são iguais em termos de quantidade de matéria-prima em stock; invoca o operador
 * sobrecarregado == da superclasse POSTO
 * @param a     é a referência para um objecto do tipo ARMAZEM
 * @return      TRUE se tiverem a mesma quantidade de matéria-prima em stock, caso
                contrário devolve FALSE
 */
bool Armazem::operator == (const Armazem &a) const{
    return Posto::operator ==(a);
}


/**
 * sobrecarga do operador >, para verificar se o stock de matéria-prima de um
 * posto armazém é maior do que a de outro; invoca o operador sobrecarregado >
 * da superclasse POSTO
 * @param a     é a referência para um objecto do tipo ARMAZEM
 * @return      TRUE se a quantidade de metéria-prima em stock fôr superior, caso
                contrário devolve FALSE
 */
bool Armazem::operator > (const Armazem &a) const{
    return Posto::operator >(a);
}


/**
 * sobrecarga do operador de atribuição = para atribuir, directamente, um objecto
 * do tipo ARMAZEM a outro; invoca o operador sobrecarregado = da superclasse
 * POSTO de forma a que os atributos da superclasse sejam também atribuídos
 * @param a     é a referência para um objecto do tipo ARMAZEM
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
 * @param out   referência do standard output
 * @param a     referência de um objecto do tipo ARMAZEM
 * @return      referência do standard output
 */
ostream &operator << (ostream &out, const Armazem &a){
    a.write(out);
    return out;
}

#endif	/* ARMAZEM_H */

