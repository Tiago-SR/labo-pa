#include "../header/OfertaLaboral.h"

OfertaLaboral::OfertaLaboral(int nroExp, string titulo, string desc, int cantHoras, dtRangoSalario* salario, dtFecha* fI, dtFecha* fF, int cantPuestos, Seccion* seccion) {
  this->nroExpediente = nroExp;
  this->titulo = titulo;
  this->desc = desc;
  this->cantHoras = cantHoras;
  this->salario = salario;
  this->fechaInicio = fI;
  this->fechaFin = fF;
  this->cantPuestos = cantPuestos;
  this->seccionOferta = seccion;

  this->asignaturas = new OrderedDictionary();
  this->efectivos = new OrderedDictionary();
  this->anotarse = new OrderedDictionary();
}
OfertaLaboral::OfertaLaboral(dtOfertaLaboral* info, Seccion* seccion) {
  this->nroExpediente = info->getNroExpediente();
  this->titulo = info->getTitulo();
  this->desc = info->getDesc();
  this->cantHoras = info->getCantHoras();
  this->salario = info->getSalario();
  this->fechaInicio = info->getFechaInicio();
  this->fechaFin = info->getFechaFin();
  this->cantPuestos = info->getCantPuestos();
  this->seccionOferta = seccion;

  this->asignaturas = new OrderedDictionary();
  this->efectivos = new OrderedDictionary();
  this->anotarse = new OrderedDictionary();
}

void OfertaLaboral::setTitulo(string titulo) {
  this->titulo = titulo;
}
void OfertaLaboral::setDesc(string desc) {
  this->desc = desc;
} 
void OfertaLaboral::setCantHoras(int cantHoras) {
  this->cantHoras = cantHoras;
}
void OfertaLaboral::setSalario(dtRangoSalario* salario) {
  this->salario = salario;
}
void OfertaLaboral::setFechaInicio(dtFecha* fechaInicio) {
  this->fechaInicio = fechaInicio;
}
void OfertaLaboral::setFechaFin(dtFecha* fechaFin) {
  this->fechaFin = fechaFin;
}
void OfertaLaboral::setCantPuestos(int cantPuestos) {
  this->cantPuestos = cantPuestos;
}
int OfertaLaboral::getNroExpediente() {
  return this->nroExpediente;
}
string OfertaLaboral::getTitulo() {
  return this->titulo;
}
string OfertaLaboral::getDesc() {
  return this->desc;
}
int OfertaLaboral::getCantHoras() {
  return this->cantHoras;
}
dtRangoSalario* OfertaLaboral::getSalario() {
  return this->salario;
}
dtFecha* OfertaLaboral::getFechaInicio() {
  return this->fechaInicio;
}
dtFecha* OfertaLaboral::getFechaFin() {
  return this->fechaFin;
}
int OfertaLaboral::getCantPuestos() {
  return this->cantPuestos;
}


dtOfertaLaboral* OfertaLaboral::getInfoOfertaLaboral() {
  return new dtOfertaLaboral(this->nroExpediente, this->titulo, this->desc, this->cantHoras, this->salario, this->fechaInicio, this->fechaFin, this->cantPuestos);
}
void OfertaLaboral::modificarLlamado(string titulo, string desc, string cantHoras, string salarioMin, string salarioMax, string fechaInicio, string fechaFin, string cantPuestos) {
  if (!titulo.empty()) setTitulo(titulo);
  if (!desc.empty()) setDesc(desc);
  if (!cantHoras.empty()) setCantHoras(stoi(cantHoras));
  if (!salarioMin.empty() && !salarioMax.empty()) setSalario(new dtRangoSalario(stoi(salarioMin), stoi(salarioMax)));
  if (!fechaInicio.empty()) setFechaInicio(new dtFecha(fechaInicio));
  if (!fechaFin.empty()) setFechaFin(new dtFecha(fechaFin));
  if (!cantPuestos.empty()) setCantPuestos(stoi(cantPuestos));
}
ICollection* OfertaLaboral::listarAsignaturasOferta() {
  ICollection* ret = new List();
  IIterator* it = this->asignaturas->getIterator();
  while (it->hasCurrent()) {
    Asignatura* asig = (Asignatura*)(it->getCurrent());
    ret->add(asig->getInfoAsignatura());
    it->next();
  }
  delete it;
  return ret;
}

void OfertaLaboral::altaEntrevista(Estudiante* e, dtFecha* f) {
  Anotarse* a = (Anotarse*)(anotarse->find(new String(e->getEstudiante()->getCI().c_str())));
  a->altaEntrevista(f);
}

bool OfertaLaboral::checkAsignatura(int codigo) {
  return this->asignaturas->member(new Integer(codigo));
}

void OfertaLaboral::crearEfectivo(Efectivo* e) {
  efectivos->add(new String(e->mostrarInfoEstudiante()->getCI().c_str()), e);
}

void OfertaLaboral::asignarAsignatura(Asignatura* asig) {
  if (checkAsignatura(asig->getCodigo())) throw invalid_argument("La asignatura ya esta asignada a la oferta laboral");
  this->asignaturas->add(new Integer(asig->getCodigo()), asig);
}
ICollection* OfertaLaboral::listarAsignaturas() {
  ICollection* ret = new List();
  IIterator* it = this->asignaturas->getIterator();
  while (it->hasCurrent()) {
    Asignatura* asig = (Asignatura*)(it->getCurrent());
    ret->add(asig->getInfoAsignatura());
    it->next();
  }
  delete it;
  return ret;
}

bool OfertaLaboral::checkEstudiante(string ci) {
  return anotarse->member(new String(ci.c_str()));
}

void OfertaLaboral::inscribirEstudianteEnOferta(Estudiante* e, dtFecha* fecha) {
  if (checkEstudiante(e->getCi())) throw invalid_argument("El estudiante ya esta inscripto en la oferta laboral");
  Anotarse* a = new Anotarse(e, this, fecha);
  e->crearVinculo(a);
  anotarse->add(new String(e->getCi().c_str()), a);
} 
dtSeccion* OfertaLaboral::mostrarInfoSeccion() {
  return seccionOferta->getInfoSeccion();
}
dtSucursal* OfertaLaboral::mostrarInfoSucursal() {
  return seccionOferta->mostrarInfoSucursal();
}
dtEmpresa* OfertaLaboral::mostrarInfoEmpresa() {
  return seccionOferta->mostrarInfoEmpresa();
}
void OfertaLaboral::desvincularSeccion() {
  seccionOferta->darBajaOferta(getNroExpediente());
}


OfertaLaboral::~OfertaLaboral() {
}