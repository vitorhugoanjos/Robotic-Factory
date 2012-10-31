/* Projecto ESINF - 2º ano LEI -ISEP
 *
 * Outubro 2012
 *
 * File:   Posto.h
 * Authors: Joao Carreira, Vitor Hugo Anjos
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



/* Lista ligada de robots */
Lista<Robot*> robots;

/* Fila de espera de postos de trabalho */
Queue<Posto*> postos;

/* Matriz dinámica de distancias/tempos */
Dyn2DArray <DstTime> distanciasTempos;

/* Quantidade de armazéns */
int armazensQT;

/* Quantidade de robots */
int robotsQT;

/* Quantidade de postos automáticos */
int automaticosQT;

/* Informa se foram lidos e inseridos robots na lista ligada */
bool leuRobots;

/* Informa se foram lidos e inseridos armazéns na fila de espera */
bool leuArmazens;

/* Informa se foram lidos e inseridos postos automáticos na fila de espera */
bool leuAutomaticos;

/* Informa se a configuração é válida */
bool isValid;

/* Protótipo do método init */
void init();

 /* Protótipo do método loadArmazens */
int loadArmazens();

/* Protótipo do método loadAutomaticos */
int loadAutomaticos();

/* Protótipo do método loadRobots */
int loadRobots();

/* Protótipo do método loadTimeDists */
int loadTimeDists();

/* Protótipo do método checkConfig */
bool checkConfig();

/* Protótipo do método showMenu */
void showMenu();


int main(int argc, char** argv) {

    init();

    if(isValid)
      showMenu();
    else
      cout << " >> Configuracao invalida, por cada n postos armazém devem existir 2^n postos automaticos, servidos por n robots." << endl;

    return 0;
}

/**
 * Chama os metodos responsaveis pela leitura dos ficheiros e verifica se os ficheiros foram lidos com sucesso de modo a evitar
 * falhas na leitura e insercao; Este metodo tambem verifica se a configuracao é valida.
 */
void init(){

  loadRobots();
  loadAutomaticos();
  if(leuRobots)
   loadArmazens();
  if(leuRobots && leuArmazens && leuAutomaticos)
   loadTimeDists();
  isValid = checkConfig();

}

/**
 * Mostra um menu no terminal e corre a opcao escolhida pelo utilizador, o menu
 * é controlado por uma condicao de saída.
 */
void showMenu(){



  bool sair = false;

  while(!sair){

    int choice = 0;
    cout << "*****************************************" << endl;
    cout << "*                                       *" << endl;
    cout << "*           FABRICA ROBOTIZADA          *" << endl;
    cout << "*                                       *" << endl;
    cout << "*****************************************" << endl;
    cout << "*     Menu:                             *\n" ;
    cout << "*       1 - Listar robots               *\n" ;
    cout << "*       2 - Listar postos               *\n" ;
    cout << "*       3 - Listar tempos e distancias  *\n" ;
    cout << "*       4 - Sair                        *\n";
    cout << "*     Escolha a opcao:                  *\n";
    cout << "*                                       *" << endl;
    cout << "*****************************************" << endl;
    cin >> choice;


    switch(choice){

    case 1:
      if(leuRobots)
       cout << robots <<  endl;
      else
        cout << " >> Nao leu o ficheiro de robots!" << endl;
      break;

    case 2:
      if(leuRobots && leuArmazens && leuAutomaticos)
       cout << postos << endl;
      else
        cout << " >> Nao leu os ficheiros necessarios!" << endl;
      break;

    case 3:
      if(leuRobots && leuArmazens && leuAutomaticos)
        cout << distanciasTempos << endl;
      else
        cout << " >> Nao leu os ficheiros necessarios!" << endl;
      break;

    case 4:
      cout << " >> A terminar programa..." << endl;
      sair = true;
      break;

    default:
      cout << " >> Escolha inválida!" << endl;
    }
  }


}


/**
 * verifica se por cada n postos armazém devem existir 2^n postos automaticos, servidos por n robots.
 * @return true se por cada n postos armazém devem existir 2^n postos automaticos, servidos por n robots.
 */
