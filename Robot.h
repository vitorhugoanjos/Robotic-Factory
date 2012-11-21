/* Projecto ESINF - 2� ano LEI -ISEP
 * Outubro 2012
 *
 * File:   Posto.h
 *
 * Created on October 16, 2012, 1:02 PM
 */

#ifndef ROBOT_H
#define	ROBOT_H

#include <iostream>

#include "Posto.h"
using namespace std;

/*
 * Subclasse ROBOT permite instanciar objectos do tipo ROBOT
 * @author Jo�o Carreira, Vitor Hugo Anjos
 * @version: 1.0 (Oct 2012)
 */
class Robot{
private:
    /* chave de identifica��o do robot (inteiro > 0, �nica entre robots
    mas distinta dos postos) */
    int robotKey;
    /* capacidade de carga do robot (kg) */
    double cargoCap;
    /* mat�ria-prima dispon�vel no robot (kg) */
    double cargoAvail;
    /* posi��o em que o robot se econtra (corresponde � key do posto) */
    int position;

public:
    /* prot�tipos de construtores e destrutor */
    Robot();
    Robot(int rKp, double cCp, double cAp, int pp);
    Robot(const Robot &r);
    ~Robot();

    /* prot�tipos de GETS e SETS */
    int getRobotKey();
    double getCargoCap();
    double getCargoAvail();
    int getPosition();
    void setRobotKey(int rKp);
    void setCargoCap(double cCp);
    void setCargoAvail(double cAp);
    void setPosition(int pp);
    void supply(double qt);
    void getSupplies();

    /* sobrecarga de operadores de compara��o */
    bool operator == (const Robot &e) const;
    bool operator > (const Robot &r) const;

    /* sobrecarga do operadtor de atribui��o */
    const Robot &operator = (const Robot &r);

    /* sobrecarga do operador de stream out */
    void write(ostream &ostr) const;
};


/**
 * Construtor sem par�metros, cria um robot com todos os seus par�metros a zero,
 * nomeadamente a sua chave, capacidade de carga, mat�ria-prima dispon�vel e
 * posi��o
 */
Robot::Robot(){
    setRobotKey(0);
    setCargoCap(0);
    setCargoAvail(0);
    setPosition(0);
}


/**
 * Construtor com par�metros: cria um objecto do tipo ROBOT, com os par�metros robotKey,
 * cargoCap, cargoAvail e position
 * @param rkp   � a chava a atribuir ao robot
 * @param cCp   � quantidade de mat�ria-prima capaz de transportar
 * @param cAp   � a quantidade de mat�ria-prima que tem dispon�vel
 * @param pp    � a posi��o em que o robot se encontra
 */
Robot::Robot(int rKp, double cCp, double cAp, int pp){
    setRobotKey(rKp);
    setCargoCap(cCp);
    setCargoAvail(cAp);
    setPosition(pp);
}


/**
 * Construtor c�pia: cria uma c�pia de um objecto do tipo ROBOT, passado por
 * refer�ncia
 * @param r     � a refer�ncia do objecto do tipo ROBOT (declarada como const de
 *              forma a que o objecto copiado n�o sofra altera��es)
 */
Robot::Robot(const Robot &r){
    robotKey = r.robotKey;
    cargoCap = r.cargoCap;
    cargoAvail = r.cargoAvail;
    position = r.position;
}


/**
 * Destrutor para objectos do tipo POSTO (sem defini��o)
 */
Robot::~Robot(){

}


/**
 * M�todo de acesso p�blico � chave de identifica��o do robot
 * @return      chave de identifica��o do robot
 */
int Robot::getRobotKey(){
    return robotKey;
}

/**
 * M�todo de acesso p�blico � capacidade de carga do robot
 * @return      capacidade de carga do robot
 */
double Robot::getCargoCap(){
    return cargoCap;
}


/**
 * M�todo de acesso p�blico � quantidade de mat�ria-prima que o robot ainda
 * tem dispon�vel
 * @return      quantidade de mat�ria-prima dispon�vel
 */
double Robot::getCargoAvail(){
    return cargoAvail;
}


/**
 * M�todo de acesso p�blico � localiza��o actual do robot
 * @return      posi��o do robot
 */
int Robot::getPosition(){
    return position;
}


