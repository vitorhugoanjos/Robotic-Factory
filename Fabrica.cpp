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
#include <string.h>
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
#include "ListAdjGrafo.h"




/* Lista ligada de robots */
Lista<Robot*> robots;

/* Fila de espera de postos de trabalho */
Queue<Posto*> postos;

/* Matriz dinámica de distancias/tempos */
Dyn2DArray <DstTime> distanciasTempos;

// declarar grafo
ListAdjGrafo <Posto*, DstTime> grafo;

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

/* Protótipos do método construirGrafo */
void construirGrafo();

/* Protótipo do método validarGrafo */
bool validarGrafo();

/* Prototipo do método estadoFabrica */
void estadoFabrica();

/* Prototipo do metodo mostrarGrafo */
void mostrarGrafo();

/* Protótipos dos métodos abastecerAut e abastecerArm */
void abastecerAut(int pNum);
void abastecerArm(int pNum);

/* Prototipo para procuraRobot */
void procuraRobots(int v[], int numRobots);

/* Protótipos dos métodos que actualizam robots/postos/armazens */
void abastecerAutomatico(Automatico &a, Robot &r); 
void abastecerArmazem(Armazem &a, Robot &r); 
bool abastecerRobot(Armazem &a, Robot &r);




bool automaticoExiste(int key);

bool armazemExiste(int key);


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
  if(leuRobots && leuArmazens && leuAutomaticos){
    loadTimeDists();
    construirGrafo();
  }
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
	cout << endl;
	cout << endl;
    cout << "*****************************************" << endl;
    cout << "*                                       *" << endl;
    cout << "*           FABRICA ROBOTIZADA          *" << endl;
    cout << "*                                       *" << endl;
    cout << "*****************************************" << endl;
    cout << "*     Menu:                             *\n" ;
    cout << "*       1 - Listar robots               *\n" ;
    cout << "*       2 - Listar postos               *\n" ;
    cout << "*       3 - Listar tempos e distancias  *\n" ;
    cout << "*       4 - Mostrar grafo               *\n" ;
    cout << "*       5 - Ver estado da fabrica       *\n" ;
    cout << "*       6 - Abastecer Automatico        *\n" ;
    cout << "*       7 - Abastecer Armazem           *\n" ;
    cout << "*       8 - Sair                        *\n";
    cout << "*---------------------------------------*" << endl;
    cout << "*     Escolha a opcao:                  *\n";
    cout << "*                                       *" << endl;
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
        if(validarGrafo())
          mostrarGrafo();
        else
          cout << " >> Grafo invalido! Todos os postos automaticos tem que ser\n alcancaveis a partir de pelo menos um posto armazem\n e inicialmente cada posto armazem tem que ter um robot estacionado."<< endl;
      break;

    case 5:      
        estadoFabrica();
        break;

    case 6:
      int pNum;
      cout << "Abastecer o Automatico numero: ";
      cin >> pNum;
      
      if(!automaticoExiste(pNum))
        cout << "\n >> O posto automatico que escolheu nao existe!" << endl;
      else{
        cout << "\n >> A abastecer o posto automatico " << pNum << "...\n\n" << endl;
		abastecerAut(pNum);
		//estadoFabrica();
      }
      break;

    case 7:
      int pNumA;
      cout << "Abastecer o Armazem numero: ";
      cin >> pNumA;
      if(!armazemExiste(pNumA))
        cout << "\n >> O posto armazem que escolheu nao existe!" << endl;
      else{
        cout << "\n >> A abastecer o posto armazem " << pNumA << "...\n\n" << endl;
		abastecerArm(pNumA);
		//estadoFabrica();
      }
      break;

    case 8:
      cout << " >> A terminar programa..." << endl;
      sair = true;
	  break;

    default:
      cout << " >> Escolha invalida!" << endl;
    }
  }


}

