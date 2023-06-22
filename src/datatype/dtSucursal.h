#ifndef DTSUCURSAL_H
#define DTSUCURSAL_H

#include <iostream>
using namespace std;
#include "../../ICollection/interfaces/ICollectible.h"
#include "dtDireccion.h"

class dtSucursal : public ICollectible {
private:
  string nombre;
  string telefono;
  dtDireccion* direccion;

public:
  dtSucursal(string nombre, string telefono, dtDireccion* direccion);
  string getNombre();
  string getTelefono();
  dtDireccion* getDireccion();
};

#endif