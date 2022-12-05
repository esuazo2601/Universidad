#ifndef Simulador_H
#define Simulador_H
#include<bits/stdc++.h>
#include "HebraT.h"
using namespace std;

class Simulador{

	private:
		mutex m[9];
		vector<queue<HebraT*>> active;
		vector<queue<HebraT*>> expired;
		int processCounter = 0;
		int processInActive = 0;

	public:
		Simulador();
		~Simulador();
		void addToActive(HebraT* p);
		void addToExpired(HebraT* p);
		HebraT* getHebraTFromActive();
		void swap();
		void decreaseCounter();
		int getProcessCounter();
		int getProcessInActive();
		void resetProcessInActive();
};

#endif