bool automaticoExiste(int key){
  bool existe= false;
  Posto* tPosto;
  Automatico* tAutomatico;
  int cont = 0;

 while(cont < postos.comprimento()){
    postos.retira(tPosto);
    if(strcmp(typeid(*tPosto).name(), typeid(Automatico).name()) == 0 ){
        tAutomatico = dynamic_cast<Automatico*>(tPosto);
            if(tAutomatico->getKey() == key)
              existe = true;
        }
        postos.insere(tPosto);  
        cont++;
      }
  return existe;
}

bool armazemExiste(int key){
  bool existe= false;
  Posto* tPosto;
  Armazem* tArmazem;
  int cont = 0;

 while(cont < postos.comprimento()){

    postos.retira(tPosto);
    if(strcmp(typeid(*tPosto).name(), typeid(Armazem).name()) == 0 ){
        tArmazem = dynamic_cast<Armazem*>(tPosto);
            if(tArmazem->getKey() == key)
              existe = true;
        }
        postos.insere(tPosto);  
        cont++;
      }
  return existe;
}


/**
 * verifica se por cada n postos armazém devem existir 2^n postos automaticos, servidos por n robots.
 * @return true se por cada n postos armazém devem existir 2^n postos automaticos, servidos por n robots.
 */
bool checkConfig(){
    return(armazensQT == robotsQT && automaticosQT == pow((float)2,armazensQT));
}

/**
 * imprime o grafo
 */
void mostrarGrafo(){
  grafo.escreve_grafo();
}
/*
 * Método para gerar o grafo a partir dos objectos Posto guardados na queue (vértices do grafo) e a
 * partir do objectos DstTime guardardos na matriz dinâmica (ramos do grafo)
 */
void construirGrafo() {
  /* o ciclo while permite adicionar vértices automaticamente, com base nos objectos que estão
  na queue dos postos */
  // variável contadora inicializada a zero
  int cont = 0;
  // enquanto não se alcançar o comprimento total da fila
  while(cont < postos.comprimento()){
    // apontador temporário para objecto do tipo posto
    Posto *temp;
    // retira primeiro elemento da queue e guardar em temp
    postos.retira(temp);
    // temp é adicionado ao grafo como vértice
    grafo.juntar_vertice(temp);
    // volta a colocar o objecto na fila (vai para o fim da fila)
    postos.insere(temp);
    // incrementar cont para avaliar condição while
    cont++;
  }
  /* o cliclo for permite adicionar ramos automaticamente, com base nos objectos DstTime presentes
  na matriz dinâmica */
  /* objecto DstTime blank usado nas comparações dentro do ciclo,
  de forma a não retornar objectos construídos pelo construtor vazio */
  DstTime blank;
  /* percorrer a matriz dinâmica à procura de objectos DstTime */
  for(int i = 0; i <= distanciasTempos.getCap()-1; i++){
      for(int j = 0; j <= distanciasTempos.getCap()-1; j++){
          /* guardar em tempDt o objecto DstTime que está na posição i j */
          DstTime tempDt = distanciasTempos.returnElem(i,j);
          /* se objecto DstTime for diferente de blank, entao esse objecto
          vai ser usado para ser adicionado ao grafo */
          if(tempDt != blank){
              /* dois apontadores temporários para objectos do tipo Posto para procurar 
              Postos pela key respectiva (keys correspondem aos valores de i e j) */
              Vertice<Posto*,DstTime> *temp1 = grafo.encvert_keyPosto(i);
              Vertice<Posto*,DstTime> *temp2 = grafo.encvert_keyPosto(j);
              //adiciona ramo (objecto DstTime) entre os dois vértices (objectos Posto) encontrados 
              grafo.juntar_ramo(tempDt,temp1->GetConteudo(),temp2->GetConteudo());
          }
      }
  }
}

