/*
 * Dados.h
 *
 *  Created on: 29/03/2017
 *      Author: FranciscoSilva
 */
#include "Coordenadas.h"
#include "Estrada.h"
#include "includes.h"

#ifndef DADOS_H_
#define DADOS_H_

class Dados
{
	vector<Coordenadas> coordsVec ;
	vector<Estrada> streetsVec ;

public:
	Dados (){};

	void loadNodesFile(){
		ifstream in;
		string trans_string;
		long long int id;
		double xdeg, ydeg, xrad, yrad;
		stringstream is;
		string str;
		Coordenadas coord;

		in.open("files/A.txt");


		while(getline(in, trans_string)){
			is.str(trans_string);
			getline(is, str, ';');
			id = stoll(str);
			coord.setId(id);

			getline(is, str, ';');
			xdeg = stod(str);
			coord.setxDegrees(xdeg);

			getline(is, str, ';');
			ydeg = stod(str);
			coord.setyDegrees(ydeg);

			getline(is, str, ';');
			xrad = stod(str);
			coord.setxRad(xrad);

			getline(is, str, ';');
			yrad = stod(str);
			coord.setyRad(yrad);

			cout << id << ";" << xdeg << ";" << ydeg << ";" << xrad << ";" << yrad << "\n";
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
		Estrada est;

		in.open("files/B.txt");


		while(getline(in, trans_string)){
			is.str(trans_string);
			getline(is, str, ';');
			id = stoll(str);
			est.setId(id);

			getline(is, nome, ';');
			est.setNome(nome);

			getline(is, str, ';');
			if(str=="false")
				est.setTwoWays(false);
			else
				est.setTwoWays(true);

			cout << id << ";" << nome << ";" << str << "\n";
			this->streetsVec.push_back(est);
			is.ignore();
			is.clear();
		}

		in.close();

	}


	vector<Coordenadas> getCoordsVec(){return this->coordsVec;}
	vector<Estrada> getStreetsVec(){return this->streetsVec;}

};



#endif /* DADOS_H_ */
