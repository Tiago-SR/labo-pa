#include "dtEstudiante.h"

dtEstudiante::dtEstudiante(string ci, string nombre, string apellido) {
  this->ci = ci;
  this->nombre = nombre;
  this->apellido = apellido;
}
string dtEstudiante::getCI() {
  return ci;
}
string dtEstudiante::getNombre() {
  return nombre;
}
string dtEstudiante::getApellido() {
  return apellido;
}