void abastecerAut(int x){
	// vai à lista de robots ver quantos robots existem na presente configuracao da fabrica
	int numRobots = robots.comprimento();
	// vector de inteiros para guardar as posiçoes dos robots
	int vecRobot[100];
	// procura onde estao os robots e guarda as suas posicoes no vector
	procuraRobots(vecRobot, numRobots);
	/* código que se segue permite encontrar um caminho entre o posto introduzido
	pelo utilizador e cada um dos postos onde se encontre o robot */
	// posto inicial (posto introduzido pelo utilizador
	Vertice<Posto*,DstTime> *inicial = grafo.encvert_keyPosto(x);
	// executa o algoritmo de procura caminho mais curto para cada robot que exista
	for(int i = 0; i < numRobots; i++){
		cout << "\nCaminho mais rapido a partir do robot estacionado no posto " << vecRobot[i] << endl;
		// o posto final é o posto onde se encontra o i-ésimo robot
		Vertice<Posto*,DstTime> *final = grafo.encvert_keyPosto(vecRobot[i]);
		grafo.caminhoMinimoPesadoAut(final->GetConteudo(),inicial->GetConteudo());
	}
	// pedir ao utilizador que escolha o robot
	cout << "\nIndique o robot que vai realizar o abastecimento do posto " << x << endl;
	int robot;
	bool control = false;
	cin >> robot;
	// validar num introduzido pelo utilizador
	for(int i = 0; i < numRobots; i++)
		if(robot == vecRobot[i])
			control = true;
	if(control == false)
		cout << "\nTem que introduzir um robot valido! Abastecimento nao realizado!" << endl;
	else{
		Posto *p;
		Automatico *a;
		int contP = 0;
		Robot *r;
		Robot *r2;
		int contR = 0;
		// procurar o armazem na queue, sem a modificar
		while(contP < postos.comprimento()){
			postos.retira(p);
			// guardar o armazem com chave procurada em *a
			if(p->getKey() == x){
				a = dynamic_cast<Automatico*>(p);
			}
			contP++;
			postos.insere(p);
		}
		// procurar robot na fila
		int cont1 = 1;
		while(cont1 <= robots.comprimento()){
			robots.encontra(cont1,r);
			if(r->getPosition() == robot)
				r2 = r; 
			cont1++;
		}
		// chamar método para abastecer
		abastecerAutomatico(*a,*r2);
		cout << "\nO posto " << x << " foi abastecido pelo robot que estava estacionado no posto " << robot << endl;
	} // end else
	
}

void abastecerArm(int x){
	// vai à lista de robots ver quantos robots existem na presente configuracao da fabrica
	int numRobots = robots.comprimento();
	// vector de inteiros para guardar as posiçoes dos robots
	int vecRobot[100];
	// procura onde estao os robots e guarda as suas posicoes no vector
	procuraRobots(vecRobot, numRobots);
	/* código que se segue permite encontrar um caminho entre o posto introduzido
	pelo utilizador e cada um dos postos onde se encontre o robot */
	// posto inicial (posto introduzido pelo utilizador
	Vertice<Posto*,DstTime> *inicial = grafo.encvert_keyPosto(x);
	// executa o algoritmo de procura caminho mais curto para cada robot que exista
	for(int i = 0; i < numRobots; i++){
		cout << "\nCaminho mais curto a partir do robot estacionado no posto " << vecRobot[i] << endl;
		// o posto final é o posto onde se encontra o i-ésimo robot
		Vertice<Posto*,DstTime> *final = grafo.encvert_keyPosto(vecRobot[i]);
		grafo.caminhoMinimoPesadoArm(final->GetConteudo(),inicial->GetConteudo());
	}
	// pedir ao utilizador que escolha o robot
	cout << "\nIndique o robot que vai realizar o abastecimento do posto " << x << endl;
	int robot;
	bool control = false;
	cin >> robot;
	// validar num introduzido pelo utilizador
	for(int i = 0; i < numRobots; i++)
		if(robot == vecRobot[i])
			control = true;
	if(control == false)
		cout << "\nTem que introduzir um robot valido! Abastecimento nao realizado!" << endl;
	else{
		Posto *p;
		Armazem *a;
		int contP = 0;
		Robot *r;
		Robot *r2;
		int contR = 0;
		// procurar o armazem na queue, sem a modificar
		while(contP < postos.comprimento()){
			postos.retira(p);
			// guardar o armazem com chave procurada em *a
			if(p->getKey() == x){
				a = dynamic_cast<Armazem*>(p);
			}
			contP++;
			postos.insere(p);
		}
		// procurar robot na fila
		int cont1 = 1;
		while(cont1 <= robots.comprimento()){
			robots.encontra(cont1,r);
			if(r->getPosition() == robot)
				r2 = r; 
			cont1++;
		}
		// chamar método para abastecer
		abastecerArmazem(*a,*r2);
		cout << "\nO posto " << x << " foi abastecido pelo robot que estava estacionado no posto " << robot << endl;
	} // end else
}



