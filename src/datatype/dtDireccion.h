#ifndef DTDIRECCION_H
#define DTDIRECCION_H

#include <iostream>
using namespace std;

class dtDireccion {
private:
  string calle;
  int nro;

public:
  dtDireccion(string calle, int nro);
  string getCalle();
  int getNumero();
};

#endif