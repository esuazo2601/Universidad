#include <bits/stdc++.h>
#include "HebraG.h"
using namespace std;

HebraG::HebraG(){

}

HebraG::~HebraG(){

}

HebraT* HebraG::crearHebra(){ //Crea una hebra T y la retorna
	HebraT *ht = new HebraT();
	printf( " Proceso PID: %d con tiempo: %d\n",ht->getPID(),ht->getExecTime());
	return ht;
}
