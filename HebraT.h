#ifndef HebraT_H
#define HebraT_H
#include <bits/stdc++.h>
#include <chrono>
#include <unistd.h>
using namespace std;

class HebraT{
	private:
   		int execTime;
			int priority;
			int pid;
	public:
		HebraT();
		~HebraT();
		void ejecutar(int tiempoDormir);
		int getExecTime();
		void setPriority(int p);
		int getPriority();
		int getPID();
};

#endif
