#include "dtFecha.h"

dtFecha::dtFecha(int dia, int mes, int anio) {
  this->dia = dia;
  this->mes = mes;
  this->anio = anio;
}
dtFecha::dtFecha(string fecha) {
  string delimiter = "/";
  string token = fecha.substr(0, fecha.find(delimiter));
  this->dia = stoi(token);
  fecha.erase(0, fecha.find(delimiter) + 1);
  token = fecha.substr(0, fecha.find(delimiter));
  this->mes = stoi(token);
  fecha.erase(0, fecha.find(delimiter) + 1);
  token = fecha.substr(0, fecha.find(delimiter));
  this->anio = stoi(token);
}
int dtFecha::getDia() {
  return dia;
}
int dtFecha::getMes() {
  return mes;
}
int dtFecha::getAnio() {
  return anio;
}
string dtFecha::getFecha() {
  return to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
}

bool dtFecha::menorQue(dtFecha* fecha) {
  if (anio < fecha->getAnio())
    return true;
  else if (anio == fecha->getAnio()) {
    if (mes < fecha->getMes())
      return true;
    else if (mes == fecha->getMes())
      return dia < fecha->getDia();
  }
  return false;
}
bool dtFecha::mayorQue(dtFecha* fecha) {
  if (anio > fecha->getAnio())
    return true;
  else if (anio == fecha->getAnio()) {
    if (mes > fecha->getMes())
      return true;
    else if (mes == fecha->getMes())
      return dia > fecha->getDia();
  }
  return false;
}