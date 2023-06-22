#include "../header/Sucursal.h"


Sucursal::Sucursal(string nombre, string telefono, dtDireccion* direccion, Empresa* e) {
  this->nombre = nombre;
  this->telefonoSucursal = telefono;
  this->direccionSucursal = direccion;
  this->empresa = e;
  this->secciones = new OrderedDictionary();
}
void Sucursal::setTelefono(string t) {
  this->telefonoSucursal = t;
}
void Sucursal::setDireccion(dtDireccion* d) {
  this->direccionSucursal = d;
}
string Sucursal::getNombre() {
  return this->nombre;
}
string Sucursal::getTelefonoSucursal() {
  return this->telefonoSucursal;
}
dtDireccion* Sucursal::getDireccionSucursal() {
  return this->direccionSucursal;
}

dtSucursal* Sucursal::getInfoSucursal() {
  return new dtSucursal(nombre, telefonoSucursal, direccionSucursal);
}

dtEmpresa* Sucursal::mostrarInfoEmpresa() {
  return this->empresa->getInfoEmpresa();
}

Seccion* Sucursal::getSeccion(string nombreSeccion) {
  return (Seccion*)(this->secciones->find(new String(nombreSeccion.c_str())));
}

ICollection* Sucursal::listarSecciones() {
  ICollection* ret = new List();
  IIterator* it = this->secciones->getIterator();
  while (it->hasCurrent()) {
    Seccion* seccion = (Seccion*)(it->getCurrent());
    ret->add(seccion->getInfoSeccion());
    it->next();
  }
  delete it;
  return ret;
}

bool Sucursal::checkSeccion(string seccion) {
  return this->secciones->member(new String(seccion.c_str()));
}

// ICollection* Sucursal::listarInfoSecciones() {
//   ICollection* ret = new List();
//   IIterator* it = this->secciones->getIterator();
//   while (it->hasCurrent()) {
//     Seccion* seccion = (Seccion*)(it->getCurrent());
//     ret->add(seccion->getInfoSeccion());
//     it->next();
//   }
//   delete it;
//   return ret;
// }

void Sucursal::agregarSeccion(string nombreSeccion, string interno) {
  this->secciones->add(new String(nombreSeccion.c_str()), new Seccion(nombreSeccion, interno, this));
}
void Sucursal::bajaSeccion(string nombreSeccion) {
  IKey* key = new String(nombreSeccion.c_str());
  Seccion* s = (Seccion*)secciones->find(key);
  secciones->remove(key);
  delete key;
  delete s;
}

void Sucursal::altaOfertaLaboral(string nombreSeccion, OfertaLaboral* infoOferta) {
  if (!checkSeccion(nombreSeccion)) throw invalid_argument("No existe la seccion");
  Seccion* s = (Seccion*)(this->secciones->find(new String(nombreSeccion.c_str())));
  s->altaOfertaLaboral(infoOferta);
}
void Sucursal::darBajaOferta(string nombreSec, int nroExp) {
  if (!checkSeccion(nombreSec)) throw invalid_argument("No existe la seccion");
  Seccion* s = (Seccion*)(this->secciones->find(new String(nombreSec.c_str())));
  s->darBajaOferta(nroExp);
}


Sucursal::~Sucursal() {
  IIterator* it = secciones->getIterator();
  Seccion* s;
  while (it->hasCurrent()) {
    s = (Seccion*)(it->getCurrent());
    it->next();
    secciones->remove(new String(s->getNombre().c_str()));
    delete s;
  }
  delete it;
}