#include "dtSeccion.h"

dtSeccion::dtSeccion(string nombre, string interno) {
  this->nombre = nombre;
  this->interno = interno;
}
string dtSeccion::getNombre() {
  return nombre;
}
string dtSeccion::getInterno() {
  return interno;
}