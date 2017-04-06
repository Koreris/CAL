/*
 * UI.cpp
 *
 *  Created on: 05/04/2017
 *      Author: MDA
 */

#include "UI.h"

/**
 * Prompts user to press enter, mimicking a paused state until user presses enter
 * @brief press enter to continue
 */
void pressEnter ()
{
	cout << "Press Enter to continue..." << endl;
	getchar ();
}
/**
 * Uses windows related functions to clear console screen
 * @brief clears console screen
 */
void cls ()
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle (STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo (console, &screen);
	FillConsoleOutputCharacterA (console, ' ',
									screen.dwSize.X * screen.dwSize.Y, topLeft,
									&written);
	FillConsoleOutputAttribute (console,
	FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
								screen.dwSize.X * screen.dwSize.Y, topLeft,
								&written);
	SetConsoleCursorPosition (console, topLeft);
}


UI::UI(Dados* dados)
{
	d=dados;
	estado_atual=estMenuPrincipal;
	estado_anterior=estMenuPrincipal;
}

UI::~UI()
{
}

void UI::menuPrincipal ()
{
	string user_in;
	long user_in_;
	bool validInput = false;
	while (!validInput)
	{
		cout << "\n Servico de Urgencias \n\n" << endl
				<< " +=======================================================================+" << endl
				<< " | 1.  Reportar urgencia                                                 |" << endl
				<< " | 0.  Sair                                                              |" << endl
				<< " +=======================================================================+\n" << endl;
		cout << "\n Numero selecionado do menu:\n";

		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ == 1 || user_in_ == 0)
		{
			validInput = true;
			switch (user_in_)
			{

			case 1:
				estado_anterior = estado_atual;
				estado_atual = estMenuLocalUrgencia;
				cls ();
				break;
			case 0:
				exit (0);
			}
		}
	}
	return;
}

int UI::menuLocalUrgencia ()
{

	string user_in;
	long user_in_;
	bool validInput = false;
	int local=0;
	while (!validInput)
	{
		//TODO
		//adicionar restricoes
		cout << "\n Reportar Urgencia \n\n" << endl
				<< " +=======================================================================+" << endl
				<< " | +.  Por favor selecione o local da urgencia                           |" << endl
				<< " | +.  Devera ser um numero entre 1 e 767                                |" << endl
				<< " | 0.  Retroceder                                                        |" << endl
				<< " +=======================================================================+\n" << endl;
		cout << "\n Numero selecionado do menu:\n";

		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 767)
		{
			local=user_in_;
			validInput = true;
			estado_anterior = estado_atual;
			estado_atual = estMenuOpcUrgencia;
			cls ();
			return local;
		}
		if(user_in_ == 0)
		{
			estado_anterior=estado_atual;
			estado_atual=estMenuPrincipal;
			menuPrincipal();
		}
	}
}


int UI::menuOpcUrgencia ()
{

	string user_in;
	long user_in_;
	bool validInput = false;
	int ambitoSituacao=0;
	while (!validInput)
	{
		cout << "\n Reportar Urgencia \n\n" << endl
				<< " +=======================================================================+" << endl
				<< " | +.  Por favor selecione o ambito da situacao                          |" << endl
				<< " | 1.  Criminal/judicial                                                 |" << endl
				<< " | 2.  Saude                                                             |" << endl
				<< " | 3.  Fogos                                                             |" << endl
				<< " | 0.  Retroceder                                                        |" << endl
				<< " +=======================================================================+\n" << endl;
		cout << "\n Numero selecionado do menu:\n";

		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 3)
		{
			ambitoSituacao=user_in_;
			validInput = true;
			estado_anterior = estado_atual;
			estado_atual = estMenuOpcUrgencia2;
			cls ();
			return ambitoSituacao;
		}
		if(user_in_ == 0)
		{
			estado_anterior=estado_atual;
			estado_atual=estMenuLocalUrgencia;
			menuPrincipal();
		}
	}
}

