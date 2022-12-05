#include <bits/stdc++.h>
#include "HebraE.h"
#include "HebraT.h"
using namespace std;

HebraE::HebraE(){

}

HebraE::~HebraE(){

}

void HebraE::addHebra(HebraT *ht){ //Linkea una hebraT con su respectiva HebraE
  hebra = ht;
}

void HebraE::ejecutarHebraT(){ //ejecuta su hebra T almacenada
  if(hebra != NULL){
    if(hebra->getExecTime() < quantum){ //si el tiempo restante de ejecucion es menor que el quantum
      hebra->ejecutar(hebra->getExecTime()); //solo se ejecuta el tiempo
    }else{
      hebra->ejecutar(quantum); //de lo contrario, se ejecuta el quatum de la hebra E
    }
  }
}

HebraT* HebraE::getHebraT(){ //retorna su proceso asociado
  if(hebra != NULL) return hebra;
  else return NULL;
}

int HebraE::getQuantum(){
  return quantum;
}

void HebraE::unlink(){ //se desenlaza de su proceso
  if(hebra != NULL) hebra = NULL;
}