void procuraRobots(int v[], int n){
	// apontador do tipo robot para ir a fila de robots buscar a sua posicao
	Robot *tempRobot;
	// variavel contadora para controlar posicoes percorridas na lista de robots
	int cont = 0;
	// o numero de vezes que se acede a lista e igual ao núm de robots lá presentes
	while(cont < n){
		// remove-se o robot, ficando este no apontador tempRobot
		robots.remove(cont+1, tempRobot);
		// no vector de posicoes é guardada a respectiva posicao do robot
		v[cont] = tempRobot->getPosition();
		// o robot retirado anteriormente e colocado novamente na lisa, no mesmo local
		robots.insere(cont+1, tempRobot);
		// incrementa-se contador para passar ao robot seguinte (ou sair do ciclo)
		cont++;
	}
}

bool abastecerRobot(Armazem &a, Robot &r){
  Robot* pRobot = &r;
  Armazem* pArmazem = &a;
  pRobot->setPosition(pArmazem->getKey());
  if(pArmazem->getStock()-pArmazem->getSafety() >= pRobot->getCargoCap()){
    pRobot->setCargoAvail(pRobot->getCargoCap());
    pArmazem->setStock(pArmazem->getStock()-pRobot->getCargoCap());
    return true;
  }else{
    cout << "O armazem " << pArmazem->getKey() <<" nao tem stock suficiente para abastecer o robot " << pRobot->getRobotKey() << "." << endl;
    return false;
  }
}

void abastecerArmazem(Armazem &a, Robot &r){
   // isto aqui foi so para ter um armazem para poder testar
    Posto* tPosto;
    Armazem* tArmazem;
    Armazem* tArmazem2;
    int cont = 0;

    while(cont < postos.comprimento()){

    postos.retira(tPosto);
      if(strcmp(typeid(*tPosto).name(), typeid(Armazem).name()) == 0 ){
          tArmazem = dynamic_cast<Armazem*>(tPosto);
              if(tArmazem->getKey() == 0)
                tArmazem2=tArmazem;
          }
          postos.insere(tPosto);  
          cont++;
      }
    // acaba aqui 
    
  Robot * pRobot = &r;
  Armazem * pArmazem = &a;
  double resto;

  pRobot->setPosition(pArmazem->getKey());// robot viaja para este posto

  if(pRobot->getCargoAvail() >= pArmazem->getSafety()*3){ // se stock_robot >= stock_segurança * 3
    pRobot->setCargoAvail(pRobot->getCargoAvail()-pArmazem->getSafety()*3); // stock_robot -= stock_segurança * 3
    pArmazem->setStock(pArmazem->getStock()+pArmazem->getSafety()*3); // stock_armazem += stock_segurança * 3

    if(pRobot->getCargoAvail() == 0) // abastecer robot se tiver 0 de stock
      abastecerRobot(*tArmazem2,*pRobot);
  }else{

    resto = pArmazem->getSafety()*3;
    
    while(resto != 0){
      pArmazem->setStock(pArmazem->getStock()+pRobot->getCargoAvail()); // stock_armazem += stock_robot
      pRobot->setCargoAvail(0); // stock_robot = 0

      if(abastecerRobot(*tArmazem2,*pRobot)){ // stock_robot = full

        pRobot->setPosition(pArmazem->getKey()); // robot volta ao posto
        if((resto - pRobot->getCargoAvail()) < pRobot->getCargoAvail()){
          pArmazem->setStock(pArmazem->getStock()+(resto - pRobot->getCargoAvail())); // stock_armazem += (resto-stock_robot)
          resto = 0;
        }else{
          resto -= pRobot->getCargoAvail(); // resto -= stock_robot
        }
      }else{
        resto = 0;
        cout << "Nao ha materia-prima suficiente no armazem para abastecer este posto." << endl;
      }
    }
    estadoFabrica();
      }
    }

