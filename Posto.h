/* Projecto ESINF - 2� ano LEI -ISEP
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
 * Superclasse POSTO: topo da hierarquia de classes, � superclasse de ARMAZEM e
 * AUTOM�TICO. Nas classes derivadas poder�o ser instanciados objectos dos tipos
 * referidos.
 * @author Jo�o Carreira, Vitor Hugo Anjos
 * @version 1.0 (Oct 2012)
 */
class Posto{

private:
    /* chave do posto: cada posto � identificado por um n� inteiro > 0; esta key
     * tem que ser �nica entre os v�rios postos */
    int key;
    /* quantidade de mat�ria-prima que o posto tem em stock; representa uma dada
     * quantidade, em kg) */
    double stock;

public:
    /* prot�tipos de construtores e destrutor */
    Posto();
    Posto(int kp, double sp);
    Posto(const Posto &p);
    virtual ~Posto();

    /* prot�tipos de GETS e SETS */
    int getKey();
    double getStock();
    void setKey(int kp);
    void setStock(double sp);

    /* sobrecarga de operadores de compara��o */
    bool operator == (const Posto &p) const;
    bool operator > (const Posto &p) const;

    /* sobrecarga do operadtor de atribui��o */
    const Posto &operator = (const Posto &p);

    /* sobrecarga do operador de stream out */
    virtual void write(ostream &out) const;

};


/**
 * Construtor sem par�metros, cria um posto com chave e quantidade de stock
 * iguais a zero
 */
Posto::Posto(){
    setKey(0);
    setStock(0);
}


/**
 * Construtor com par�metros: cria um objecto do tipo POSTO, com os par�metros
 * kp (keyParameter) e sp (stockParameter)
 * @param kp    � a chava a atribuir ao posto
 * @param sp    � quantidade de mat�ria-prima que o posto disp�e
 */
Posto::Posto(int kp, double sp){
    setKey(kp);
    setStock(sp);
}


/**
 * Construtor c�pia: cria uma c�pia de um objecto do tipo POSTO, passado por
 * refer�ncia
 * @param p     � a refer�ncia do objecto do tipo Posto (declarada como const de
 *              forma a que o objecto copiado n�o sofra altera��es)
 */
Posto::Posto(const Posto &p){
    key = p.key;
    stock = p.stock;
}


/**
 * Destrutor para objectos do tipo POSTO (sem defini��o)
 */
Posto::~Posto(){
}


/**
 * M�todo de acesso p�blico � chave do posto
 * @return      � a chave do posto
 */
int Posto::getKey(){
    return key;
}


/**
 * M�todo de acesso p�blico ao stock de mater�a-prima presente no posto
 * @return      � a quantidade de mat�ria-prima presente no posto
 */
double Posto::getStock(){
    return stock;
}


/**
 * M�todo p�blico de modifica��o da chave do posto
 * @param       � a chave a atribuir ao posto
 */
void Posto::setKey(int kp){
    /* validar key, tem que ser positivo, caso contr�rio atribui 0 */
    kp > 0 ? key = kp : key = 0;
}


/**
 * M�todo p�blico de modifica��o do stock presente no posto
 * @param       � a quantidade de mat�ria-prima, em kg, a atribuir ao posto
 */
void Posto::setStock(double sp){
    /* valida se stock > 0, caso contr�rio stock = 0 */
    sp > 0 ? stock = sp : stock = 0;
}

/**
 * M�todo de escrita, imprime no ecr� a chave do posto e a quantidade de mat�ria
 * -prima presente em stock
 * @param out
 */
void Posto::write(ostream &out) const{
    cout << "---------------------------" << endl;
    cout << "Posto num: " << key << endl;
    cout << "Stock (kg): " << stock << endl;
}


/**
 * sobrecarga de operador de compara��o, para verificar se dois postos s�o
 * iguais em termos de quantidade de stock de mat�ria-prima
 * @param p     � a refer�ncia de um objecto do tipo posto
 * @return      TRUE, caso ambos os posto tenham a mesma quantidade de mat�ria-
 *              prima; FALSE, caso as quantidades de mat�ria-prima sejam
 *              diferentes
 */
bool Posto::operator == (const Posto &p) const{
    if(stock == p.stock)
        return true;
    else
        return false;
}


/**
 * sobrecarga do operador >, para verificar se a quantidade de mat�ria-prima
 * presente num dado posto � superior � de outro
 * @param p     � a refer�ncia de um objecto do tipo POSTO
 * @return      TRUE, caso a quantidade de mat�ria-prima presente num posto seja
 *              maior do que a daquele com que � comparado; FALSE, no caso
 *              oposto
 */
bool Posto::operator > (const Posto &p) const{
    return (stock > p.stock);
}


/**
 * sobrecarga do operador de atribui��o =, para atribuir, de forma directa, um
 * objecto do tipo POSTO a outro
 * @param p     refer�ncia para um objecto do tipo Posto
 * @return      apontador para o objecto corrente
 */
const Posto & Posto::operator = (const Posto &p){
    setKey(p.key);
    setStock(p.stock);
    return *this;
}


/**
 * Sobrecarga do operador de stream out
 * @param out   refer�ncia do standard output
 * @param p     refer�ncia de um objecto do tipo Posto
 * @return      refer�ncia do standard output
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

