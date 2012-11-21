/* Projecto ESINF - 2º ano LEI -ISEP
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
 * @author João Carreira, Vitor Hugo Anjos
 * @version: 1.0 (Oct 2012)
 */
class Robot{
private:
    /* chave de identificação do robot (inteiro > 0, única entre robots
    mas distinta dos postos) */
    int robotKey;
    /* capacidade de carga do robot (kg) */
    double cargoCap;
    /* matéria-prima disponível no robot (kg) */
    double cargoAvail;
    /* posição em que o robot se econtra (corresponde à key do posto) */
    int position;

public:
    /* protótipos de construtores e destrutor */
    Robot();
    Robot(int rKp, double cCp, double cAp, int pp);
    Robot(const Robot &r);
    ~Robot();

    /* protótipos de GETS e SETS */
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

    /* sobrecarga de operadores de comparação */
    bool operator == (const Robot &e) const;
    bool operator > (const Robot &r) const;

    /* sobrecarga do operadtor de atribuição */
    const Robot &operator = (const Robot &r);

    /* sobrecarga do operador de stream out */
    void write(ostream &ostr) const;
};


/**
 * Construtor sem parâmetros, cria um robot com todos os seus parâmetros a zero,
 * nomeadamente a sua chave, capacidade de carga, matéria-prima disponível e
 * posição
 */
Robot::Robot(){
    setRobotKey(0);
    setCargoCap(0);
    setCargoAvail(0);
    setPosition(0);
}


/**
 * Construtor com parâmetros: cria um objecto do tipo ROBOT, com os parâmetros robotKey,
 * cargoCap, cargoAvail e position
 * @param rkp   é a chava a atribuir ao robot
 * @param cCp   é quantidade de matéria-prima capaz de transportar
 * @param cAp   é a quantidade de matéria-prima que tem disponível
 * @param pp    é a posição em que o robot se encontra
 */
Robot::Robot(int rKp, double cCp, double cAp, int pp){
    setRobotKey(rKp);
    setCargoCap(cCp);
    setCargoAvail(cAp);
    setPosition(pp);
}


/**
 * Construtor cópia: cria uma cópia de um objecto do tipo ROBOT, passado por
 * referência
 * @param r     é a referência do objecto do tipo ROBOT (declarada como const de
 *              forma a que o objecto copiado não sofra alterações)
 */
Robot::Robot(const Robot &r){
    robotKey = r.robotKey;
    cargoCap = r.cargoCap;
    cargoAvail = r.cargoAvail;
    position = r.position;
}


/**
 * Destrutor para objectos do tipo POSTO (sem definição)
 */
Robot::~Robot(){

}


/**
 * Método de acesso público à chave de identificação do robot
 * @return      chave de identificação do robot
 */
int Robot::getRobotKey(){
    return robotKey;
}

/**
 * Método de acesso público à capacidade de carga do robot
 * @return      capacidade de carga do robot
 */
double Robot::getCargoCap(){
    return cargoCap;
}


/**
 * Método de acesso público à quantidade de matéria-prima que o robot ainda
 * tem disponível
 * @return      quantidade de matéria-prima disponível
 */
double Robot::getCargoAvail(){
    return cargoAvail;
}


/**
 * Método de acesso público à localização actual do robot
 * @return      posição do robot
 */
int Robot::getPosition(){
    return position;
}


/**
 * Método público de modificação da chave de identificação do robot
 * @param rKp   chave de identificação a atribuir ao robot
 */
void Robot::setRobotKey(int rKp){
    /* validar key, se menor <= zero então atribui 0 */
    rKp > 0 ? robotKey = rKp : robotKey = 0;
}


/**
 * Método público de modificação da capacidade de carga do robot
 * @param cCp   capacidade de carga do robot
 */
void Robot::setCargoCap(double cCp){
    /* validar capacidad de carga, tem que ser >= 0 */
    cCp > 0 ? cargoCap = cCp : cargoCap = 0;
}


/**
 * Método público de modificação da quantidade de matéria-prima que o robot
 * transporta
 * @param cAp   quantidade de matéria-prima presente no robot
 */
void Robot::setCargoAvail(double cAp){
    /* validar matéria-prima disponível, tem que ser > 0 e < que capacidade de
     carga (se exceder capacidade de carga fica igual a cargoCap) */
    if(cAp < 0)
        cargoAvail = 0;
    else if(cAp > getCargoCap())
        cargoAvail = getCargoCap();
    else
        cargoAvail = cAp;
}


/**
 * Método público de modificação da posição do robot
 * @param pp    posição do robot
 */
void Robot::setPosition(int pp){
    pp > 0 ? position = pp : position = 0;
}

/**
 * Método público que abastece um posto
 * @param qt    quantidade de stock a abastecer
 */
void Robot::supply(double qt){
    if(qt > 0)
     setCargoAvail(getCargoAvail()-qt);
}

/**
 * Método público para receber abastecimento
 */
void Robot::getSupplies(){
    if(cargoAvail == 0)
        setCargoAvail(cargoCap); 
}

/**
 * Método de escrita, imprime no ecrã toda a informação sobre o robot,
 * nomeadamente a sua chave de identicação, capacidade de carga de matéria-prima,
 * quantidade de matéria-prima que ainda tem disponível e posição actual
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
 * sobrecarga de operador de comparação, para verificar se dois robots
 * são iguais em termos de quantidade de matéria-prima disponível
 * @param r     é a referência para um objecto do tipo ROBOT
 * @return      TRUE se tiverem a mesma quantidade de matéria-prima, caso
                contrário devolve FALSE
 */
bool Robot::operator == (const Robot &r) const{
    if(cargoAvail == r.cargoAvail)
        return true;
    else
        return false;
}


/**
 * sobrecarga do operador >, para verificar se a quantidade de matéria-prima presente
 * num robot é maior do que a de outro
 * @param r     é a referência para um objecto do tipo ROBOT
 * @return      TRUE se a quantidade de metéria-prima disponível fôr superior, caso
                contrário devolve FALSE
 */
bool Robot::operator > (const Robot &r) const{
    return (cargoAvail > r.cargoAvail);
}


/**
 * sobrecarga do operador de atribuição = para atribuir, directamente, um objecto
 * do tipo ROBOT a outro
 * @param r     é a referência para um objecto do tipo ROBOT
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
 * @param out   referência do standard output
 * @param r     referência de um objecto do tipo ROBOT
 * @return      referência do standard output
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

