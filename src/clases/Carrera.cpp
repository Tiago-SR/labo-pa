#include "../header/Carrera.h"

Carrera::Carrera(int codigo, string nombre, int creditosNecesarios, IDictionary* asignaturas) {
  this->codigo = codigo;
  this->nombre = nombre;
  this->creditosNecesarios = creditosNecesarios;
  this->asignaturas = new OrderedDictionary();
}

Carrera::~Carrera() {
  delete this->asignaturas;
}

int Carrera::getCodigo() {
  return this->codigo;
}

string Carrera::getNombre() {
  return this->nombre;
}

int Carrera::getCreditosNecesarios() {
  return this->creditosNecesarios;
}

IDictionary* Carrera::getAsignaturas() {
  return this->asignaturas;
}

void Carrera::setCodigo(int codigo) {
  this->codigo = codigo;
}

void Carrera::setNombre(string nombre) {
  this->nombre = nombre;
}

void Carrera::setCreditosNecesarios(int creditosNecesarios) {
  this->creditosNecesarios = creditosNecesarios;
}

void Carrera::setAsignaturas(IDictionary* asignaturas) {
  if (this->asignaturas != asignaturas) {
    delete this->asignaturas;
    this->asignaturas = asignaturas;
  }
}