/*
 * Estrada.h
 *
 *  Created on: 29/03/2017
 *      Author: FranciscoSilva
 */
#include "includes.h"

#ifndef ESTRADA_H_
#define ESTRADA_H_


class Estrada
{
	long int id;
	string nome;
	bool twoways;


public:
	Estrada (long int i, string n, bool t){
		this->id = i;
		this->nome = n;
		this->twoways = t;
	};

	void setId(long int i){this->id = i;}
	void setNome(string n){this->nome = n;}
	void setTwoWays(bool t){this->twoways = t;}

	long int getId(){return this->id;}
	string getNome(){return this->nome;}
	bool getTwoWays(){return this->twoways;}

};


#endif /* ESTRADA_H_ */
