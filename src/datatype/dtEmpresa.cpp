#include "dtEmpresa.h"

dtEmpresa::dtEmpresa(string RUT, string nombre) {
  this->RUT = RUT;
  this->nombre = nombre;
}
string dtEmpresa::getRUT() {
  return this->RUT;
}
string dtEmpresa::getNombre() {
  return this->nombre;
}