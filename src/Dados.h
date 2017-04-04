/*
 * Dados.h
 *
 *  Created on: 29/03/2017
 *      Author: FranciscoSilva
 */
#include "Coordenadas.h"
#include "Estrada.h"
#include "Graph.h"
#include "includes.h"
#include "graphviewer.h"

#ifndef DADOS_H_
#define DADOS_H_

class Dados
{
	vector<Coordenadas*> coordsVec ;
	vector<Estrada*> streetsVec ;
	vector<Coordenadas*> hospitais;
	vector<Coordenadas*> bombeiros;
	GraphViewer *gv;
	long int streetids=0;

public:

	double distancia( Coordenadas* a, Coordenadas* b){
	       return sqrt( pow( a->getx()-b->getx(), 2 ) + pow( a->gety()-b->gety() ,2) );
	}

	Dados(GraphViewer *gv){
		this->gv = gv;
		gv->createWindow(1000, 800);

		gv->defineVertexColor("blue");

		gv->defineEdgeColor("black");
	};


	void setHospital(Coordenadas *h){this->hospitais.push_back(h);}
	vector<Coordenadas*> getHospitais(){
		return this->hospitais;
	}

	void setBombeiros(Coordenadas *h){this->bombeiros.push_back(h);}
	vector<Coordenadas*> getBombeiros(){
		return this->bombeiros;
	}

	void loadNodesFile(){
		ifstream in;
		string trans_string;
		long long int id;
		int xdeg, ydeg;
		stringstream is;
		string str;


		in.open("src/files/A.txt");
		if(!in.is_open()){
			cout <<"File A.txt couldn't be found\n";
			return;
		}

		while(getline(in, trans_string)){
			is.str(trans_string);
			getline(is, str, ';');
			id = stoll(str);

			getline(is, str, ';');
			xdeg = stoi(str);

			getline(is, str, ';');
			ydeg = stoi(str);


			Coordenadas * coord = new Coordenadas(id, xdeg, ydeg);

			if(id == 523 || id == 313 || id == 196)
				this->setHospital(coord);

			if(id == 434 || id == 758)
				this->setBombeiros(coord);

			//cout << coord->getId() << ";" << coord->getx() << ";" << coord->gety() << "\n";
			this->coordsVec.push_back(coord);

			is.ignore();
			is.clear();
		}

		in.close();

	}
	void loadStreetsFile(){
		ifstream in;
		string trans_string;
		long long int id;
		stringstream is;
		string str, nome;
		bool dsk;

		in.open("src/files/B.txt");
		if(!in.is_open()){
			cout <<"File B.txt couldn't be found\n";
			return;
		}

		while(getline(in, trans_string)){
			is.str(trans_string);
			getline(is, str, ';');
			id = stoll(str);

			getline(is, nome, ';');

			getline(is, str, ';');

			if (str == "True")
				dsk = true;
			else
				dsk = false;

			//cout << id << ";" << nome << ";" << str << "\n";
			this->streetsVec.push_back(new Estrada(id, nome, dsk));
			is.ignore();
			is.clear();
		}

		in.close();
	}

	Coordenadas* findCoord(long int c){
		for (unsigned int i = 0; i < this->coordsVec.size(); ++i) {
			if(this->coordsVec[i]->getId() == c)
				return this->coordsVec[i];
		}

		return NULL;
	}

	Estrada* findStreet(long int c){
		for (unsigned int i = 0; i < this->streetsVec.size(); ++i) {
			if(this->streetsVec[i]->getId() == c)
				return this->streetsVec[i];
		}

		return NULL;
	}

	void CreateNodes(Graph<Coordenadas*> &grf, long int streetid, long int nodeid, long int adjnodeid) {
		Coordenadas *A=this->findCoord(nodeid), *B=this->findCoord(adjnodeid);

		if(A != NULL && B != NULL){
			grf.addVertex(A);
			gv->addNode(nodeid, A->getx(), A->gety());
			grf.addVertex(B);
			gv->addNode(adjnodeid, B->getx(), B->gety());

			grf.addEdge(A,B, this->distancia(A,B)); // falta atribuir o peso (que será feito com base num algoritmo de calculo de distancia vs coordenadas)

			if(this->findStreet(streetid))
				gv->addEdge(this->streetids+=1,nodeid,adjnodeid,EdgeType::UNDIRECTED);
			else
				gv->addEdge(this->streetids+=1,nodeid,adjnodeid,EdgeType::DIRECTED);

//			if(grf.getVertex(A)->getadj().size() != 0){
//				cout << "\n \nAdjacente de " << grf.getVertex(A)->getInfo()->getId() << " :\n";
//				cout << grf.getVertex(A)->getadj()[0].getdest()->getInfo()->getId();
//			cout << "\n\n";}

			if(nodeid == 523 || nodeid == 313 || nodeid == 196)
				gv->setVertexColor(nodeid, "red");
			else if(adjnodeid == 523 || adjnodeid == 313 || adjnodeid == 196)
				gv->setVertexColor(adjnodeid, "red");

			if(nodeid == 434 || nodeid == 758)
				gv->setVertexColor(nodeid, "green");
			else if(adjnodeid == 434 || adjnodeid == 758)
				gv->setVertexColor(adjnodeid, "green");
		}
		else
			return;
	}

	void loadConnectorsFile(Graph<Coordenadas*> &grf){
			ifstream in;
			string trans_string;
			long long int streetid, nodeid, adjnodeid;
			stringstream is;
			string str, nome;

			in.open("src/files/C.txt");
			if(!in.is_open()){
				cout <<"File C.txt couldn't be found\n";
				return;
			}

			while(getline(in, trans_string)){
				is.str(trans_string);
				getline(is, str, ';');
				streetid = stoll(str);

				getline(is, str, ';');
				nodeid = stoll(str);

				getline(is, str, ';');
				adjnodeid = stoll(str);

				cout << streetid << ";" << nodeid << ";" << adjnodeid << "\n";

				CreateNodes(grf, streetid, nodeid, adjnodeid);

				is.ignore();
				is.clear();
			}
			gv->rearrange();
			in.close();
	}


	vector<Coordenadas*> getCoordsVec(){return this->coordsVec;}
	vector<Estrada*> getStreetsVec(){return this->streetsVec;}

};



#endif /* DADOS_H_ */
