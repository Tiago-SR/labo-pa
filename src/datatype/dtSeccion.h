#ifndef DTSECCION_H
#define DTSECCION_H

#include <iostream>
using namespace std;
#include "../../ICollection/interfaces/ICollectible.h"

class dtSeccion : public ICollectible {
private:
  string nombre;
  string interno;

public:
  dtSeccion(string nombre, string interno);
  string getNombre();
  string getInterno();
};

#endif