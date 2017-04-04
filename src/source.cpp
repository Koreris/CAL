/*
  * source.cpp
  *
  *  Created on: 29/03/2017
  *      Author: FranciscoSilva
  */

 #include <iostream>
 #include "Dados.h"
 #include "Graph.h"
 using namespace std;


int main(){

	GraphViewer *gv = new GraphViewer(600, 600, false);
	Dados *novo = new Dados(gv);

	novo->loadNodesFile();
	novo->loadStreetsFile();

	Graph<Coordenadas*> exp;
	novo->loadConnectorsFile(exp);

	getchar();

}
