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
 Dados d;

 d.loadNodesFile();

 cout << "\n\n";

 d.loadStreetsFile();



Dados novo;

Graph<Coordenadas*> exp  ;

cout << novo.getCoordsVec()[1]->getId() << endl;


	//cout << novo.getCoordsVec().size() << endl;



/*
exp.addVertex(novo.getCoordsVec().at(0));
exp.addVertex(novo.getCoordsVec()[1]);
exp.addVertex(novo.getCoordsVec()[2]);*/



//Vertex<Coordenadas*> *no = exp.getVertex(novo.getCoordsVec()[1]);

//cout << exp.getVertexSet().size() << endl;
//cout << no->getInfo()->getId();




}
