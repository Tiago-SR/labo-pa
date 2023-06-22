#include "../header/Efectivo.h"

Efectivo::Efectivo(dtFecha* fecha, float sueldo, Estudiante* e, OfertaLaboral* o) {
  this->fecha = fecha;
  this->sueldo = sueldo;
  this->estudiante = e;
  this->ofertaLaboral = o;
}
void Efectivo::setFecha(dtFecha* fecha) {
  this->fecha = fecha;
}
void Efectivo::setSueldo(float sueldo) {
  this->sueldo = sueldo;
}
string Efectivo::getFecha() {
  return this->fecha->getFecha();
}
float Efectivo::getSueldo() {
  return this->sueldo;
}
Estudiante* Efectivo::getEstudiante() {
  return this->estudiante;
}
OfertaLaboral* Efectivo::getOfertaLaboral() {
  return this->ofertaLaboral;
}
dtOfertaLaboral* Efectivo::mostrarLlamadoEstudiante() {
  return this->ofertaLaboral->getInfoOfertaLaboral();
}