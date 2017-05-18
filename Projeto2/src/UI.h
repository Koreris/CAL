/*
 * UI.h
 *
 *  Created on: 05/04/2017
 *      Author: MDA
 */

#ifndef SRC_UI_H_
#define SRC_UI_H_

#include "includes.h"
#include "Dados.h"
#include "graphviewer.h"
#include "Graph.h"


enum states
{
	estMenuPrincipal,
	estMenuOpcUrgencia,
	estMenuOpcUrgencia2,
	estMenuLocalUrgencia,
	estVazioPGrafo,
	estIntermedio,
	estMenuPesquisa,
	estMenuEscrita
};


class UI
{
private:
	Dados* d;
public:
	UI(Dados* dados);
	states estado_atual;
	states estado_anterior;
	void menuPrincipal();
	int menuOpcUrgencia();
	int menuOpcUrgencia2();
	int menuVazioPGrafo();
	int menuLocalUrgencia();
	int menuIntermedio();
	int menuPesquisa();
	string menuEscritaLocal();
	virtual ~UI();
};

#endif /* SRC_UI_H_ */
