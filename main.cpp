/* Projecto ESINF - 2º ano LEI -ISEP
 *
 * Outubro 2012
 *
 * File:   Posto.h
 * Authors: João Carreira
 *
 * Created on October 16, 2012, 1:02 PM
 */

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
#include "DstTime.h"
#include "Dyn2DArray.h"
#include "Lista.h"
#include "Queue.h"



 /* Linked list of robots */
    Lista<Robot*> robots;

    /* Queue of postos */
    Queue<Posto*> postos;

    /* 2D Array of DstTime */
    Dyn2DArray <DstTime> distanciasTempos;

    /* Number of armazens */
    int armazensQT;

    /* Number of robots */
    int robotsQT;

    /* Number of automaticos */
    int automaticosQT;

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

    int showMenu();
    void runChoice(int choice);



int main(int argc, char** argv) {

    loadRobots();
    loadArmazens();
    loadAutomaticos();
    loadTimeDists();

    int choice;
    choice = showMenu();
    runChoice(choice);

    return 0;
}

/**
 * Runs the user's choice
 * @param choice
 */
void runChoice(int choice){


  switch(choice){

    case 1:
      cout << robots <<  endl;
      break;

    case 2:
      cout << postos << endl;
      break;

    case 3:
      cout << distanciasTempos << endl;
      break;

    case 4:
      cout << "A sair..." << endl;
      break;

    default:
      cout << "Escolha invalida!" << endl;
  }

}

/**
 * Shows a simple console menu
 * @return the choice
 */
int showMenu(){

      int choice = 0;

      cout << "Menu: \n" ;
      cout << " 1 - Listar robots\n" ;
      cout << " 2 - Listar postos\n" ;
      cout << " 3 - Listar tempos e distancias\n" ;
      cout << " 4 - Sair\n";
      cout << "\nEscolha a opcao: " << endl;
      cin >> choice;

  return choice;
}

/**
 * gets the quantity of armazens
 * @return quantity of armazens
 */
int getArmazensQT(){
    return armazensQT;
}

/**
 * sets the quantity of armazens
 * @param armQT quantity of armazens
 */
void setArmazensQT(int armQT){
    armazensQT = armQT;
}

/**
 * gets the quantity of armazens
 * @return quantity of armazens
 */
int getRobotsQT(){
    return robotsQT;
}

/**
 * sets the quantity of robots
 * @param rbtQT quantity of robots
 */
void setRobotsQT(int rbtQT){
    robotsQT = rbtQT;
}

/**
 * gets the quantity of automaticos
 * @return quantity of automaticos
 */
int getAutomaticosQT(){
    return automaticosQT;
}

/**
 * sets the quantity of automaticos
 * @param autQT quantity of automaticos
 */
void setAutomaticosQT(int autQT){
    automaticosQT = autQT;
}

/**
 * checks if the number of armazens is the same as the number of robots and if the number of automaticos is 2^armazens
 * @return true if it is a valid config
 */
// bool checkConfig(){
//     return(armazensQT == robotsQT || automaticosQT == pow(2,armazensQT));
// }

/**
 * Loads Armazens from file
 * @return 0 if successful or -1 if the file doesnt exist
 */
int loadArmazens() {
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
int loadAutomaticos(){
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
int loadRobots(){
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
int loadTimeDists(){
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

      DstTime a(distanceMeters,timeMinutes);
      
      // cout << keyPosto2 << endl;



      // distanciasTempos.insert(DstTime(10,1),0,3);
      // distanciasTempos.insert(DstTime(15,1),0,6);
      // distanciasTempos.insert(DstTime(10,1),1,5);
      // distanciasTempos.insert(DstTime(20,2),1,9);
      // distanciasTempos.insert(DstTime(10,1),2,9);
      // distanciasTempos.insert(DstTime(20,2),2,11);
      // distanciasTempos.insert(DstTime(10,1),3,4);
      // distanciasTempos.insert(DstTime(15,1),3,6);
      // distanciasTempos.insert(DstTime(10,1),4,5);
      // distanciasTempos.insert(DstTime(15,2),4,7);
      // distanciasTempos.insert(DstTime(10,1),5,8);
      // distanciasTempos.insert(DstTime(10,1),6,7);
      // distanciasTempos.insert(DstTime(15,2),6,11);
      // distanciasTempos.insert(DstTime(10,1),7,8);
      // distanciasTempos.insert(DstTime(10,1),7,11);
      // distanciasTempos.insert(DstTime(20,2),2,10);


      distanciasTempos.insert(a,keyPosto1,keyPosto2);
      // cout << "INSERIDO " << a << endl;

      }
 }

    fx4.close();
    return 0;
}
