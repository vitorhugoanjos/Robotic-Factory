/* Projecto ESINF - 2º ano LEI -ISEP
 * Outubro 2012
 *
 * File:   Posto.h
 *
 * Created on October 16, 2012, 1:02 PM
 */

#ifndef POSTO_H
#define	POSTO_H

#include <iostream>
using namespace std;

/**
 * Superclasse POSTO: topo da hierarquia de classes, é superclasse de ARMAZEM e
 * AUTOMÁTICO. Nas classes derivadas poderão ser instanciados objectos dos tipos
 * referidos.
 * @author João Carreira, Vitor Hugo Anjos
 * @version 1.0 (Oct 2012)
 */
class Posto{

private:
    /* chave do posto: cada posto é identificado por um nº inteiro > 0; esta key
     * tem que ser única entre os vários postos */
    int key;
    /* quantidade de matéria-prima que o posto tem em stock; representa uma dada
     * quantidade, em kg) */
    double stock;

public:
    /* protótipos de construtores e destrutor */
    Posto();
    Posto(int kp, double sp);
    Posto(const Posto &p);
    virtual ~Posto();

    /* protótipos de GETS e SETS */
    int getKey();
    double getStock();
    void setKey(int kp);
    void setStock(double sp);

    /* sobrecarga de operadores de comparação */
    bool operator == (const Posto &p) const;
    bool operator > (const Posto &p) const;

    /* sobrecarga do operadtor de atribuição */
    const Posto &operator = (const Posto &p);

    /* sobrecarga do operador de stream out */
    virtual void write(ostream &out) const;

};


/**
 * Construtor sem parâmetros, cria um posto com chave e quantidade de stock
 * iguais a zero
 */
Posto::Posto(){
    setKey(0);
    setStock(0);
}


/**
 * Construtor com parâmetros: cria um objecto do tipo POSTO, com os parâmetros
 * kp (keyParameter) e sp (stockParameter)
 * @param kp    é a chava a atribuir ao posto
 * @param sp    é quantidade de matéria-prima que o posto dispõe
 */
Posto::Posto(int kp, double sp){
    setKey(kp);
    setStock(sp);
}


/**
 * Construtor cópia: cria uma cópia de um objecto do tipo POSTO, passado por
 * referência
 * @param p     é a referência do objecto do tipo Posto (declarada como const de
 *              forma a que o objecto copiado não sofra alterações)
 */
Posto::Posto(const Posto &p){
    key = p.key;
    stock = p.stock;
}


/**
 * Destrutor para objectos do tipo POSTO (sem definição)
 */
Posto::~Posto(){
}


/**
 * Método de acesso público à chave do posto
 * @return      é a chave do posto
 */
int Posto::getKey(){
    return key;
}


/**
 * Método de acesso público ao stock de matería-prima presente no posto
 * @return      é a quantidade de matéria-prima presente no posto
 */
double Posto::getStock(){
    return stock;
}


/**
 * Método público de modificação da chave do posto
 * @param       é a chave a atribuir ao posto
 */
void Posto::setKey(int kp){
    /* validar key, tem que ser positivo, caso contrário atribui 0 */
    kp > 0 ? key = kp : key = 0;
}


/**
 * Método público de modificação do stock presente no posto
 * @param       é a quantidade de matéria-prima, em kg, a atribuir ao posto
 */
void Posto::setStock(double sp){
    /* valida se stock > 0, caso contrário stock = 0 */
    sp > 0 ? stock = sp : stock = 0;
}

/**
 * Método de escrita, imprime no ecrã a chave do posto e a quantidade de matéria
 * -prima presente em stock
 * @param out
 */
void Posto::write(ostream &out) const{
    cout << "---------------------------" << endl;
    cout << "Posto nº: " << key << endl;
    cout << "Stock (kg): " << stock << endl;
}


/**
 * sobrecarga de operador de comparação, para verificar se dois postos são
 * iguais em termos de quantidade de stock de matéria-prima
 * @param p     é a referência de um objecto do tipo posto
 * @return      TRUE, caso ambos os posto tenham a mesma quantidade de matéria-
 *              prima; FALSE, caso as quantidades de matéria-prima sejam
 *              diferentes
 */
bool Posto::operator == (const Posto &p) const{
    if(stock == p.stock)
        return true;
    else
        return false;
}


/**
 * sobrecarga do operador >, para verificar se a quantidade de matéria-prima
 * presente num dado posto é superior à de outro
 * @param p     é a referência de um objecto do tipo POSTO
 * @return      TRUE, caso a quantidade de matéria-prima presente num posto seja
 *              maior do que a daquele com que é comparado; FALSE, no caso
 *              oposto
 */
bool Posto::operator > (const Posto &p) const{
    return (stock > p.stock);
}


/**
 * sobrecarga do operador de atribuição =, para atribuir, de forma directa, um
 * objecto do tipo POSTO a outro
 * @param p     referência para um objecto do tipo Posto
 * @return      apontador para o objecto corrente
 */
const Posto & Posto::operator = (const Posto &p){
    setKey(p.key);
    setStock(p.stock);
    return *this;
}


/**
 * Sobrecarga do operador de stream out
 * @param out   referência do standard output
 * @param p     referência de um objecto do tipo Posto
 * @return      referência do standard output
 */
ostream &operator << (ostream &out, const Posto &p){
    p.write(out);
    return out;
}

ostream &operator << (ostream &out, const Posto *p){
    p->write(out);
    return out;
}


#endif	/* POSTO_H */

