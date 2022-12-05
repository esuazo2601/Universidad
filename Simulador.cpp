#include "Simulador.h"
#include "HebraT.h"

Simulador::Simulador(){
	active.resize(9);
	expired.resize(9);
}

Simulador::~Simulador(){

}

void Simulador::addToActive(HebraT *p){
	int priority = rand() %  9; //se da una prioridad aleatoria a la hebraT
	p->setPriority(priority);
	active[p->getPriority()].push(p); //se pushea a la queue en la prioridad establecida
	processCounter++;
	processInActive++;
}

void Simulador::addToExpired(HebraT* p){
	int prevPrio = p->getPriority();
	if(p->getExecTime() > 20 && prevPrio <= 7){
		p->setPriority(prevPrio + 1);
		expired[p->getPriority()].push(p);
	}else{
		expired[prevPrio].push(p);
	}
	printf(" AddToExpired Proceso con PID: %d; Tiempo: %d; Prio Ant: %d; Prio Actual: %d\n\n",
	p->getPID(), p->getExecTime(), prevPrio, p->getPriority());
	processInActive--;
}

HebraT* Simulador::getHebraTFromActive(){ //Retorna la primera hebra encontrada segun prioridad
	HebraT* auxT = NULL;
	for(int i = 0; i < 9; i++){ //Cada nivel de prioridad
			// m[i].lock();
			if (!active[i].empty()){ // Si hay algo en el nivel i
				auxT = active[i].front(); //copia del proceso en active
				active[i].pop(); // se quita de active
				// m[i].unlock();
				break;
			}
			// else {
			// 	m[i].unlock();
			// }
	 }
	return auxT;
}

void Simulador::swap(){ //intercambia la runque de expirada con la activa
	vector<queue<HebraT*>> *pActive = &active;
	vector<queue<HebraT*>> *pExpired = &expired;
	vector<queue<HebraT*>> aux;

	aux = *pActive;
	*pActive = *pExpired;
	*pExpired = aux;

	processInActive = processCounter;
}

void Simulador::decreaseCounter(){
	processCounter--;
	processInActive--;
}

int Simulador::getProcessCounter(){
	return processCounter;
}

int Simulador::getProcessInActive(){
	return processInActive;
}

void Simulador::resetProcessInActive(){
	processInActive = 0;
}
