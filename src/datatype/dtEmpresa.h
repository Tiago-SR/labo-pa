#ifndef DTEMPRESA_H
#define DTEMPRESA_H

#include <iostream>
using namespace std;
#include "../../ICollection/interfaces/ICollectible.h"

class dtEmpresa : public ICollectible {
  private:
    string RUT;
    string nombre;
  public:
    dtEmpresa(string RUT, string nombre);
    string getRUT();
    string getNombre();
};
#endif