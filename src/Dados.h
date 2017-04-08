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
#define sleep(a) Sleep(a * 1000)

#ifndef DADOS_H_
#define DADOS_H_

class Dados
{
	vector<Vertex<Coordenadas*>> percurso;
	vector<Coordenadas*> coordsVec ;
	vector<Estrada*> streetsVec ;
	vector<Coordenadas*> hospitais;
	vector<Coordenadas*> bombeiros;
	vector<Coordenadas*> policias;
	GraphViewer *gv;
	long int streetids=0;
	int pos;

public:

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

	void resetVertexIcon ( )
	{
		for (unsigned int i = 1; i < percurso.size()-1; i++)
		{
			gv->setVertexIcon(percurso[i].getInfo()->getId(), "src/files/house.png" );
		}
	}

	void doDikstra (Graph<Coordenadas*> &grf, long int nodeid)
	{
		unsigned int i = 0;

		for ( i = 0; i < grf.getVertexSet().size(); i++)
			if (grf.getVertexSet()[i]->getInfo()->getId() == nodeid )
			{
				grf.dijkstraShortestPath(grf.getVertexSet()[i]->getInfo());
				this->pos=i;
			}
	}

	int dijkstraAnimation(Graph<Coordenadas*> &grf, long int nodeid1, long int nodeid2, int Vehicle)
	{
		unsigned int i = 0, j = 0, k = 0, m = 0, var = 0;
		double dist = 0;
		vector<Vertex<Coordenadas*>> tmp;

		long int max = 100000, idchosen=0;


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
		for ( m = 1; m < tmp.size()-1; m++ )
		{
			cout << " " << tmp[m].getInfo()->getId() << " - " ;

			//gv->setVertexColor(tmp[m].getInfo()->getId(), "yellow");
			if (Vehicle == 1 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/ambulance.png");
			else if (Vehicle == 2 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/policecar.png");
			else if (Vehicle == 3 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/fireman.png");
			else if (Vehicle == 4 ) gv->setVertexIcon(tmp[m].getInfo()->getId(), "src/files/heli.png");
			gv->rearrange();

			sleep(0.3);

		}
		cout <<  "Distância: " << dist << endl;



		return 0; // sucesso

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
		long long int id;
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
		long long int id;
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

	Coordenadas* findCoord(long int c){
		for (unsigned int i = 0; i < this->coordsVec.size(); ++i) {
			if(this->coordsVec[i]->getId() == c)
				return this->coordsVec[i];
		}

		return NULL;
	}

	Estrada* findStreet(long int c){
		for (unsigned int i = 0; i < this->streetsVec.size(); ++i) {
			if(this->streetsVec[i]->getId() == c)
				return this->streetsVec[i];
		}

		return NULL;
	}

	void CreateNodes(Graph<Coordenadas*> &grf, long int streetid, long int nodeid, long int adjnodeid) {
		Coordenadas *A=this->findCoord(nodeid), *B=this->findCoord(adjnodeid);

		if(A != NULL && B != NULL){
			grf.addVertex(A);
			gv->addNode(nodeid, A->getx(), A->gety());
			gv->setVertexIcon(nodeid, "src/files/house.png");
			grf.addVertex(B);
			gv->addNode(adjnodeid, B->getx(), B->gety());
			gv->setVertexIcon(adjnodeid, "src/files/house.png");


			grf.addEdge(A,B, this->distancia(A,B)); // falta atribuir o peso (que será feito com base num algoritmo de calculo de distancia vs coordenadas)
			grf.addEdge(B,A, this->distancia(A,B));



			gv->addEdge(this->streetids+=1,nodeid,adjnodeid,EdgeType::UNDIRECTED);

			loadImages(grf, nodeid, adjnodeid);


			//			if(grf.getVertex(A)->getadj().size() != 0){
			//				cout << "\n \nAdjacente de " << grf.getVertex(A)->getInfo()->getId() << " :\n";
			//				cout << grf.getVertex(A)->getadj()[0].getdest()->getInfo()->getId();
			//			cout << "\n\n";}

		}
		else
			return;
	}

	void CreateNodes2(Graph<Coordenadas*> &grf, long int streetid, long int nodeid, long int adjnodeid) {
		Coordenadas *A=this->findCoord(nodeid), *B=this->findCoord(adjnodeid);

		if(A != NULL && B != NULL){
			grf.addVertex(A);
			gv->addNode(nodeid, A->getx(), A->gety());
			gv->setVertexIcon(nodeid, "src/files/house.png");
			grf.addVertex(B);
			gv->addNode(adjnodeid, B->getx(), B->gety());
			gv->setVertexIcon(adjnodeid, "src/files/house.png");


			grf.addEdge(A,B, this->distancia(A,B)); // falta atribuir o peso (que será feito com base num algoritmo de calculo de distancia vs coordenadas)
			grf.addEdge(B,A, this->distancia(A,B));



			gv->addEdge(this->streetids+=1,nodeid,adjnodeid,EdgeType::UNDIRECTED);

			loadImages2(grf, nodeid,adjnodeid);

		}
		else
			return;
	}


	void loadImages(Graph<Coordenadas*> &grf, long int nodeid, long int adjnodeid){

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

	void loadImages2(Graph<Coordenadas*> &grf, long int nodeid, long int adjnodeid){
		gv->setVertexIcon(nodeid, "src/files/mountain.png");

		gv->setVertexIcon(adjnodeid, "src/files/mountain.png");

	}

	void loadConnectorsFile(Graph<Coordenadas*> &grf){
		ifstream in;
		string trans_string;
		long long int streetid, nodeid, adjnodeid;
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
