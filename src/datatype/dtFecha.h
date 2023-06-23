#ifndef DTFECHA_H
#define DTFECHA_H

#include <iostream>
using namespace std;

#include "../../ICollection/interfaces/ICollectible.h"

class dtFecha : public ICollectible {
private:
  int dia;
  int mes;
  int anio;

public:
  dtFecha(int dia, int mes, int anio);
  dtFecha(string fecha);
  int getDia();
  int getMes();
  int getAnio();
  string getFecha();
  bool menorQue(dtFecha* fecha);
  bool mayorQue(dtFecha* fecha);
};

#endif