int UI::menuOpcUrgencia2()
{

	string user_in;
	long user_in_;
	bool validInput = false;
	int gravidadeSituacao=0;
	while (!validInput)
	{
		cout << "\n Reportar Urgencia \n\n" << endl
				<< " +=======================================================================+" << endl
				<< " | +.  Por favor selecione a gravidade da situacao                       |" << endl
				<< " | 1.  Pouco Grave                                                       |" << endl
				<< " | 2.  Grave                                                             |" << endl
				<< " | 3.  Muito Grave                                                       |" << endl
				<< " | 0.  Retroceder                                                        |" << endl
				<< " +=======================================================================+\n" << endl;
		cout << "\n Numero selecionado do menu:\n";

		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 3)
		{
			gravidadeSituacao=user_in_;
			validInput = true;
			estado_anterior = estado_atual;
			estado_atual = estVazioPGrafo;
			cls ();
			return gravidadeSituacao;
		}
		if(user_in_ == 0)
		{
			estado_anterior=estado_atual;
			estado_atual=estMenuOpcUrgencia;
			menuOpcUrgencia();
		}
	}
}

int UI::menuVazioPGrafo()
{
	string user_in;
	long user_in_;
	bool validInput = false;
	while (!validInput)
	{
		cout << "\n Visualizacao \n\n" << endl
				<< " +===============================================================+" << endl
				<< " | +.  Mapa da situacao                                          |" << endl
				<< " | 0.  Voltar ao menu principal                                  |" << endl
				<< " +===============================================================+\n" << endl;
		cout << "\n Numero selecionado do menu:\n";

		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ == 0)
		{
			validInput = true;
			estado_anterior = estado_atual;
			estado_atual = estMenuPrincipal;
			cls ();
			menuPrincipal();
		}
	}
}
int closest_relief(int urg,int type){
	switch(type){
	case 1:
		//crimial
		break;
	case 2:
		//saude
		//ver nas estaçoes de bombeiros e hospitais por closest ambulancia

	case 3:
		//fogo

		break;
	}
}
int main()
{

 cout <<"      _______.  ______        _______."<< endl;
 cout <<"     /       | /  __  \\     /       |"<< endl;
 cout <<"    |   (----`|  |  |  |    |   (----`"<< endl;
 cout <<"     \\   \\    |  |  |  |    \\   \\ "<< endl;
 cout <<" .----)   |   |  `--'  |.----)   |"<< endl;
 cout <<" |_______/     \\______/  |_______/"<< endl;


	GraphViewer *gv = new GraphViewer(600, 600, false);
	Dados *novo = new Dados(gv);
	UI ui = UI(novo);
	novo->loadNodesFile();
	novo->loadStreetsFile();
	int id_urgencia=0;
	int id_relief=0;
	int id_final=0;
	int emergency_type=0;
	int gravity=0;

	Graph<Coordenadas*> exp;

	novo->loadConnectorsFile(exp);
	while(true)
	{
		switch(ui.estado_atual)
		{
		case estMenuPrincipal:
			ui.menuPrincipal();
			break;

		case estMenuOpcUrgencia:
			emergency_type=ui.menuOpcUrgencia();
			break;

		case estMenuOpcUrgencia2:
			gravity=ui.menuOpcUrgencia2();
			break;

		case estVazioPGrafo:
			id_relief=closest_relief(id_urgencia,emergency_type);
			novo->dijkstraAnimation(exp, id_urgencia, id_relief);
			if(emergency_type==2) //so aplicavel a situaçoesde saude
				switch(gravity){
							case 1:
								//pouco grave, so vai ate a urgencia e nao volta
								break;
							case 2:
								//medio grave
								//calc closest hospital
								//int_final=closest_hospital_id;
								//novo->dijkstraAnimation(exp,id_relif,int_final);
								break;
							case 3:
								//muito grave,ambulancia vai para hospital mais proximo
								//calc closest hospital
								//int_final=closest_hospital_id;
								//novo->dijkstraAnimation(exp,id_relif,int_final);
								break;
			    }
			break;
			ui.menuVazioPGrafo();
			break;

		case estMenuLocalUrgencia:
			id_urgencia=ui.menuLocalUrgencia();
			break;
		}
	}


	/*Pinta a Amarelo o Trajeto mais curto entre quaisquer dois pontos do grafo*/

	/*Pinta a Amarelo o Trajeto mais curto entre quaisquer dois pontos do grafo*/


	getchar();

}
