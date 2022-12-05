#include "HebraT.h"
#include "HebraG.h"
#include "HebraE.h"
#include "Simulador.h"
#include <stdlib.h>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <chrono>
using namespace std;

int main(){
  srand(7); //semilla para el random
  int M, N; // M Cpus y N procesos iniciales
  Simulador *rq = new Simulador();
  HebraG *hg = new HebraG();
  vector<HebraE*> proceHebrasE; //arreglo de hebras E

  printf(" ¿ Cuantos procesadores utilizara ?: ");
  scanf("%d",&M);
  // Se crean las hebras E
  for(int i = 0; i < M; i++){
    HebraE *He = new HebraE();
    proceHebrasE.push_back(He);
  }

  printf (" ¿ Cuantos procesos tiene inicialmente ?: ");
  scanf("%d",&N);
  cout<<endl;
  for(int i = 0; i < N; i++){ // Se crean hebras T
    HebraT *aux = hg->crearHebra();
    rq->addToActive(aux); //se añaden las hebras T a la runqueue activa del planificador
  }

  while(true){
    thread tE[M]; // Paraleliza las hebrasE
    int cantidad = 0;
     cout << endl << "                                             PROCESOS EN COLA ACTIVA "<< rq->getProcessInActive() << endl << endl;

    // for creacion de hilos
   	for(int i = 0; i < M; i++, cantidad++){
      HebraT *aux = rq->getHebraTFromActive();

      if(aux != NULL){
        proceHebrasE[i]->addHebra(aux); //si el retorno no es NULL, se enlaza con su hebraE

        printf(" INICIO Proceso PID: %d; Tiempo %d; HebraE #%d \n", aux->getPID(), aux->getExecTime(), i);
        tE[i] = thread(&HebraE::ejecutarHebraT, proceHebrasE[i]);

      }
      else break; //si retorna null, no quedan mas hebras en la cola activa
    }

    cout << endl;

    // for del join
    for(int i = 0; i < cantidad; i++){ //se itera la cantidad de procesos enlazados con procesadores
      tE[i].join();
      HebraT *aux = proceHebrasE[i]->getHebraT();

      if(aux->getExecTime() == 0){ //si un proceso termina, se desenlaza de su procesador
        printf(" Finalizacion Proceso PID: %d; HebraE #%d \n\n", aux->getPID(), i);
        proceHebrasE[i]->unlink();
        rq->decreaseCounter(); //y se decrementa el contador de procesos
      }

      else{ //si no termina el proceso, se añaden a la cola activa
        printf(" FIN Proceso PID: %d; Tiempo %d; HebraE #%d \n", aux->getPID(), aux->getExecTime(), i);
        rq->addToExpired(aux);
        proceHebrasE[i]->unlink();
      }
    }

    if(rq->getProcessInActive() == 0){ // ya no quedan procesos en active
      rq->swap(); // se intercambia el runqueue expirado por el activo

      printf("\033[1;34m");
      printf("\n-----------------------------------------SIGUIENTE PERIODO DE PLANIFICACION-----------------------------------------\n\n");
      printf("\033[0m");
    }

    int cantidadDeProcesos = rq->getProcessCounter();

    if(cantidadDeProcesos == 0){ // ya no quedan procesos
      rq->resetProcessInActive(); //el contador de procesos en activo se iguala a 0
      cout << endl << "                                             PROCESOS EN COLA ACTIVA "<< rq->getProcessInActive() << endl << endl;

      int cantNuevosProcesos = (rand() % 6) + 2; //Se crean entre 2 a 6 procesos nuevos cuando la run queue queda vacía

      cout << "  INICIO CREACION HEBRAS ..." << endl;

      for(int j = 0 ; j < cantNuevosProcesos; j++){ // for creacion de procesos
        HebraT *aux = hg->crearHebra();
        rq->addToActive(aux);
      }

      cout << "  FIN CREACION DE " << cantNuevosProcesos << " HEBRAS" << endl << endl;
    }

  }
  return 0;
}
