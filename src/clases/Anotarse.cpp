#include "../header/Anotarse.h"

Anotarse::Anotarse(Estudiante* e, OfertaLaboral* o, dtFecha* fecha) {
  this->estudiante = e;
  this->ofertaLaboral = o;
  this->fecha = fecha;
  this->entrevista = new List();
}
void Anotarse::setFecha(dtFecha* fecha) {
  this->fecha = fecha;
}
dtFecha* Anotarse::getFecha() {
  return this->fecha;
}
Estudiante* Anotarse::getEstudiante() {
  return this->estudiante;
}
OfertaLaboral* Anotarse::getOfertaLaboral() {
  return this->ofertaLaboral;
}
dtOfertaLaboral* Anotarse::mostrarLlamadoEstudiante() {
  return ofertaLaboral->getInfoOfertaLaboral();
}
void Anotarse::altaEntrevista(dtFecha* fecha) {
  entrevista->add(fecha);
}