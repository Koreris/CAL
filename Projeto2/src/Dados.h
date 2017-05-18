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
#include "bubbleSort.h"
#include "matcher.h"
#define sleep(a) Sleep(a * 1000)

#ifndef DADOS_H_
#define DADOS_H_

class Dados
{
	vector<Vertex<Coordenadas*>> percurso;
	vector<Coordenadas*> coordsVec ;
	vector<Estrada*> streetsVec ;
	vector<Estrada*> streetsVecfinal ;
	vector<Coordenadas*> hospitais;
	vector<Coordenadas*> bombeiros;
	vector<Coordenadas*> policias;
	vector<Vertex<Coordenadas*>> todos;
	int pos;

	int FLAG_POL = 0;
	int FLAG_BOMB = 0;
	int FLAG_HOSP = 0;

public:
	GraphViewer *gv;
	int streetids=0;
	string streetnametemp = "  ";

	double distancia( Coordenadas* a, Coordenadas* b){
		return sqrt( pow( a->getx()-b->getx(), 2 ) + pow( a->gety()-b->gety() ,2) );
		gv->rearrange();
	}

	Dados(GraphViewer *gv){
		this->gv = gv;
		gv->setBackground("src/files/background.jpg");
		gv->createWindow(1000, 800);

		gv->defineVertexColor("blue");

		gv->defineEdgeColor("black");
	};

	vector<Coordenadas*> getCoordsVec(){return this->coordsVec;}
	vector<Estrada*> getStreetsVec(){return this->streetsVec;}

	vector<Estrada*> updateDistanceOnStreets(string choosen){

		string tempStreetName;

		int count = 0;

		for(unsigned int i=0; i < this->streetsVec.size(); i++){
			this->streetsVec[i]->setDistance(editDistance(this->streetsVec[i]->getNome(), choosen));
		}

		bubbleSort(this->streetsVec);

		tempStreetName = this->streetsVec[0]->getNome();
		cout << "(" << count << ") " << "Nome da Rua:" << this->streetsVec[0]->getNome() << "; Distance from Word: " << this->streetsVec[0]->getDistance() << endl;
		streetsVecfinal.push_back(this->streetsVec[0]);

		count++;

		for(unsigned int i=1; i < this->streetsVec.size(); i++){
			if(tempStreetName != this->streetsVec[i]->getNome()){
				tempStreetName = this->streetsVec[i]->getNome();
				cout  << "(" << count << ") " << "Nome da Rua:" << this->streetsVec[i]->getNome() << "; Distance from Word: " << this->streetsVec[i]->getDistance() << endl;
				streetsVecfinal.push_back(this->streetsVec[i]);
				count++;
			}
		}

		return streetsVecfinal;
	}


	void SendMeAsreetAndIsearch(Graph<Coordenadas*> &grf, string StreetName){

		todos.clear();

		for  ( unsigned int i = 0; i < grf.getVertexSet().size(); i++ )
		{
			for( unsigned int j = 0; j < grf.getVertexSet()[i]->getadj().size(); j++)
			{
				if ( grf.getVertexSet()[i]->getadj()[j].getName() == StreetName)
				{
					if(grf.getVertexSet()[i]->getInfo()->getId() == 165
					|| grf.getVertexSet()[i]->getInfo()->getId() == 434
					|| grf.getVertexSet()[i]->getInfo()->getId() == 144
					|| grf.getVertexSet()[i]->getInfo()->getId() == 642
					|| grf.getVertexSet()[i]->getInfo()->getId() == 523
					|| grf.getVertexSet()[i]->getInfo()->getId() == 313
					) todos.push_back(grf.getVertexSet()[i]->getInfo());


					if(grf.getVertexSet()[i]->getInfo()->getId() == 165
					|| grf.getVertexSet()[i]->getInfo()->getId() == 434
					|| grf.getVertexSet()[i]->getInfo()->getId() == 144
					|| grf.getVertexSet()[i]->getInfo()->getId() == 642
					|| grf.getVertexSet()[i]->getInfo()->getId() == 523
					|| grf.getVertexSet()[i]->getInfo()->getId() == 313
					) todos.push_back(grf.getVertexSet()[i]->getInfo());



				}
			}

		}

if(printServices(StreetName) ==  -1)
	cout << "Em " << StreetName << " nao existe nenhum serviço de Emergência" << endl;

	}