void abastecerAutomatico(Automatico &a , Robot &r){
    // isto aqui foi so para ter um armazem para poder testar
    Posto* tPosto;
    Armazem* tArmazem;
    Armazem* tArmazem2;
    int cont = 0;

    while(cont < postos.comprimento()){

    postos.retira(tPosto);
      if(strcmp(typeid(*tPosto).name(), typeid(Armazem).name()) == 0 ){
          tArmazem = dynamic_cast<Armazem*>(tPosto);
              if(tArmazem->getKey() == 0)
                tArmazem2=tArmazem;
          }
          postos.insere(tPosto);  
          cont++;
      }
    // acaba aqui 

  Robot * pRobot = &r;
  Automatico * pAutomatico = &a;
  double resto;

  pRobot->setPosition(pAutomatico->getKey()); // robot viaja para este posto

  if(pRobot->getCargoAvail() >= pAutomatico->getRequest()){ // se stock_robot >= stock_requesitado
    pRobot->setCargoAvail(pRobot->getCargoAvail()-pAutomatico->getRequest()); // stock_robot -= stock_requesitado
    pAutomatico->setStock(pAutomatico->getStock()+pAutomatico->getRequest()); // stock_automatico += stock_requesitado

    if(pRobot->getCargoAvail() == 0) // abastecer robot se tiver 0 de stock
      abastecerRobot(*tArmazem2, *pRobot);

  }else{
    resto = pAutomatico->getRequest();

    while(resto != 0){
      pAutomatico->setStock(pAutomatico->getStock()+pRobot->getCargoAvail()); // stock_automatico += stock_robot
      pRobot->setCargoAvail(0); // stock_robot = 0

      if(abastecerRobot(*tArmazem2, *pRobot)){ // stock_robot  = full

        pRobot->setPosition(pAutomatico->getKey()); // robot volta ao posto

        if((resto - pRobot->getCargoAvail()) < pRobot->getCargoAvail()){
          pAutomatico->setStock(pAutomatico->getStock()+(resto - pRobot->getCargoAvail())); // stock_automatico += (resto-stock_robot)
          resto = 0;
        }else{
          resto -= pRobot->getCargoAvail(); // resto -= stock_robot
        }
      }else{
        resto = 0;
        cout << "Nao ha materia-prima suficiente no armazem para abastecer este posto." << endl;
      }
    }

    estadoFabrica();
  }

}


