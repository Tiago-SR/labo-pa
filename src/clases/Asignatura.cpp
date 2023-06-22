#include "../header/Asignatura.h"

Asignatura::Asignatura(int codigo, string nombre, int creditos) {
  this->codigo = codigo;
  this->nombre = nombre;
  this->creditos = creditos;
}
void Asignatura::setNombre(string nuevo) {
  this->nombre = nuevo;
}
void Asignatura::setCreditos(int nuevo) {
  this->creditos = nuevo;
}
int Asignatura::getCodigo() {
  return this->codigo;
}
string Asignatura::getNombre() {
  return this->nombre;
}
int Asignatura::getCreditos() {
  return this->creditos;
}
dtAsignatura* Asignatura::getInfoAsignatura() {
  return new dtAsignatura(this->codigo, this->nombre, this->creditos);
}