/**
 * M�todo p�blico de modifica��o da chave de identifica��o do robot
 * @param rKp   chave de identifica��o a atribuir ao robot
 */
void Robot::setRobotKey(int rKp){
    /* validar key, se menor <= zero ent�o atribui 0 */
    rKp > 0 ? robotKey = rKp : robotKey = 0;
}


/**
 * M�todo p�blico de modifica��o da capacidade de carga do robot
 * @param cCp   capacidade de carga do robot
 */
void Robot::setCargoCap(double cCp){
    /* validar capacidad de carga, tem que ser >= 0 */
    cCp > 0 ? cargoCap = cCp : cargoCap = 0;
}


/**
 * M�todo p�blico de modifica��o da quantidade de mat�ria-prima que o robot
 * transporta
 * @param cAp   quantidade de mat�ria-prima presente no robot
 */
void Robot::setCargoAvail(double cAp){
    /* validar mat�ria-prima dispon�vel, tem que ser > 0 e < que capacidade de
     carga (se exceder capacidade de carga fica igual a cargoCap) */
    if(cAp < 0)
        cargoAvail = 0;
    else if(cAp > getCargoCap())
        cargoAvail = getCargoCap();
    else
        cargoAvail = cAp;
}


/**
 * M�todo p�blico de modifica��o da posi��o do robot
 * @param pp    posi��o do robot
 */
void Robot::setPosition(int pp){
    pp > 0 ? position = pp : position = 0;
}

/**
 * M�todo p�blico que abastece um posto
 * @param qt    quantidade de stock a abastecer
 */
void Robot::supply(double qt){
    if(qt > 0)
     setCargoAvail(getCargoAvail()-qt);
}

/**
 * M�todo p�blico para receber abastecimento
 */
void Robot::getSupplies(){
    if(cargoAvail == 0)
        setCargoAvail(cargoCap); 
}

/**
 * M�todo de escrita, imprime no ecr� toda a informa��o sobre o robot,
 * nomeadamente a sua chave de identica��o, capacidade de carga de mat�ria-prima,
 * quantidade de mat�ria-prima que ainda tem dispon�vel e posi��o actual
 * @param out
 */
void Robot::write(ostream &out) const{
    cout << "\n---------------------------" << endl;
    cout << "Robot num: " << robotKey << endl;
    cout << "Capacidade de carga: " << cargoCap  << " kg" << endl;
    cout << "Carga disponivel: " << cargoAvail << " kg" << endl;
    cout << "Posicao actual: " << position << endl;
}


/**
 * sobrecarga de operador de compara��o, para verificar se dois robots
 * s�o iguais em termos de quantidade de mat�ria-prima dispon�vel
 * @param r     � a refer�ncia para um objecto do tipo ROBOT
 * @return      TRUE se tiverem a mesma quantidade de mat�ria-prima, caso
                contr�rio devolve FALSE
 */
bool Robot::operator == (const Robot &r) const{
    if(cargoAvail == r.cargoAvail)
        return true;
    else
        return false;
}


/**
 * sobrecarga do operador >, para verificar se a quantidade de mat�ria-prima presente
 * num robot � maior do que a de outro
 * @param r     � a refer�ncia para um objecto do tipo ROBOT
 * @return      TRUE se a quantidade de met�ria-prima dispon�vel f�r superior, caso
                contr�rio devolve FALSE
 */
bool Robot::operator > (const Robot &r) const{
    return (cargoAvail > r.cargoAvail);
}


/**
 * sobrecarga do operador de atribui��o = para atribuir, directamente, um objecto
 * do tipo ROBOT a outro
 * @param r     � a refer�ncia para um objecto do tipo ROBOT
 * @return      apontador para o objecto corrente
 */
const Robot & Robot::operator = (const Robot &r){
    setRobotKey(r.robotKey);
    setCargoCap(r.cargoCap);
    setCargoAvail(r.cargoAvail);
    setPosition(r.position);
    return *this;
}


/**
 * Sobrecarga do operador de stream out
 * @param out   refer�ncia do standard output
 * @param r     refer�ncia de um objecto do tipo ROBOT
 * @return      refer�ncia do standard output
 */
ostream &operator << (ostream &out, const Robot &r){
    r.write(out);
    return out;
}

ostream &operator << (ostream &out, const Robot *r){
    r->write(out);
    return out;
}

#endif	/* ROBOT_H */

