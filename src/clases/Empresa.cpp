#include "../header/Empresa.h"

Empresa::Empresa(string nombre, string RUT) {
  this->nombre = nombre;
  this->RUT = RUT;
  this->sucursales = new OrderedDictionary();
}
void Empresa::setNombre(string nombre) {
  this->nombre = nombre;
}
string Empresa::getRUT() {
  return this->RUT;
}

string Empresa::getNombre() {
  return this->nombre;
}

dtEmpresa* Empresa::getInfoEmpresa() {
  return new dtEmpresa(this->RUT, this->nombre);
}

// ICollection* Empresa::listarInfoSucursales() {
//   ICollection* ret = new List();
//   IIterator* it = this->sucursales->getIterator();
//   while (it->hasCurrent()) {
//     Sucursal* sucursal = (Sucursal*)(it->getCurrent());
//     ret->add(sucursal->getInfoSucursal());
//     it->next();
//   }
//   delete it;
//   return ret;
// }
// ICollection* Empresa::listarInfoSecciones(string nombre) {
//   Sucursal* s = ((Sucursal*)(this->sucursales->find(new String(nombre.c_str()))));
//   if (s == NULL) {
//     return nullptr;
//   }
//   return s->listarInfoSecciones();
// }



void Empresa::agregarSucursal(string nombre, string telefono, dtDireccion* direccion) {
  if (sucursales->member(new String(nombre.c_str()))) throw invalid_argument("Ya existe una sucursal con ese nombre");
  sucursales->add(new String(nombre.c_str()), new Sucursal(nombre, telefono, direccion, this));
}
void Empresa::bajaSucursal(string nombre) {
  IKey* key = new String(nombre.c_str());
  Sucursal* s = (Sucursal*)sucursales->find(key);
  sucursales->remove(key);
  delete key;
  delete s;
}
bool Empresa::checkSucursal(string nombre) {
  return this->sucursales->member(new String(nombre.c_str()));
}
Sucursal* Empresa::getSucursal(string nombre) {
  return (Sucursal*)(this->sucursales->find(new String(nombre.c_str())));
}
ICollection* Empresa::listarSucursales() {
  ICollection* ret = new List();
  IIterator* it = this->sucursales->getIterator();
  while (it->hasCurrent()) {
    Sucursal* sucursal = (Sucursal*)(it->getCurrent());
    ret->add(sucursal);
    it->next();
  }
  delete it;
  return ret;
}
ICollection* Empresa::listarSecciones(string nombreSuc) {
  if (!checkSucursal(nombreSuc)) throw invalid_argument("No existe la sucursal");
  Sucursal* s = (Sucursal*)(this->sucursales->find(new String(nombreSuc.c_str())));
  return s->listarSecciones();
}

void Empresa::agregarSeccion(string nombreSuc, string nombreSeccion, string interno) {
  Sucursal* s = (Sucursal*)(this->sucursales->find(new String(nombreSuc.c_str())));
  s->agregarSeccion(nombreSeccion, interno);
}
void Empresa::bajaSeccion(string nombreSuc, string nombreSeccion) {
  if (!checkSucursal(nombreSuc)) throw invalid_argument("No existe la sucursal");
  Sucursal* s = (Sucursal*)(this->sucursales->find(new String(nombreSuc.c_str())));
  s->bajaSeccion(nombreSeccion);
}
bool Empresa::checkSeccion(string sucursal, string seccion) {
  Sucursal* su = (Sucursal*)(this->sucursales->find(new String(sucursal.c_str())));
  if (su == NULL) return false;
  return su->checkSeccion(seccion);
}


void Empresa::altaOfertaLaboral(string nombreSucursal, string nombreSeccion, OfertaLaboral* infoOferta) {
  if (!checkSucursal(nombreSucursal)) throw invalid_argument("No existe la sucursal");
  Sucursal* s = (Sucursal*)(this->sucursales->find(new String(nombreSucursal.c_str())));
  s->altaOfertaLaboral(nombreSeccion, infoOferta);
}
void Empresa::darBajaOferta(string nombreSuc, string nombreSec, int nroExp) {
  if (!checkSucursal(nombreSuc)) throw invalid_argument("No existe la sucursal");
  Sucursal* s = (Sucursal*)(this->sucursales->find(new String(nombreSuc.c_str())));
  s->darBajaOferta(nombreSec, nroExp);
}

Empresa::~Empresa() {
  IIterator* it = sucursales->getIterator();
  Sucursal* s;
  while (it->hasCurrent()) {
    s = (Sucursal*)(it->getCurrent());
    it->next();
    sucursales->remove(new String(s->getNombre().c_str()));
    delete s;
  }
  delete it;
}