	int printServices(string StreetName){

		if(todos.size() == 0) return -1;

		for (unsigned int i = 0 ; i < todos.size(); i++)
		{
			if(todos[i].getInfo()->getId() == 165 || todos[i].getInfo()->getId() == 434){
				if (FLAG_POL == 0) {cout << "-> Em " << StreetName << " existe uma Esquadra PSP localizada em " << todos[i].getInfo()->getId()<< endl; FLAG_POL = 1;}
			}

			else if(todos[i].getInfo()->getId() == 144 || todos[i].getInfo()->getId() == 642){
				if (FLAG_BOMB == 0){ cout << "-> Em " << StreetName << " existe um quartel de Bombeiros localizado em " << todos[i].getInfo()->getId()<< endl; FLAG_BOMB = 1;}
			}

			else if(todos[i].getInfo()->getId() == 523 || todos[i].getInfo()->getId() == 313){
				if (FLAG_HOSP == 0) {cout << "-> Em " << StreetName << " existe um Hospital localizado em " << todos[i].getInfo()->getId()<< endl; FLAG_HOSP =1;}
			}
		}
	}


	/*
	if(grf.getVertexSet()[i]->getInfo()->getId() == 165 || grf.getVertexSet()[i]->getInfo()->getId() == 434)
							cout << "Em " << StreetName << "existe uma Esquadra PSP localizada em" << grf.getVertexSet()[i]->getInfo()->getId()	<< endl;
						else if (grf.getVertexSet()[i]->getInfo()->getId() == 144 || grf.getVertexSet()[i]->getInfo()->getId() == 642)
							cout << "Em " << StreetName << "existe um Quartel de Bombeiros localizado em" << grf.getVertexSet()[i]->getInfo()->getId()	<< endl;
						else if (grf.getVertexSet()[i]->getInfo()->getId() == 523 || grf.getVertexSet()[i]->getInfo()->getId() == 313)
							cout << "Em " << StreetName << "existe um Hospital localizado em" << grf.getVertexSet()[i]->getInfo()->getId()	<< endl;

*/
	void resetVertexIcon (bool heli)
	{
		if(heli)
			for (unsigned int i = 1; i < percurso.size()-1; i++)
			{
				gv->setVertexIcon(percurso[i].getInfo()->getId(), "src/files/mountain.png" );
			}
		else
			for (unsigned int i = 1; i < percurso.size(); i++)
			{
				if(percurso[i].getInfo()->getId() == 165 || percurso[i].getInfo()->getId() == 434) gv->setVertexIcon(percurso[i].getInfo()->getId(), "src/files/police.png" );
				else if(percurso[i].getInfo()->getId() == 144 || percurso[i].getInfo()->getId() == 642) gv->setVertexIcon(percurso[i].getInfo()->getId(), "src/files/firestation.png" );
				else if(percurso[i].getInfo()->getId() == 523 || percurso[i].getInfo()->getId() == 313) gv->setVertexIcon(percurso[i].getInfo()->getId(), "src/files/Hospital.png" );
				else  gv->setVertexIcon(percurso[i].getInfo()->getId(), "src/files/house.png" );


			}
	}

	void doDikstra (Graph<Coordenadas*> &grf, int nodeid)
	{
		unsigned int i = 0;

		for ( i = 0; i < grf.getVertexSet().size(); i++)
			if (grf.getVertexSet()[i]->getInfo()->getId() == nodeid )
			{
				grf.dijkstraShortestPath(grf.getVertexSet()[i]->getInfo());
				this->pos=i;
			}
	}

