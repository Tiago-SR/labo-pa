#ifndef DTESTUDIANTE_H
#define DTESTUDIANTE_H

#include <iostream>
using namespace std;
#include "../../ICollection/interfaces/ICollectible.h"

class dtEstudiante : public ICollectible {
private:
  string ci;
  string nombre;
  string apellido;

public:
  dtEstudiante(string ci, string nombre, string apellido);
  string getCI();
  string getNombre();
  string getApellido();
};

#endif