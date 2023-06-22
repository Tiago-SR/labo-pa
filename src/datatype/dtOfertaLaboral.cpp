#include "dtOfertaLaboral.h"

dtOfertaLaboral::dtOfertaLaboral(int nroExpediente, string titulo, string desc, int cantHoras, dtRangoSalario* salario, dtFecha* fechaInicio, dtFecha* fechaFin, int cantPuestos) {
  this->nroExpediente = nroExpediente;
  this->titulo = titulo;
  this->desc = desc;
  this->cantHoras = cantHoras;
  this->salario = salario;
  this->fechaInicio = fechaInicio;
  this->fechaFin = fechaFin;
  this->cantPuestos = cantPuestos;
}
int dtOfertaLaboral::getNroExpediente() {
  return nroExpediente;
}
string dtOfertaLaboral::getTitulo() {
  return titulo;
}
string dtOfertaLaboral::getDesc() {
  return desc;
}
int dtOfertaLaboral::getCantHoras() {
  return cantHoras;
}
dtRangoSalario* dtOfertaLaboral::getSalario() {
  return salario;
}
dtFecha* dtOfertaLaboral::getFechaInicio() {
  return fechaInicio;
}
dtFecha* dtOfertaLaboral::getFechaFin() {
  return fechaFin;
}
int dtOfertaLaboral::getCantPuestos() {
  return cantPuestos;
}