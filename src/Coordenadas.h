/*
 * Coordenadas.h
 *
 *  Created on: 29/03/2017
 *      Author: FranciscoSilva
 */

#ifndef COORDENADAS_H_
#define COORDENADAS_H_


class Coordenadas
{
	long int id;
	int x;
	int y;

public:
	Coordenadas ( long int i, int x, int y){

			this->id = i;
			this->x = x;
			this->y = y;
	};

	void setId(long int i){this->id = i;}
	void setx(int x){this->x = x;}
	void sety(int y){this->y = y;}


	long int getId(){return this->id;}
	int getx(){return this->x;}
	int gety(){return this->y;}


	bool operator==(const Coordenadas& other) // copy assignment
	{
		if(this->id == other.id)
			return true;
		else
			return false;
	}

};


#endif /* COORDENADAS_H_ */
