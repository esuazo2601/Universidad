#include <thread>
#include <chrono>
#include <unistd.h>
#include <bits/stdc++.h>
#include "HebraT.h"
using namespace std;
int a = 1; //tiempo minimo 1s
int b = 40; //maximo 40

HebraT::HebraT(){
	execTime = (rand() % b) + a; //el tiempo de ejecucion es aleatorio
	pid = (rand() % 1000) + 100; // se añadio un pid para identificar cada proceso
}

void HebraT::ejecutar(int tiempoDormir){
	sleep(tiempoDormir);
	execTime = execTime - tiempoDormir; //se disminuye el tiempo de ejeucion segun el tiempo que durmio la hebra
	if(execTime <= 0) execTime = 0; //nos aseguramos que el tiempo restante no sea negativo
}

HebraT::~HebraT(){
	delete this;
}

int HebraT::getExecTime(){
	return this->execTime;
}


void HebraT::setPriority(int p){
	this->priority=p;
}

int HebraT::getPriority(){
	return priority;
}

int HebraT::getPID(){
	return pid;
}
