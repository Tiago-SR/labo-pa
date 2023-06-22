#ifndef DTASIGNATURA_H
#define DTASIGNATURA_H

#include <iostream>
using namespace std;
#include "../../ICollection/interfaces/ICollectible.h"

class dtAsignatura : public ICollectible {
private:
  int codigo;
  string nombre;
  int creditos;

public:
  dtAsignatura(int codigo, string nombre, int creditos);
  int getCodigo() ;
  string getNombre();
  int getCreditos();
};
#endif