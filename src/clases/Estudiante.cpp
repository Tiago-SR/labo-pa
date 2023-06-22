#include "../header/Estudiante.h"

Estudiante::Estudiante(string ci, string nombre, string apellido, string telefono, dtDireccion* direccion, dtFecha* fechaNac, int creditos) {
  this->ci = ci;
  this->nombre = nombre;
  this->apellido = apellido;
  this->telefono = telefono;
  this->direccion = direccion;
  this->fechaNacimiento = fechaNac;
  this->creditos = creditos;
  this->asignaturas = new OrderedDictionary();
  this->efectivos = new OrderedDictionary();
  this->anotarse = new OrderedDictionary();
}
void Estudiante::setNombre(string nombre) {
  this->nombre = nombre;
}
void Estudiante::setApellido(string apellido) {
  this->apellido = apellido;
}
void Estudiante::setTelefono(string telefono) {
  this->telefono = telefono;
}
void Estudiante::setDireccion(dtDireccion* direccion) {
  this->direccion = direccion;
}
void Estudiante::setFechaNacimiento(dtFecha* fechaNacimiento) {
  this->fechaNacimiento = fechaNacimiento;
}
void Estudiante::setCreditos(int creditos) {
  this->creditos = creditos;
}
string Estudiante::getCi() {
  return this->ci;
}
string Estudiante::getNombre() {
  return this->nombre;
}
string Estudiante::getApellido() {
  return this->apellido;
}
string Estudiante::getTelefono() {
  return this->telefono;
}
dtDireccion* Estudiante::getDireccion() {
  return this->direccion;
}
dtFecha* Estudiante::getFechaNacimiento() {
  return this->fechaNacimiento;
}
int Estudiante::getCreditos() {
  return this->creditos;
}



bool Estudiante::checkAsignatura(int nroExp) {
  return this->asignaturas->member(new Integer(nroExp));
}
bool Estudiante::estaVinculadoAsignatura(int id) {
  return this->asignaturas->member(new Integer(id));
}
void Estudiante::crearVinculo(Anotarse* a) {
  anotarse->add(new Integer(a->mostrarLlamadoEstudiante()->getNroExpediente()), a);
}
// solo declaracion de metodos no codigo interno
dtEstudiante* Estudiante::getEstudiante() {
  return new dtEstudiante(ci, nombre, apellido);
}
dtEstudianteTodo* Estudiante::getEstudianteTodo() {
  return new dtEstudianteTodo(ci, nombre, apellido, fechaNacimiento, telefono);
}
ICollection* Estudiante::mostrarAsignaturas() {
  ICollection* ret = new List();
  IIterator* it = asignaturas->getIterator();
  while (it->hasCurrent()) {
    ret->add(((Asignatura*)(it->getCurrent()))->getInfoAsignatura());
    it->next();
  }
  delete it;
  return ret;
}
ICollection* Estudiante::mostrarLlamadosEstudiante() {
  ICollection* ret = new List();
  IIterator* it = anotarse->getIterator();
  while (it->hasCurrent()) {
    // TO-DO para cuando se implemente anotarse
    // ret->add(((Anotarse*)(it->getCurrent()))->getInfoAnotarse());
    it->next();
  }
  delete it;
  return ret;
}

bool Estudiante::estaVinculadoOferta(int nroExp) {
  return anotarse->member(new Integer(nroExp));
}

Estudiante::~Estudiante() {
  // TO-DO cuando se implemente anotarse y efectivo
}