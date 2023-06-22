#include "dtAsignatura.h"
dtAsignatura::dtAsignatura(int codigo, string nombre, int creditos) {
  this->codigo = codigo;
  this->nombre = nombre;
  this->creditos = creditos;
}
int dtAsignatura::getCodigo() {
  return codigo;
}
string dtAsignatura::getNombre() {
  return nombre;
}
int dtAsignatura::getCreditos() {
  return creditos;
}