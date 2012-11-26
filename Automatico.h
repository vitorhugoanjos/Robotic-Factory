/* Projecto ESINF - 2º ano LEI -ISEP
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
 * objectos dos postos automático de trabalho; herda os atributos key e stock de POSTO.
 * @author João Carreira, Vitor Hugo Anjos
 * @version: 1.0 (Oct 2012)
 */
class Automatico : public Posto{

private:
    /* quantidade de matéria-prima a requisitar (representa unidades em kg) */
    double request;
    /* velocidade de operação (representa unidades em kg/min) */
    double procSpeed;

public:
    /* protótipos de construtores e destrutor */
    Automatico();
    Automatico(int kp, double sp, double rp, double pSp);
    Automatico(const Automatico &a);
    ~Automatico();

    /* protótipos de GETS e SETS */
    double getRequest();
    double getProcSpeed();
    void setRequest(double rp);
    void setProcSpeed(double pSp);

    /* sobrecarga de operadores de comparação */
    bool operator == (const Automatico &a) const;
    bool operator > (const Automatico &a) const;

    /* sobrecarga do operadtor de atribuição */
    const Automatico &operator = (const Automatico &a);

    /* sobrecarga do operador de stream out */
    void write(ostream &ostr) const;

};

/**
 * Construtor sem parâmetros, cria um posto AUTOMATICO com matéria-prima a requisitar
 * e velocidade de operação a zero; invoca o construtor sem parâmetros da superclasse POSTO
 */
Automatico::Automatico():Posto(){
    setRequest(0);
    setProcSpeed(0);
}


/**
 * Construtor com parâmetros: cria um objecto do tipo AUTOMATICO, com os parâmetros key e
 * stock (herdados de POSTO), request e procSpeed; invoca o construtor com parâmetros de
 * POSTO
 * @param kp    é a chave a atribuir ao posto automático (herdado de POSTO)
 * @param sp    é a quantidade de matéria-prima que o posto automático dispõe (herdado de POSTO)
 * @param rp    é a quantidade de matéria-prima que o posto automático requisita
 * @param pSp   é a velocidade de operação do posto automático
 */
Automatico::Automatico(int kp, double sp, double rp, double pSp):Posto(kp, sp){
    setRequest(rp);
    setProcSpeed(pSp);
}


/**
 * Construtor cópia: cria uma cópia de um objecto do tipo AUTOMATICO, passado por
 * referência
 * @param a     é a referência do objecto do tipo AUTOMATICO (declarada como const de
 *              forma a que o objecto copiado não sofra alterações)
 */
Automatico::Automatico(const Automatico &a):Posto(a){
    request = a.request;
    procSpeed = a.procSpeed;
}


/**
 * Destrutor para objectos do tipo POSTO (sem definição)
 */
Automatico::~Automatico(){
}


/**
 * Método de acesso público à quantidade de matéria-prima requisitada pelo posto
 * automático
 * @return      quantidade de matéria-prima requisitada
 */
double Automatico::getRequest(){
    return request;
}


/**
 * Método de acesso público à velocidade de operação do posto automático
 * @return      velocidade de operação
 */
double Automatico::getProcSpeed(){
    return procSpeed;
}


/**
 * Método público de modificação da quantidade de matéria-prima requisitada pelo
 * posto automático
 * @param rp    quantidade de matéria-prima requisitada
 */
void Automatico::setRequest(double rp){
    /* valida se request > 0, caso contrário request = 0 */
    rp > 0 ? request = rp : request = 0;
}


/**
 * Método público de modificação da velocidade de operação do posto automático
 * @param pSp   velocidade de operação do posto automático
 */
void Automatico::setProcSpeed(double pSp){
    /* valida se procSpeed > 0, caso contrário procSpeed = 0 */
    pSp > 0 ? procSpeed = pSp : procSpeed = 0;
}


/**
 * Método de escrita, imprime no ecrã toda a informação sobre o posto automático,
 * nomeadamente a sua chave de identicação e quantidade de matéria-prima
 * em stock (invocando o método de escrita da superclasse POSTO), a quantidade
 * de matéria-prima requisitada e a sua velocidade de operação
 * @param out
 */
void Automatico::write(ostream &out) const{
    cout << "\nTipo de Posto: Automatico" << endl;
    Posto::write(out);
    cout << "Materia prima requisitada: " << request << " kg" << endl;
    cout << "Velocidade de operacao: " << procSpeed << " kg/min" << endl;
}


/**
 * sobrecarga de operador de comparação, para verificar se dois postos automáticos
 * são iguais em termos de quantidade de matéria-prima em stock; invoca o operador
 * sobrecarregado == da superclasse POSTO
 * @param a     é a referência para um objecto do tipo AUTOMATICO
 * @return      TRUE se tiverem a mesma quantidade de matéria-prima em stock, caso
                contrário devolve FALSE
 */
bool Automatico::operator == (const Automatico &a) const{
    return Posto::operator ==(a);
}


/**
 * sobrecarga do operador >, para verificar se o stock de matéria-prima de um
 * posto armazém é maior do que a de outro; invoca o operador sobrecarregado >
 * da superclasse POSTO
 * @param a     é a referência para um objecto do tipo AUTOMATICO
 * @return      TRUE se a quantidade de metéria-prima em stock fôr superior, caso
                contrário devolve FALSE
 */
bool Automatico::operator > (const Automatico &a) const{
    return Posto::operator >(a);
}


/**
 * sobrecarga do operador de atribuição = para atribuir, directamente, um objecto
 * do tipo AUTOMATICO a outro; invoca o operador sobrecarregado = da superclasse
 * POSTO de forma a que os atributos da superclasse sejam também atribuídos
 * @param a     é a referência para um objecto do tipo AUTOMATICO
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
 * @param out   referência do standard output
 * @param a     referência de um objecto do tipo AUTOMATICO
 * @return      referência do standard output
 */
ostream &operator << (ostream &out, const Automatico &a){
    a.write(out);
    return out;
}


#endif	/* AUTOMATICO_H */

