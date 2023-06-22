#include "dtSucursal.h"

dtSucursal::dtSucursal(string nombre, string telefono, dtDireccion* direccion) {
  this->nombre = nombre;
  this->telefono = telefono;
  this->direccion = direccion;
}
string dtSucursal::getNombre() {
  return nombre;
}
string dtSucursal::getTelefono() {
  return telefono;
}
dtDireccion* dtSucursal::getDireccion() {
  return direccion;
}