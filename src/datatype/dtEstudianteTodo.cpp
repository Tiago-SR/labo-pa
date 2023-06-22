#include "dtEstudianteTodo.h"

dtEstudianteTodo::dtEstudianteTodo(string ci, string nombre, string apellido, dtFecha* fechaNacimiento, string telefono) {
  this->ci = ci;
  this->nombre = nombre;
  this->apellido = apellido;
  this->fechaNacimiento = fechaNacimiento;
  this->telefono = telefono;
}
string dtEstudianteTodo::getCI() {
  return ci;
}
string dtEstudianteTodo::getNombre() {
  return nombre;
}
string dtEstudianteTodo::getApellido() {
  return apellido;
}
dtFecha* dtEstudianteTodo::getFechaNacimiento() {
  return fechaNacimiento;
}
string dtEstudianteTodo::getTelefono() {
  return telefono;
}