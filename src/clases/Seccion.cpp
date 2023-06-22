#include "../header/Seccion.h"

Seccion::Seccion(string nombre, string interno, Sucursal* s) {
  this->nombre = nombre;
  this->interno = interno;
  this->sucursal = s;
  this->ofertasLaborales = new OrderedDictionary();
}
void Seccion::setInterno(string i) {
  this->interno = i;
}
string Seccion::getNombre() {
  return this->nombre;
}
string Seccion::getInterno() {
  return this->interno;
}


dtSeccion* Seccion::getInfoSeccion() {
  return new dtSeccion(this->getNombre(), this->getInterno());
}

bool Seccion::checkOfertaLaboral(int nroExp) {
  return ofertasLaborales->member(new Integer(nroExp));
}
void Seccion::altaOfertaLaboral(OfertaLaboral* infoOferta) {
  if (checkOfertaLaboral(infoOferta->getNroExpediente())) throw invalid_argument("Ya existe una oferta laboral con ese titulo");
  this->ofertasLaborales->add(new Integer(infoOferta->getNroExpediente()), infoOferta);
}
void Seccion::darBajaOferta(int nroExp) {
  if (!checkOfertaLaboral(nroExp)) throw invalid_argument("No existe una oferta laboral con ese numero de expediente");
  this->ofertasLaborales->remove(new Integer(nroExp));
}
OfertaLaboral* Seccion::getOfertaLaboral(int nroExp) {
  if (!checkOfertaLaboral(nroExp)) throw invalid_argument("No existe una oferta laboral con ese numero de expediente");
  return ((OfertaLaboral*)(this->ofertasLaborales->find(new Integer(nroExp))));
}

ICollection* Seccion::listarOfertasLaborales() {
  ICollection* ret = new List();
  IIterator* it = this->ofertasLaborales->getIterator();
  while (it->hasCurrent()) {
    ret->add(((OfertaLaboral*)(it->getCurrent()))->getInfoOfertaLaboral());
    it->next();
  }
  return ret;
}

dtSucursal* Seccion::mostrarInfoSucursal() {
  return this->sucursal->getInfoSucursal();
}
dtEmpresa* Seccion::mostrarInfoEmpresa() {
  return this->sucursal->mostrarInfoEmpresa();
}


Seccion::~Seccion() {
  IIterator* it = ofertasLaborales->getIterator();
  OfertaLaboral* elem;
  while (it->hasCurrent()) {
    elem = (OfertaLaboral*)(it->getCurrent());
    it->next();
    ofertasLaborales->remove(new Integer(elem->getNroExpediente()));
    delete elem;
  }
  delete it;
}