void estadoFabrica(){

  Posto *tPosto;
  Armazem *tArmazem;
  Automatico *tAutomatico;
  Robot *tRobot;
  Robot *tRobot2;
  int cont = 0;
  bool temRobot = false;

  cout << "Estado da fabrica apos abastecimento:" << endl;
  cout << "\t Armazens: "<< endl;

  while(cont < postos.comprimento()){

    postos.retira(tPosto);
    if(strcmp(typeid(*tPosto).name(), typeid(Armazem).name()) == 0 ){
        tArmazem = dynamic_cast<Armazem*>(tPosto);
        cout << "\t\tArmazem num: " << tArmazem->getKey()  << "." << endl ;
        cout << "\t\tStock: " << tArmazem->getStock()  << "kg." << endl ;
        cout << "\t\tLimite de seguranca: " << tArmazem->getSafety() << "kg."  << endl ;
        cout << "\t\tRobot: ";

        int cont1 = 1;
        while(cont1 <= robots.comprimento()){
          robots.encontra(cont1,tRobot2);
          if(tRobot2->getPosition() == tArmazem->getKey())
            temRobot = true;
          cont1++;
        }
        if(temRobot){
          cout << "Tem robot estacionado neste posto."<< endl;
          temRobot = false;
        }else
          cout << "Nao tem robot estacionado neste posto."<< endl;
        cout << "\t\t-------------------------------------------" << endl;
    }
    postos.insere(tPosto);  
    cont++;
  }

  cont = 0;
  cout << "\n\t Automaticos: "<< endl;
  while(cont < postos.comprimento()){
    postos.retira(tPosto);
    if(strcmp(typeid(*tPosto).name(), typeid(Automatico).name()) == 0 ){
        tAutomatico = dynamic_cast<Automatico*>(tPosto);
        cout << "\t\tAutomatico num: " << tAutomatico->getKey()  << "." << endl ;
        cout << "\t\tStock: " << tAutomatico->getStock() << "kg."  << endl ;
        cout << "\t\tQuantidade requesitada: " << tAutomatico->getRequest() << "kg." << endl ;
        cout << "\t\tVelocidade de operacao: " << tAutomatico->getProcSpeed() << "kg/min." << endl ;
        cout << "\t\t--------------------------------" << endl;
    }
    postos.insere(tPosto);  
    cont++;
  }

  cont = 1;
  cout << "\n\t Robots: "<< endl;
  while(cont <= robots.comprimento()){
    robots.remove(cont, tRobot);
    cout << "\t\tRobot num: " << tRobot->getRobotKey()  << "." << endl ;
    cout << "\t\tQuantidade disponivel: " << tRobot->getCargoAvail()  << "kg." << endl ;
    cout << "\t\tQuantidade maxima: " << tRobot->getCargoCap() << "kg." << endl ;
    cout << "\t\tPosicao actual: ";
    int i = 0;
    while(i < postos.comprimento()){
      postos.retira(tPosto);
      if(tPosto->getKey() == tRobot->getPosition()){
        if(strcmp(typeid(*tPosto).name(),typeid(Armazem).name())== 0){
          cout << "Estacionado no armazem num: " << tRobot->getPosition() << "." << endl;
        }else{
          cout << "Estacionado no automatico num: " << tRobot->getPosition() << "." << endl;
        }
      }
      postos.insere(tPosto);
      i++;
    }
    cout << "\t\t-----------------------------------------------" << endl;
    robots.insere(cont, tRobot);
    cont++;
  }
}

/**
* verifica se todos os postos automáticos sao
* alcancaveis a partir de pelo menos um posto
* armazem e se inicialmente cada posto armazem
* tem um robot estacionado.
*/
bool validarGrafo(){
  
  bool temLigacao = true;
  bool temRobots = true;
  Posto *tPosto;
  Armazem *tArmazem;
  int cont = 0;

  while(cont < postos.comprimento()){
    Posto *temp;
    postos.retira(temp);
    if(!((grafo.grau_entrada(temp) >= 1) || (grafo.grau_saida(temp) >= 1))){
         temLigacao = false;
     }
    postos.insere(temp);
    cont++;
  }


  cont = 0;
  while(cont < postos.comprimento()){

    postos.retira(tPosto);
    if(strcmp(typeid(*tPosto).name(), typeid(Armazem).name()) == 0 ){
        tArmazem = dynamic_cast<Armazem*>(tPosto);
        if(tArmazem->getKey() != tArmazem->getRobot().getPosition()){
          temRobots = false;
        }
    }
    postos.insere(tPosto);
  
    cont++;
  }

return temLigacao && temRobots;
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