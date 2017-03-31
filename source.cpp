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

Dados  novo ;

novo.loadNodesFile();
novo.loadStreetsFile();

Graph<Coordenadas*> exp  ;

novo.loadConnectorsFile(exp);

//for (int i = 0; i < novo.getCoordsVec().size(); i++)
//{
//	//cout << novo.getCoordsVec()[i]->getId() << endl;
//	}
//
//
//exp.addVertex(novo.getCoordsVec()[0]);
//exp.addVertex(novo.getCoordsVec()[1]);
//exp.addVertex(novo.getCoordsVec()[2]);
//
//
//Vertex<Coordenadas*> *no = exp.getVertex(novo.getCoordsVec()[1]);
//
//cout << exp.getVertexSet().size() << " nós inseridos" << endl;
//
//cout << "o id do segundo no e " << no->getInfo()->getId();


}
