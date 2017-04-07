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
		cout << "\n Reportar Urgencia \n\n" << endl
				<< " +=======================================================================+" << endl
				<< " | +.  Por favor selecione o local da urgencia                           |" << endl
				<< " | +.  Devera ser um numero entre 1 e 767                                |" << endl
				<< " | -.  Excluindo:                                                        |" << endl
				<< " | -.  165, 434 - PSP                                                         |" << endl
				<< " | -.  144, 642 - Bombeiros                                              |" << endl
				<< " | -.  523, 313 - Hospitais                                         |" << endl
				<< " | 0.  Retroceder                                                        |" << endl
				<< " +=======================================================================+\n" << endl;
		cout << "\n Numero selecionado do menu:\n";

		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 767
				&& user_in_ != 165
				&& user_in_ != 434
				&& user_in_ != 144
				&& user_in_ != 523
				&& user_in_ != 313
				&& user_in_ != 642) //stations cant be chosen
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

int estacaoMaisProxima(int local,int tipo, Graph<Coordenadas*> g)
{
	switch(tipo)
	{
	case 1:
		//criminal - policias
	{
		int idMaisProximoB=g.getVertexSet()[0]->getInfo()->getId();
		for(int i=0; i<g.getVertexSet().size(); i++)
		{
			if((g.getVertexSet()[i]->getDist() <= g.getVertexSet()[idMaisProximoB]->getDist())
					&& ((g.getVertexSet()[i]->getInfo()->getId()==434)
							|| (g.getVertexSet()[i]->getInfo()->getId()==165)))
			{
				idMaisProximoB=g.getVertexSet()[i]->getInfo()->getId();
			}
		}
		return idMaisProximoB;
	}
	break;
	case 2:
		//bombeiros e hospitais
	{
		int idMaisProximoB=g.getVertexSet()[0]->getInfo()->getId();
		for(int i=0; i<g.getVertexSet().size(); i++)
		{
			if((g.getVertexSet()[i]->getDist() <= g.getVertexSet()[idMaisProximoB]->getDist())
					&& ((g.getVertexSet()[i]->getInfo()->getId()==523)
							|| (g.getVertexSet()[i]->getInfo()->getId()==313)
							|| (g.getVertexSet()[i]->getInfo()->getId()==144)
							|| (g.getVertexSet()[i]->getInfo()->getId()==642)))
			{
				idMaisProximoB=g.getVertexSet()[i]->getInfo()->getId();
			}
		}
		return idMaisProximoB;
	}
	break;
	case 3:
	{
		int idMaisProximoB=g.getVertexSet()[0]->getInfo()->getId();
		for(int i=0; i<g.getVertexSet().size(); i++)
		{
			if((g.getVertexSet()[i]->getDist() <= g.getVertexSet()[idMaisProximoB]->getDist())
					&& ((g.getVertexSet()[i]->getInfo()->getId()==144)
							|| (g.getVertexSet()[i]->getInfo()->getId()==642)))
			{
				idMaisProximoB=g.getVertexSet()[i]->getInfo()->getId();
			}
		}
		return idMaisProximoB;
	}
	break;
	case 4:
	{
		int idMaisProximoB=g.getVertexSet()[0]->getInfo()->getId();
		for(int i=0; i<g.getVertexSet().size(); i++)
		{
			if((g.getVertexSet()[i]->getDist() <= g.getVertexSet()[idMaisProximoB]->getDist())
					&& ((g.getVertexSet()[i]->getInfo()->getId()==523)
							|| (g.getVertexSet()[i]->getInfo()->getId()==313)))
			{
				idMaisProximoB=g.getVertexSet()[i]->getInfo()->getId();
			}
		}
		return idMaisProximoB;
	}
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
	int idLocal=0;
	int idEstacao=0;
	int idFinal=0;
	int tipoEmergencia=0;
	int gravidade=0;

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
			tipoEmergencia=ui.menuOpcUrgencia();
			break;

		case estMenuOpcUrgencia2:
			gravidade=ui.menuOpcUrgencia2();
			break;

		case estVazioPGrafo:
			novo->doDikstra(exp, idLocal);
			idEstacao=estacaoMaisProxima(idLocal,tipoEmergencia, exp);
			if(tipoEmergencia==2) //so aplicavel a situaçoesde saude
				switch(gravidade)
				{
							case 1:
								//pouco grave, a ambulancia so vai la
								novo->dijkstraAnimation(exp,idEstacao,idLocal);
								break;
							case 2:
								//medio grave vai p hospital
								novo->dijkstraAnimation(exp,idEstacao,idLocal);
								idFinal=estacaoMaisProxima(idLocal,4,exp);
								novo->dijkstraAnimation(exp,idLocal,idFinal);
								break;
							case 3:
								//muito grave,ambulancia vai para hospital mais proximo
								novo->dijkstraAnimation(exp,idEstacao,idLocal);
								idFinal=estacaoMaisProxima(idLocal,4,exp);
								novo->dijkstraAnimation(exp,idLocal,idFinal);
								break;
				}
			break;
			ui.menuVazioPGrafo();
			break;

		case estMenuLocalUrgencia:
			idLocal=ui.menuLocalUrgencia();
			break;
		}
	}
	getchar();
}
