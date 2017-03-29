/*
 * source.cpp
 *
 *  Created on: 29/03/2017
 *      Author: FranciscoSilva
 */

#include <iostream>
#include "Dados.h"
using namespace std;


int main(){
 Dados d;

 d.loadNodesFile();

 cout << "\n\n";

 d.loadStreetsFile();

}