bool checkConfig(){
    return(armazensQT == robotsQT && automaticosQT == pow((float)2,armazensQT));
}

/**
 * Lê o ficheiro que tem informações sobre os armazéns e insere os armazéns na fila de espera.
 * @return false se o ficheiro nao existir, true caso o ficheiro exista.
 */
int loadArmazens() {
   int lineNumber = 1;
   int quantity;
   int key;
   int robotKey;
   double stock;
   double safety;
   string line;

   ifstream fx1("FX1.csv"); /* abre o ficheiro */

   if(!fx1){
    cout << "FX1.csv nao existe!"<< endl;
   return -1;
   }

  while(!fx1.eof()){ /* enquanto nao chega ao final do ficheiro */
      getline(fx1,line,'\n'); /* grava o conteúdo da linha */
      if(line.size() > 0 ) {

        if(lineNumber==1){

            quantity = atoi(line.c_str()); /* quantidade ( armazenada na primeira linha do ficheiro ) */
            armazensQT = quantity;
            lineNumber++;

        }else{

        /* guarda o conteúdo entre linhas, auxiliado por duas variaveis indice, begin e pos */

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
        robots.encontra(robotKey, apRobot); // encontra o robot que tem a robot key igual à armazenada na variavel robotKey
        postos.insere(new Armazem(key,stock,safety,*apRobot)); // insere o armazém na lista de espera
    }
      }
 }

    fx1.close();
    leuArmazens = true; /* leu com sucesso*/
    return 0;
}


/**
 * Lê o ficheiro que tem informações sobre os postos automáticos e insere os postos automáticos na fila de espera.
 * @return false se o ficheiro nao existir, true caso o ficheiro exista.
 */
int loadAutomaticos(){
   int key;
   int index= 1;
   double stock;
   double request;
   double procSpeed;
   string line;


   ifstream fx2("FX2.csv"); /* abre o ficheiro */

   if(!fx2){
    cout << "FX2.csv nao existe!"<< endl;
   return -1;
   }

  while(!fx2.eof()){ /* enquanto nao chega ao final do ficheiro */
      getline(fx2,line,'\n'); /* grava o conteúdo da linha */
      if(line.size() > 0 ) {


        /* guarda o conteúdo entre linhas, auxiliado por duas variaveis indice, begin e pos */

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
    automaticosQT = index-1;
    fx2.close();
    leuAutomaticos = true; /* leu com sucesso*/
    return 0;
}


/**
 * Lê o ficheiro que tem informações sobre os robots e insere os robots na lista ligada.
 * @return false se o ficheiro nao existir, true caso o ficheiro exista.
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

  while(!fx3.eof()){ /* enquanto nao chega ao final do ficheiro */
      getline(fx3,line,'\n'); /* grava o conteúdo da linha */
      if(line.size() > 0 ) {

         /* guarda o conteúdo entre linhas, auxiliado por duas variaveis indice, begin e pos */

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



        robots.insere(index, new Robot(key,cargoCap,cargoAvail, position)); // insere o armazém na lista ligada
        index++;


      }
 }
    robotsQT=index-1;
    fx3.close();
    leuRobots = true; /* leu com sucesso*/
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
    double timeMinutes;
    string line;


   ifstream fx4("FX4.csv"); /* abre o ficheiro */

   if(!fx4){
    cout << "FX4.csv nao existe!"<< endl;
   return -1;
   }

  while(!fx4.eof()){ /* enquanto nao chega ao final do ficheiro */
      getline(fx4,line,'\n'); /* grava o conteúdo da linha */
      if(line.size() > 0 ) {

         /* guarda o conteúdo entre linhas, auxiliado por duas variaveis indice, begin e pos */

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

        distanciasTempos.insert(DstTime(distanceMeters,timeMinutes),keyPosto1,keyPosto2); // insere o armazém na matriz dinámica

      }
 }

    fx4.close();
    return 0;
}
