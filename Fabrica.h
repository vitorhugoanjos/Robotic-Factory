#ifndef FABRICA_H
#define FABRICA_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <typeinfo>

using namespace std;

#include "Posto.h"
#include "Robot.h"
#include "Armazem.h"
#include "Automatico.h"
#include "Lista.h"
#include "Queue.h"
#include "DstTime.h"
#include "Dyn2DArray.h"

class Fabrica {

private:

    /* Linked list of robots */
    Lista<Robot*> robots;

    /* Queue of postos */
    Queue<Posto*> postos;

    Dyn2DArray<DstTime> aDstTime;

    /* Number of armazens */
    int armazensQT;

    /* Number of robots */
    int robotsQT;

    /* Number of automaticos */
    int automaticosQT;

public:

    /* protótipos de construtopres e destrutor */
    Fabrica();
    ~Fabrica();

    /* load from files */
    int loadArmazens();
    int loadAutomaticos();
    int loadRobots();
    int loadTimeDists();

    /* GETS SETS */
    int getArmazensQT();
    void setArmazensQT(int armQT);

    int getRobotsQT();
    void setRobotsQT(int rbtQT);

    int getAutomaticosQT();
    void setAutomaticosQT(int autQT);

    bool checkConfig();

    Lista<Robot*> getRobots();
    Queue<Posto*> getPostos();
    Dyn2DArray<DstTime> getDstTimes();
};

Fabrica::Fabrica() {
    loadRobots();
    loadArmazens();
    loadAutomaticos();
    loadTimeDists();
}

Fabrica::~Fabrica(){}


/**
 * gets the quantity of armazens
 * @return quantity of armazens
 */
int Fabrica::getArmazensQT(){
    return armazensQT;
}

/**
 * sets the quantity of armazens
 * @param armQT quantity of armazens
 */
void Fabrica::setArmazensQT(int armQT){
    armazensQT = armQT;
}

/**
 * gets the quantity of armazens
 * @return quantity of armazens
 */
int Fabrica::getRobotsQT(){
    return robotsQT;
}

/**
 * sets the quantity of robots
 * @param rbtQT quantity of robots
 */
void Fabrica::setRobotsQT(int rbtQT){
    robotsQT = rbtQT;
}

/**
 * gets the quantity of automaticos
 * @return quantity of automaticos
 */
int Fabrica::getAutomaticosQT(){
    return automaticosQT;
}

/**
 * sets the quantity of automaticos
 * @param autQT quantity of automaticos
 */
void Fabrica::setAutomaticosQT(int autQT){
    automaticosQT = autQT;
}

/**
 * returns a list of robots
 * @return list of robots
 */
Lista<Robot*> Fabrica::getRobots(){
    return robots;
}


/**
 * returns a list of robots
 * @return list of robots
 */
Queue<Posto*> Fabrica::getPostos(){
    return postos;
}

Dyn2DArray<DstTime> Fabrica::getDstTimes(){
    return aDstTime;
}


/**
 * checks if the number of armazens is the same as the number of robots and if the number of automaticos is 2^armazens
 * @return true if it is a valid config
 */
bool Fabrica::checkConfig(){
    return(armazensQT == robotsQT || automaticosQT == pow(2,armazensQT));
}

/**
 * Loads Armazens from file
 * @return 0 if successful or -1 if the file doesnt exist
 */
int Fabrica::loadArmazens() {
   int lineNumber = 1;
   int quantity;
   int key;
   int robotKey; /* suponho que é pela key do robot que vamos buscar o robot associado */
   double stock;
   double safety;
   string line;


   ifstream fx1("FX1.csv"); /* opens the file */

   if(!fx1){
    cout << "FX1.csv nao existe!"<< endl;
   return -1;
   }

  while(!fx1.eof()){ /* while it doesnt reach the end of the file */
      getline(fx1,line,'\n'); /* the content of the line is saved */
      if(line.size() > 0 ) {

        if(lineNumber==1){

            quantity = atoi(line.c_str()); /* quantity ( stored in the first row) */
            setArmazensQT(quantity);
            lineNumber++;

        }else{

        /* gets the content between commas, uses two 10 indexes variables to keep track of the position */

        int begin = 0;
        int pos = line.find(',',begin);


        string key_tmp(line.substr(begin,pos-begin));
        char* aux = &key_tmp[0];
        key= atoi(aux);


        pos++;
        begin = pos;
        pos = line.find(',',begin);

        string stock_tmp(line.substr(begin,pos-begin));
        aux = &stock_tmp[0];
        stock= atof(aux);


        pos++;
        begin = pos;
        pos = line.find(',', begin);

        string safety_tmp(line.substr(begin, pos-begin));
        aux = &safety_tmp[0];
        safety= atof(aux);


        pos++;
        begin = pos;
        pos = line.find(',', begin);


        string robotKey_tmp(line.substr(begin, pos-begin));
        aux = &robotKey_tmp[0];
        robotKey= atof(aux);

        pos++;

        Robot auxRobot;
        Robot *apRobot = &auxRobot;
        robots.encontra(robotKey, apRobot); // encontra o robot que tem a robot key armazenada na variavel robotKey
        postos.insere(new Armazem(key,stock,safety,*apRobot));
    }
      }
 }

    fx1.close();
    return 0;
}


