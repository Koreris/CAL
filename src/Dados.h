/*
 * Dados.h
 *
 *  Created on: 29/03/2017
 *      Author: FranciscoSilva
 */
#include "Coordenadas.h"
#include "Estrada.h"
#include "includes.h"
#include "Graph.h"
#include "Haversine.h"

#ifndef DADOS_H_
#define DADOS_H_

class Dados
{
	vector<Coordenadas*> coordsVec ;
	vector<Estrada*> streetsVec ;

public:
	Dados (){

	};

	void loadNodesFile(){
		ifstream in;
		string trans_string;
		long long int id;
		double xdeg, ydeg, xrad, yrad;
		stringstream is;
		string str;


		in.open("src/files/A.txt");

		while(getline(in, trans_string)){
			is.str(trans_string);
			getline(is, str, ';');
			id = stoll(str);
			//coord->setId(id);

			getline(is, str, ';');
			xdeg = stod(str);
			//coord->setxDegrees(xdeg);

			getline(is, str, ';');
			ydeg = stod(str);
			//coord->setyDegrees(ydeg);

			getline(is, str, ';');
			xrad = stod(str);
			//coord->setxRad(xrad);

			getline(is, str, ';');
			yrad = stod(str);
			//coord->setyRad(yrad);

			//cout << id << ";" << xdeg << ";" << ydeg << ";" << xrad << ";" << yrad << "\n";
			Coordenadas * coord = new Coordenadas(id, xdeg, ydeg, xrad, yrad);
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

			cout << id << ";" << nome << ";" << str << "\n";
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
			grf.addVertex(B);

			grf.addEdge(A,B, distanceEarth(A->getxDegrees(), A->getyDegrees(), B->getxDegrees(), B->getyDegrees())); // falta atribuir o peso (que será feito com base num algoritmo de calculo de distancia vs coordenadas)
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

			in.open("files/C.txt");


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
	}


	vector<Coordenadas*> getCoordsVec(){return this->coordsVec;}
	vector<Estrada*> getStreetsVec(){return this->streetsVec;}

};



#endif /* DADOS_H_ */
