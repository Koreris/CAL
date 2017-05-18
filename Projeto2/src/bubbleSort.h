#include <vector>
#include "Estrada.h"
using namespace std;

template <class Estrada>
void bubbleSort(vector<Estrada> &v)
{
	for(unsigned int j=v.size()-1; j>0; j--)
	{
		bool troca=false;
		for(unsigned int i = 0; i<j; i++)
			if(v[i+1]->getDistance() < v[i]->getDistance()) {
				swap(v[i],v[i+1]);
			troca = true;
			}

		if (!troca) return;
	}

}
