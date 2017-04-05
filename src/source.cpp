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
	int i = 0, j = 0;

	GraphViewer *gv = new GraphViewer(600, 600, false);
	Dados *novo = new Dados(gv);

	novo->loadNodesFile();
	novo->loadStreetsFile();

	Graph<Coordenadas*> exp;

	novo->loadConnectorsFile(exp);


	/*Pinta a Amarelo o Trajeto mais curto entre quaisquer dois pontos do grafo*/

	novo->dijkstraAnimation(exp, 120, 122);

	/*Pinta a Amarelo o Trajeto mais curto entre quaisquer dois pontos do grafo*/


	getchar();

}