	double dijkstraAnimation(Graph<Coordenadas*> &grf, int nodeid1, int nodeid2, int Vehicle, bool heli)
	{
		unsigned int i = 0, j = 0, k = 0, m = 0, var = 0;
		double dist = 0;
		vector<Vertex<Coordenadas*>> tmp;

		int max = 100000, idchosen=0;


		for ( i = 0; i < grf.getVertexSet().size(); i++)
			if (grf.getVertexSet()[i]->getInfo()->getId() == nodeid1 )
			{
				grf.dijkstraShortestPath(grf.getVertexSet()[i]->getInfo());
				var = i;
			}


		for ( j = 0; j < grf.getVertexSet().size(); j++)
			if (grf.getVertexSet()[j]->getInfo()->getId() == nodeid2 )
			{
				tmp.push_back(grf.getVertexSet()[j]->getInfo());
				dist = grf.getVertexSet()[j]->getDist();
				cout << dist << endl;
				break;
			}


		while (idchosen != nodeid1){

			for (k = 0; k < grf.getVertexSet()[j]->getadj().size(); k++)
			{
				if( grf.getVertexSet()[j]->getadj()[k].getdest()->getDist() < max){
					max = grf.getVertexSet()[j]->getadj()[k].getdest()->getDist();
					cout << grf.getVertexSet()[j]->getadj()[k].getName() << endl;
					idchosen = grf.getVertexSet()[j]->getadj()[k].getdest()->getInfo()->getId();
				}

			}
			j = var;
			for ( j = 0; j < grf.getVertexSet().size(); j++){
				if (grf.getVertexSet()[j]->getInfo()->getId() == idchosen )
				{
					tmp.push_back(grf.getVertexSet()[j]->getInfo());
					break;
				}
			}
		}


		reverse(tmp.begin(), tmp.end());
		this-> percurso = tmp;

		cout << "Trajeto mais curto : " << endl;
		if(heli)
			for ( m = 1; m < tmp.size(); m++ )
			{
				cout << " " << tmp[m].getInfo()->getId() << " - " ;

				//gv->setVertexColor(tmp[m].getInfo()->getId(), "yellow");
				if (Vehicle == 1 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/ambulance.png");
				else if (Vehicle == 2 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/policecar.png");
				else if (Vehicle == 3 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/fireman.png");
				else if (Vehicle == 4 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/heli.png");
				else if (Vehicle == 5 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/policecar2.png");
				else if (Vehicle == 6 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/firetruck.png");
				else if (Vehicle == 7 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/tank.png");
				gv->rearrange();

				sleep(0.3);

			}
		else
			for ( m = 1; m < tmp.size()-1; m++ )
			{
				cout << " " << tmp[m].getInfo()->getId() << " - " ;

				//gv->setVertexColor(tmp[m].getInfo()->getId(), "yellow");
				if (Vehicle == 1 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/ambulance.png");
				else if (Vehicle == 2 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/policecar.png");
				else if (Vehicle == 3 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/fireman.png");
				else if (Vehicle == 4 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/heli.png");
				else if (Vehicle == 5 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/policecar2.png");
				else if (Vehicle == 6 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/firetruck.png");
				else if (Vehicle == 7 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/tank.png");
				gv->rearrange();

				sleep(0.3);

			}

		cout <<  "Distância: " << dist << endl;



		return dist; // sucesso

	}


	void setHospital(Coordenadas *h){this->hospitais.push_back(h);}
	vector<Coordenadas*> getHospitais(){
		return this->hospitais;
	}

	void setBombeiros(Coordenadas *h){this->bombeiros.push_back(h);}
	vector<Coordenadas*> getBombeiros(){
		return this->bombeiros;
	}

	void setPolicias(Coordenadas *h){this->policias.push_back(h);}
	vector<Coordenadas*> getPolicias(){
		return this->policias;
	}

	void loadNodesFile(){
		ifstream in;
		string trans_string;
		int id;
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


			Coordenadas * coord = new Coordenadas(id, xdeg+50, ydeg+100);

			if(id == 523 || id == 313)
				this->setHospital(coord);

			if(id == 144 || id == 642)
				this->setBombeiros(coord);

			if(id == 434 || id == 165)
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
		int id;
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

			//cout << nome << endl;

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

	Coordenadas* findCoord(int c){
		for (unsigned int i = 0; i < this->coordsVec.size(); ++i) {
			if(this->coordsVec[i]->getId() == c)
				return this->coordsVec[i];
		}

		return NULL;
	}

	Estrada* findStreet(int c){
		for (unsigned int i = 0; i < this->streetsVec.size(); ++i) {
			if(this->streetsVec[i]->getId() == c)
				return this->streetsVec[i];
		}

		return NULL;
	}

	void setHeli(Graph<Coordenadas*> &exp, int idLocal, int idEstacao){
		Coordenadas *A=this->findCoord(idLocal), *B=this->findCoord(idEstacao);

		exp.addEdge(A,B, this->distancia(A,B), " "); // falta atribuir o peso (que será feito com base num algoritmo de calculo de distancia vs coordenadas)
		cout << "\nO local escolhido para emergência é um Local de dificil acesso, será enviado um helicoptero!" << endl;

		exp.addEdge(B,A, this->distancia(A,B), " ");

		gv->addEdge(this->streetids+=1, idLocal, idEstacao,EdgeType::UNDIRECTED);
		gv->rearrange();
	}

	void CreateNodes(Graph<Coordenadas*> &grf, int streetid, int nodeid, int adjnodeid) {
		Coordenadas *A=this->findCoord(nodeid), *B=this->findCoord(adjnodeid);

		if(A != NULL && B != NULL){
			grf.addVertex(A);
			gv->addNode(nodeid, A->getx(), A->gety());
			gv->setVertexIcon(nodeid, "src/files/house.png");
			grf.addVertex(B);
			gv->addNode(adjnodeid, B->getx(), B->gety());
			gv->setVertexIcon(adjnodeid, "src/files/house.png");

			if(findStreet(streetid) != NULL){
				streetnametemp = findStreet(streetid)->getNome();
			}

			grf.addEdge(A,B, this->distancia(A,B), streetnametemp); // falta atribuir o peso (que será feito com base num algoritmo de calculo de distancia vs coordenadas)
			grf.addEdge(B,A, this->distancia(A,B), streetnametemp);

			//cout << "rua: " << findStreet(streetid)->getNome();

			gv->addEdge(this->streetids+=1,nodeid,adjnodeid,EdgeType::UNDIRECTED);
			gv->setEdgeLabel(this->streetids,streetnametemp);

			loadImages(grf, nodeid, adjnodeid);


			//			if(grf.getVertex(A)->getadj().size() != 0){
			//				cout << "\n \nAdjacente de " << grf.getVertex(A)->getInfo()->getId() << " :\n";
			//				cout << grf.getVertex(A)->getadj()[0].getdest()->getInfo()->getId();
			//			cout << "\n\n";}

		}
		else
			return;
	}

	void CreateNodes2(Graph<Coordenadas*> &grf, int streetid, int nodeid, int adjnodeid) {
		Coordenadas *A=this->findCoord(nodeid), *B=this->findCoord(adjnodeid);

		if(A != NULL && B != NULL){
			grf.addVertex(A);
			gv->addNode(nodeid, A->getx(), A->gety());
			gv->setVertexIcon(nodeid, "src/files/house.png");
			grf.addVertex(B);
			gv->addNode(adjnodeid, B->getx(), B->gety());
			gv->setVertexIcon(adjnodeid, "src/files/house.png");


			grf.addEdge(A,B, this->distancia(A,B), " "); // falta atribuir o peso (que será feito com base num algoritmo de calculo de distancia vs coordenadas)
			grf.addEdge(B,A, this->distancia(A,B), " ");



			gv->addEdge(this->streetids+=1,nodeid,adjnodeid,EdgeType::UNDIRECTED);

			/*if(findStreet(streetid) != NULL){
				gv->setEdgeLabel(this->streetids,findStreet(streetid)->getNome());
			}*/


			loadImages2(grf, nodeid,adjnodeid);

		}
		else
			return;
	}


	void loadImages(Graph<Coordenadas*> &grf, int nodeid, int adjnodeid){

		if(nodeid == 352 || nodeid == 421 || nodeid == 536 || nodeid == 492) // gasolina
			gv->setVertexIcon(nodeid, "src/files/petrol.png");
		else if(adjnodeid == 352 || adjnodeid == 421 || adjnodeid == 536 || adjnodeid == 492)
			gv->setVertexIcon(adjnodeid, "src/files/petrol.png");
		if(nodeid == 640 || nodeid == 481 || nodeid == 55) // macdonalds
			gv->setVertexIcon(nodeid, "src/files/mac.png");
		else if(adjnodeid == 640 || adjnodeid == 481 || adjnodeid == 55)
			gv->setVertexIcon(adjnodeid, "src/files/mac.png");
		else if(nodeid == 720 || nodeid == 355 || nodeid == 136 || nodeid == 78 || nodeid == 259) // school
			gv->setVertexIcon(nodeid, "src/files/school.png");
		else if(adjnodeid == 720 || adjnodeid == 355 || adjnodeid == 136 || adjnodeid == 78 || adjnodeid == 259)
			gv->setVertexIcon(adjnodeid, "src/files/school.png");
		else if(nodeid == 523 || nodeid == 313) // hospitais
			gv->setVertexIcon(nodeid, "src/files/hospital.png");
		else if(adjnodeid == 523 || adjnodeid == 313)
			gv->setVertexIcon(adjnodeid, "src/files/hospital.png");
		else if(nodeid == 434 || nodeid == 165)
			gv->setVertexIcon(nodeid, "src/files/police.png"); //bombeiros
		else if(adjnodeid == 434 || adjnodeid == 165)
			gv->setVertexIcon(adjnodeid, "src/files/police.png");
		else if(nodeid == 144 || nodeid == 642) //psp
			gv->setVertexIcon(nodeid, "src/files/firestation.png");
		else if(adjnodeid == 144 || adjnodeid == 642)
			gv->setVertexIcon(adjnodeid, "src/files/firestation.png");
		else if(nodeid == 429 || nodeid == 529 || nodeid == 617 || nodeid == 487 || nodeid == 634 || nodeid == 544 || nodeid == 469) //psp
			gv->setVertexIcon(nodeid, "src/files/ilha.png");
		else if(adjnodeid == 429 || adjnodeid == 529 || adjnodeid == 617 || adjnodeid == 487 || adjnodeid == 634 || adjnodeid == 544 || adjnodeid == 469)
			gv->setVertexIcon(adjnodeid, "src/files/ilha.png");
	}

	void loadImages2(Graph<Coordenadas*> &grf, int nodeid, int adjnodeid){
		gv->setVertexIcon(nodeid, "src/files/mountain.png");

		gv->setVertexIcon(adjnodeid, "src/files/mountain.png");

	}

	void loadConnectorsFile(Graph<Coordenadas*> &grf){
		ifstream in;
		string trans_string;
		int streetid, nodeid, adjnodeid;
		stringstream is;
		string str, nome;

		in.open("src/files/C.txt");
		if(!in.is_open()){
			cout <<"File C.txt couldn't be found\n";
			return;
		}

		int count =0;

		while(getline(in, trans_string)){
			is.str(trans_string);
			getline(is, str, ';');
			streetid = stoll(str);

			getline(is, str, ';');
			nodeid = stoll(str);

			getline(is, str, ';');
			adjnodeid = stoll(str);

			//cout << streetid << ";" << nodeid << ";" << adjnodeid << "\n";

			if(count < 713)
				CreateNodes(grf, streetid, nodeid, adjnodeid);
			else
				CreateNodes2(grf, streetid, nodeid, adjnodeid);

			is.ignore();
			is.clear();
			count++;
		}

		gv->setBackground("src/files/background.png");
		gv->rearrange();
		in.close();
	}




};



#endif /* DADOS_H_ */
