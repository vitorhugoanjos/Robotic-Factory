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

using namespace std;

#include "Posto.h"
#include "Robot.h"
#include "Armazem.h"
#include "Automatico.h"
#include "Lista.h"
#include "Queue.h"
#include "Fabrica.h"


int showMenu();
void runChoice(int choice);

int main(int argc, char** argv) {

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

  Fabrica fabrica;

  switch(choice){

    case 1:
      cout << fabrica.getRobots() <<  endl;
      break;

    case 2:
      cout << fabrica.getPostos() << endl;
      break;

    case 3:
      cout << fabrica.getDstTimes() << endl;
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