/**
 * Loads Automaticos from file
 * @return 0 if successful or -1 if the file doesnt exist
 */
int Fabrica::loadAutomaticos(){
   int key;
   int index= 1;
   double stock;
   double request;
   double procSpeed;
   string line;


   ifstream fx2("FX2.csv"); /* opens the file */

   if(!fx2){
    cout << "FX2.csv nao existe!"<< endl;
   return -1;
   }

  while(!fx2.eof()){ /* while it doesnt reach the end of the file */
      getline(fx2,line,'\n'); /* the content of the line is saved */
      if(line.size() > 0 ) {


        /* gets the content between commas, uses two indexes variables to keep track of the position */

        int begin = 0;
        int pos = line.find(',',begin);


        string key_tmp(line.substr(begin,pos-begin));
        char* aux = &key_tmp[0];
        key= atoi(aux);


        pos++;
        begin = pos;
        pos = line.find(',',begin);

        string stock_tmp(line.substr(begin,pos-begin));
        aux = &stock_tmp[0];
        stock= atof(aux);


        pos++;
        begin = pos;
        pos = line.find(',', begin);

        string request_tmp(line.substr(begin, pos-begin));
        aux = &request_tmp[0];
        request= atof(aux);


        pos++;
        begin = pos;
        pos = line.find(',', begin);


        string procSpeed_tmp(line.substr(begin, pos-begin));
        aux = &procSpeed_tmp[0];
        procSpeed= atof(aux);

        pos++;

        index++;

        postos.insere(new Automatico(key,stock,request,procSpeed));



      }
 }
    setAutomaticosQT(index-1);
    fx2.close();
    return 0;
}


/**
 * Loads Robots from file
 * @return 0 if successful or -1 if the file doesnt exist
 */
int Fabrica::loadRobots(){
    int index= robots.comprimento()+1;
    int key;
    double cargoCap;
    double cargoAvail;
    int position;
    string line;

   ifstream fx3("FX3.csv"); /* opens the file */

   if(!fx3){
    cout << "FX3.csv nao existe!"<< endl;
   return -1;
   }

  while(!fx3.eof()){ /* while it doesnt reach the end of the file */
      getline(fx3,line,'\n'); /* the content of the line is saved */
      if(line.size() > 0 ) {

        /* gets the content between commas, uses two indexes variables to keep track of the position */

        int begin = 0;
        int pos = line.find(',',begin);


        string key_tmp(line.substr(begin,pos-begin));
        char* aux = &key_tmp[0];
        key= atoi(aux);


        pos++;
        begin = pos;
        pos = line.find(',',begin);

        string cargoCap_tmp(line.substr(begin,pos-begin));
        aux = &cargoCap_tmp[0];
        cargoCap= atof(aux);


        pos++;
        begin = pos;
        pos = line.find(',', begin);

        string cargiAvail_tmp(line.substr(begin, pos-begin));
        aux = &cargiAvail_tmp[0];
        cargoAvail= atof(aux);


        pos++;
        begin = pos;
        pos = line.find(',', begin);


        string position_tmp(line.substr(begin, pos-begin));
        aux = &position_tmp[0];
        position= atoi(aux);

        pos++;



        robots.insere(index, new Robot(key,cargoCap,cargoAvail, position));
        index++;


      }
 }
    setRobotsQT(index-1);
    fx3.close();
    return 0;
}


/**
 * Loads TimeDist from file
 * @return 0 if successful or -1 if the file doesnt exist
 */
int Fabrica::loadTimeDists(){
    int keyPosto1;
    int keyPosto2;
    double distanceMeters;
    double timeMinutes; /* time é palavra reservada do c++ pelos vistos */
    string line;


   ifstream fx4("FX4.csv"); /* opens the file */

   if(!fx4){
    cout << "FX4.csv nao existe!"<< endl;
   return -1;
   }

  while(!fx4.eof()){ /* while it doesnt reach the end of the file */
      getline(fx4,line,'\n'); /* the content of the line is saved */
      if(line.size() > 0 ) {

        int begin = 0;
        int pos = line.find(',',begin);


        string keyPosto1_tmp(line.substr(begin,pos-begin));
        char* aux = &keyPosto1_tmp[0];
        keyPosto1= atoi(aux);


        pos++;
        begin = pos;
        pos = line.find(',',begin);

        string keyPosto2_tmp(line.substr(begin,pos-begin));
        aux = &keyPosto2_tmp[0];
        keyPosto2= atoi(aux);


        pos++;
        begin = pos;
        pos = line.find(',',begin);

        string distanceMeters_tmp(line.substr(begin,pos-begin));
        aux = &distanceMeters_tmp[0];
        distanceMeters= atof(aux);


        pos++;
        begin = pos;
        pos = line.find(',', begin);

        string timeMinutes_tmp(line.substr(begin, pos-begin));
        aux = &timeMinutes_tmp[0];
        timeMinutes= atof(aux);


        pos++;

        //cout << "KEY_POSTO1: "<< keyPosto1 << " KEY_POSTO2: " << keyPosto2 << " DISTANCE: " << distanceMeters << " TIME: "  << timeMinutes << endl;

       aDstTime.insertRC(DstTime(distanceMeters,timeMinutes), keyPosto1, keyPosto2);


      }
 }

    fx4.close();

    return 0;
}


#endif