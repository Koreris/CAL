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
	long long int id;
	double xDegrees;
	double yDegrees;
	double xRad;
	double yRad;

public:
	Coordenadas (long long int i, double x,double y, double x2, double y2 ){

			this->id = i;
			this->xDegrees = x;
			this->yDegrees = y;
			this->xRad = x2;
			this->yRad = y2;
	};

	void setId(long long int i){this->id = i;}
	void setxDegrees(double x){this->xDegrees = x;}
	void setyDegrees(double y){this->yDegrees = y;}
	void setxRad(double x){this->xRad = x;}
	void setyRad(double y){this->yRad = y;}

	long long int getId(){return this->id;}
	double getxDegrees(double x){return this->xDegrees;}
	double getyDegrees(double y){return this->yDegrees;}
	double getxRad(double x){return this->xRad;}
	double getyRad(double y){return this->yRad;}

};


#endif /* COORDENADAS_H_ */
