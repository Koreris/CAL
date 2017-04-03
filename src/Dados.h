/*
 * Dados.h
 *
 *  Created on: 29/03/2017
 *      Author: FranciscoSilva
 */
#include "Coordenadas.h"
#include "Estrada.h"
#include "Graph.h"
#include "Haversine.h"
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
		double xdeg, ydeg, xrad, yrad;
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
			xdeg = stod(str);

			getline(is, str, ';');
			ydeg = stod(str);

			getline(is, str, ';');
			xrad = stod(str);

			getline(is, str, ';');
			yrad = stod(str);

			Coordenadas * coord = new Coordenadas(id, xdeg, ydeg, xrad, yrad);

			if(id == 4378186376 || id == 1724272859 || id == 3573235293)
				this->setHospital(coord);

			if(id == 3116927841 || id == 3570149421)
				this->setBombeiros(coord);

			//cout << coord->getId() << ";" << coord->getxDegrees() << ";" << coord->getyDegrees() << ";" << coord->getxRad()<< ";" << coord->getyRad() << "\n";
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
	}

	Coordenadas* findCoord(long long c){
		for (int i = 0; i < this->coordsVec.size(); ++i) {
			if(this->coordsVec[i]->getId() == c)
				return this->coordsVec[i];
		}

		return NULL;
	}

	void CreateNodes(Graph<Coordenadas*> &grf, long long int streetid, long long int nodeid, long long int adjnodeid) {
		Coordenadas *A=this->findCoord(nodeid), *B=this->findCoord(adjnodeid);

		if(A != NULL && B != NULL){
			grf.addVertex(A);
			gv->addNode(nodeid);
			grf.addVertex(B);
			gv->addNode(adjnodeid);

			grf.addEdge(A,B, distanceEarth(A->getxDegrees(), A->getyDegrees(), B->getxDegrees(), B->getyDegrees())); // falta atribuir o peso (que será feito com base num algoritmo de calculo de distancia vs coordenadas)

			gv->addEdge(this->streetids+=1,nodeid,adjnodeid,EdgeType::UNDIRECTED);

			if(grf.getVertex(A)->getadj().size() != 0){
				cout << "\n \nAdjacente de " << grf.getVertex(A)->getInfo()->getId() << " :\n";
				cout << grf.getVertex(A)->getadj()[0].getdest()->getInfo()->getId();
			cout << "\n\n";}
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
	}


	vector<Coordenadas*> getCoordsVec(){return this->coordsVec;}
	vector<Estrada*> getStreetsVec(){return this->streetsVec;}

};



#endif /* DADOS_H_ */
