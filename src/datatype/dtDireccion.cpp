#include "dtDireccion.h"
dtDireccion::dtDireccion(string calle, int nro) {
  this->calle = calle;
  this->nro = nro;
}
string dtDireccion::getCalle() {
  return calle;
}
int dtDireccion::getNumero() {
  return nro;
}