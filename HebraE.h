#ifndef HEBRA_E
#define HEBRA_E
#include <bits/stdc++.h>
#include "HebraT.h"
using namespace std;


class HebraE{
  private:
    HebraT *hebra = NULL; //Proceso asociado a esta HebraE
    int quantum = 10;
  public:
    HebraE();
    ~HebraE();
    void addHebra(HebraT *ht);
    void ejecutarHebraT();
    int getQuantum();
    void unlink();
    HebraT* getHebraT();
};

#endif
