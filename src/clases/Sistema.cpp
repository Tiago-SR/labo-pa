#include "../header/Sistema.h"

Sistema* Sistema::instance = NULL;

Sistema::Sistema() {
  this->empresas = new OrderedDictionary();
  this->estudiantes = new OrderedDictionary();
  this->asignaturas = new OrderedDictionary();
  this->ofertas = new OrderedDictionary();
  this->carreras = new OrderedDictionary();

  altaEmpresa("Empresa1", "1");
    altaSucursal("1", "suc", "098", new dtDireccion("Calle1", 1));
      altaSeccion("1", "suc", "sec", "099");
      altaSeccion("1", "suc", "sec2", "099");

    altaSucursal("1", "suc2", "098", new dtDireccion("Calle1", 1));
      altaSeccion("1", "suc2", "sec3", "099");
      altaSeccion("1", "suc2", "sec4", "099");

  altaEmpresa("Empresa2", "2");
  altaSucursal("2", "suc2", "096", new dtDireccion("Calle2", 2));
  altaSeccion("2", "suc2", "sec2", "097");

  altaAsignatura(1, "Matematicas", 10);
  altaAsignatura(2, "Ciencias", 10);
  altaAsignatura(3, "Programacion", 50);

  altaOfertaLaboral("1", "suc", "sec", new dtOfertaLaboral(1, "Dev", "Web-Dev", 30, new dtRangoSalario(10, 30), new dtFecha("11/06/2023"), new dtFecha("11/07/2023"), 1));
  altaOfertaLaboral("1", "suc", "sec2", new dtOfertaLaboral(2, "Dav", "dev-Dev", 30, new dtRangoSalario(10, 30), new dtFecha("03/3/2002"), new dtFecha("31/12/2023"), 1));
  altaOfertaLaboral("1", "suc2", "sec4", new dtOfertaLaboral(3, "Div", "Dev-Web", 30, new dtRangoSalario(10, 30), new dtFecha("03/3/2024"), new dtFecha("31/12/2024"), 1));
  altaOfertaLaboral("2", "suc2", "sec2", new dtOfertaLaboral(4, "otra", "Dev-Web", 30, new dtRangoSalario(10, 30), new dtFecha("03/3/2024"), new dtFecha("31/12/2024"), 1));

  altaEstudiante("534", "Tiago", "Silva", "09128", new dtDireccion("Calle1", 1), new dtFecha("03/09/2003"), 10);
  altaEstudiante("123", "Matias", "Bel", "099123456", new dtDireccion("Calle2", 2), new dtFecha("12/11/2003"), 0);
  altaEstudiante("231", "Cristian", "Ebs", "09875", new dtDireccion("Calle3", 3), new dtFecha("01/11/2000"), 0);
  altaEstudiante("321", "denis", "Bar", "342224", new dtDireccion("Calle4", 4), new dtFecha("01/01/2000"), 0);

  Empresa* e = getEmpresa("1");
  Sucursal* s = e->getSucursal("suc");
  Seccion* sec = s->getSeccion("sec");
  OfertaLaboral* o = sec->getOfertaLaboral(1);

  o->asignarAsignatura(getAsignatura(1));
  o->asignarAsignatura(getAsignatura(2));

  Estudiante* est = getEstudiante("123");
  est->agregarAsignatura(getAsignatura(1));
  est->agregarAsignatura(getAsignatura(2));
  est->agregarAsignatura(getAsignatura(3));

  est = getEstudiante("321");
  est->agregarAsignatura(getAsignatura(1));
  est->agregarAsignatura(getAsignatura(2));

  altaCarrera(1, "Ingenieria en Computacion", 15, nullptr);
  altaCarrera(2, "Ingenieria en Software", 30, nullptr);
  Carrera* c = getCarrera(1);
  c->agregarAsignatura(getAsignatura(1));
  c->agregarAsignatura(getAsignatura(3));

  c = getCarrera(2);
  c->agregarAsignatura(getAsignatura(2));
  c->agregarAsignatura(getAsignatura(3));
  // cout << ">>Sistema Cargado<<\n";
}

Sistema* Sistema::getInstance() {
  if (instance == NULL) instance = new Sistema();
  return instance;
}
dtFecha* Sistema::getFechaActual() {
  time_t now = time(nullptr);
  tm* ltm = localtime(&now);
  int dia = ltm->tm_mday;
  int mes = 1 + ltm->tm_mon;
  int anio = 1900 + ltm->tm_year;
  return new dtFecha(dia, mes, anio);
}


void Sistema::parseCsv() {

}



// --> empresas
bool Sistema::checkRUT(string rut) {
  return this->empresas->member(new String(rut.c_str()));
}
void Sistema::altaEmpresa(string nombre, string rut) {
  if (checkRUT(rut)) throw invalid_argument("RUT ya registrado");
  this->empresas->add(new String(rut.c_str()), new Empresa(nombre, rut));
}
void Sistema::bajaEmpresa(string r) {
  if (!checkRUT(r)) throw invalid_argument("Empresa no encontrada");
  IKey* key = new String(r.c_str());
  Empresa* empresa = (Empresa*)(empresas->find(key));
  IIterator* itOfertas = ofertas->getIterator();
  while (itOfertas->hasCurrent()) {
    OfertaLaboral* o = (OfertaLaboral*)itOfertas->getCurrent();
    if ((o->mostrarInfoEmpresa()->getRUT()) == r) 
      ofertas->remove(new Integer(o->getNroExpediente()));
    itOfertas->next();
  }
  empresas->remove(key);
  delete key;
  delete empresa;
}
Empresa* Sistema::getEmpresa(string rut) {
  Empresa* empresa = (Empresa*)(this->empresas->find(new String(rut.c_str())));
  if (empresa == NULL) throw invalid_argument("Empresa no encontrada");
  return empresa;
}

// --> sucursales
bool Sistema::checkSucursal(string rut, string nombre) {
  if (!checkRUT(rut)) return false;
  Empresa* e = (Empresa*)(this->empresas->find(new String(rut.c_str())));
  return e->checkSucursal(nombre);
}
void Sistema::altaSucursal(string rut, string nombre, string telefono, dtDireccion* direccion) {
  if (checkSucursal(rut, nombre)) throw invalid_argument("Ya existe una sucursal con ese nombre");
  Empresa* e = ((Empresa*)(this->empresas->find(new String(rut.c_str()))));
  e->agregarSucursal(nombre, telefono, direccion);
}
void Sistema::bajaSucursal(string rut, string nombre) {
  if (!checkRUT(rut)) throw invalid_argument("Empresa no encontrada");
  Empresa* e = (Empresa*)empresas->find(new String(rut.c_str()));
  IIterator* itOfertas = ofertas->getIterator();
  while (itOfertas->hasCurrent()) {
    OfertaLaboral* o = (OfertaLaboral*)itOfertas->getCurrent();
    if ((o->mostrarInfoEmpresa()->getRUT() == rut) && (o->mostrarInfoSucursal()->getNombre() == nombre))
      ofertas->remove(new Integer(o->getNroExpediente()));
    itOfertas->next();
  }
  e->bajaSucursal(nombre);
}


// --> secciones
bool Sistema::checkSeccion(string rut, string sucursal, string seccion) {
  if (!checkRUT(rut)) return false;
  Empresa* e = (Empresa*)(this->empresas->find(new String(rut.c_str())));
  return e->checkSeccion(sucursal, seccion);
}
void Sistema::altaSeccion(string rut, string nombreSuc, string nombreSeccion, string interno) {
  if (!checkRUT(rut)) throw invalid_argument("Empresa no encontrada");
  Empresa* e = ((Empresa*)(this->empresas->find(new String(rut.c_str()))));
  e->agregarSeccion(nombreSuc, nombreSeccion, interno);
}
void Sistema::bajaSeccion(string rut, string nombreSuc, string nombreSeccion) {
  if (!checkRUT(rut)) throw invalid_argument("Empresa no encontrada");
  Empresa* e = ((Empresa*)(this->empresas->find(new String(rut.c_str()))));
  IIterator* itOfertas = ofertas->getIterator();
  while (itOfertas->hasCurrent()) {
    OfertaLaboral* o = (OfertaLaboral*)itOfertas->getCurrent();
    if ((o->mostrarInfoEmpresa()->getRUT() == rut) && (o->mostrarInfoSucursal()->getNombre() == nombreSuc) && (o->mostrarInfoSeccion()->getNombre() == nombreSeccion))
      ofertas->remove(new Integer(o->getNroExpediente()));
    itOfertas->next();
  }
  e->bajaSeccion(nombreSuc, nombreSeccion);
}

// --> asignaturas
bool Sistema::checkAsignatura(int codigo) {
  return this->asignaturas->member(new Integer(codigo));
}
void Sistema::altaAsignatura(int codigo, string nombre, int creditos) {
  this->asignaturas->add(new Integer(codigo), new Asignatura(codigo, nombre, creditos));
}
void Sistema::bajaAsignatura(int codigo) {
  IKey* key = new Integer(codigo);
  Asignatura* asignatura = (Asignatura*)(this->asignaturas->find(key));
  if (asignatura == NULL) {
    delete key;
    delete asignatura;
    throw invalid_argument("Asignatura no encontrada");
  }
  this->asignaturas->remove(key);
  delete key;
  delete asignatura;
}
Asignatura* Sistema::getAsignatura(int codigo) {
  if (!checkAsignatura(codigo)) throw invalid_argument("Asignatura no encontrada");
  return (Asignatura*)(this->asignaturas->find(new Integer(codigo)));
}

// --> ofertas laborales
bool Sistema::checkOferta(int nroExp) {
  return this->ofertas->member(new Integer(nroExp));
}
void Sistema::altaOfertaLaboral(string rut, string nombreSucursal, string nombreSeccion, dtOfertaLaboral* infoOferta) {
  if (!checkRUT(rut)) throw invalid_argument("Empresa no encontrada");
  Empresa* e = ((Empresa*)(this->empresas->find(new String(rut.c_str()))));
  IKey* key = new Integer(infoOferta->getNroExpediente());
  this->ofertas->add(key, new OfertaLaboral(infoOferta, e->getSucursal(nombreSucursal)->getSeccion(nombreSeccion)));
  e->altaOfertaLaboral(nombreSucursal, nombreSeccion, (OfertaLaboral*)(this->ofertas->find(key)));
}
OfertaLaboral* Sistema::getOferta(int nroExp){
  return (OfertaLaboral*)ofertas->find(new Integer(nroExp));
}
void Sistema::seleccionarAsignatura(int codigo, int nroExp) {
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  if (!checkAsignatura(codigo)) throw invalid_argument("Asignatura no encontrada");
  OfertaLaboral* o = (OfertaLaboral*)(this->ofertas->find(new Integer(nroExp)));
  o->asignarAsignatura(getAsignatura(codigo));
}
ICollection* Sistema::listarOfertasActivasDeEmpresa(string rut) {
  if (!checkRUT(rut)) throw invalid_argument("Empresa no encontrada");
  ICollection* ret = new List();
  IIterator* it = ofertas->getIterator();
  while (it->hasCurrent()) {
    OfertaLaboral* o = (OfertaLaboral*)it->getCurrent();
    if (o->mostrarInfoEmpresa()->getRUT() == rut && (o->getFechaInicio()->menorQue(Sistema::getFechaActual()) && o->getFechaFin()->mayorQue(Sistema::getFechaActual())))
      ret->add(o->getInfoOfertaLaboral());
    it->next();
  }
  delete it;
  return ret;
}

// --> estudiantes
bool Sistema::checkEstudiante(string ci) {
  return this->estudiantes->member(new String(ci.c_str()));
}
void Sistema::altaEstudiante(string ci, string nombre, string apellido, string telefono, dtDireccion* dir, dtFecha* fechaNac, int creditos) {
  if (checkEstudiante(ci)) throw invalid_argument("Estudiante ya registrado");
  this->estudiantes->add(new String(ci.c_str()), new Estudiante(ci, nombre, apellido, telefono, dir, fechaNac, creditos));
}
void Sistema::bajaEstudiante(string ci) {
  IKey* key = new String(ci.c_str());
  Estudiante* estudiante = (Estudiante*)(this->estudiantes->find(key));
  if (estudiante == NULL) {
    delete key;
    delete estudiante;
    throw invalid_argument("Estudiante no encontrado");
  }
  this->estudiantes->remove(key);
  delete key;
  delete estudiante;
}
bool Sistema::checkAsignaturaDeEstudiante(string ci, int nroExp) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  Estudiante* e = ((Estudiante*)(this->estudiantes->find(new String(ci.c_str()))));
  return e->checkAsignatura(nroExp);
}
Estudiante* Sistema::getEstudiante(string ci) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  return (Estudiante*)(this->estudiantes->find(new String(ci.c_str())));
}

// --> carreras
bool Sistema::checkCarrera(int codigo){
  return this->carreras->member(new Integer(codigo));
}
bool Sistema::checkCarreraDeEstudiante(string ci, int codigo) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  Estudiante* e = ((Estudiante*)(this->estudiantes->find(new String(ci.c_str()))));
  return e->checkCarrera(codigo);
}
void Sistema::altaCarrera(int codigo, string nombre, int creditosNecesarios, IDictionary* asignaturas){
  if (checkCarrera(codigo)) throw invalid_argument("Codigo de carrera ya registrado");
  if (asignaturas == nullptr) 
    carreras->add(new Integer(codigo), new Carrera(codigo,nombre,creditosNecesarios));
  else 
    this->carreras->add(new Integer(codigo), new Carrera(codigo,nombre,creditosNecesarios,asignaturas));
}
IDictionary *Sistema::getCarreras() {
  return this->carreras;
}
void Sistema::agregarCarreraEstudiante(string ci, int codigo) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  if (!checkCarrera(codigo)) throw invalid_argument("Carrera no encontrada");
  Estudiante* e = ((Estudiante*)(this->estudiantes->find(new String(ci.c_str()))));
  e->agregarCarrera((Carrera*)(this->carreras->find(new Integer(codigo))));
}
void Sistema::quitarCarreraDeEstudiante(string ci, int codigo) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  if (!checkCarrera(codigo)) throw invalid_argument("Carrera no encontrada");
  Estudiante* e = ((Estudiante*)(this->estudiantes->find(new String(ci.c_str()))));
  e->quitarCarrera(codigo);
}
Carrera* Sistema::getCarrera(int codigo) {
  if (!checkCarrera(codigo)) throw invalid_argument("Carrera no encontrada");
  return (Carrera*)(this->carreras->find(new Integer(codigo)));
}
ICollection* Sistema::mostrarCarrerasDeEstudiante(string ci) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  Estudiante* e = ((Estudiante*)(this->estudiantes->find(new String(ci.c_str()))));
  return e->mostrarCarreras();
}
ICollection* Sistema::mostrarCarreras() {
  ICollection* ret = new List();
  IIterator* it = carreras->getIterator();
  while (it->hasCurrent()) {
    ret->add((Carrera*)(it->getCurrent()));
    it->next();
  }
  delete it;
  return ret;
}

// Caso de uso ModificarLlamado
dtOfertaLaboral* Sistema::getOfertaLaboral(int nroExp) {
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  return ((OfertaLaboral*)(ofertas->find(new Integer(nroExp))))->getInfoOfertaLaboral();
}
void Sistema::modificarLlamado(int nroExp, string titulo, string desc, string cantHoras, string salarioMin, string salarioMax, string fechaInicio, string fechaFin, string cantPuestos) {
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  OfertaLaboral* o = ((OfertaLaboral*)(ofertas->find(new Integer(nroExp))));
  o->modificarLlamado(titulo, desc, cantHoras, salarioMin, salarioMax, fechaInicio, fechaFin, cantPuestos);
}

// Caso de uso BajaLlamado
ICollection* Sistema::listarAsignaturasDeOferta(int nroExp) {
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  return (((OfertaLaboral*)(ofertas->find(new Integer(nroExp))))->listarAsignaturasOferta());
}

// Caso de uso Inscribir Estudiante
ICollection* Sistema::listarEstudiantesNoInscriptos(int nroExp) {
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  ICollection* ret = new List();
  IIterator* it = estudiantes->getIterator();
  Estudiante* e;
  while (it->hasCurrent()) {
    e = (Estudiante*)it->getCurrent();
    if (!e->estaVinculadoOferta(nroExp))
      ret->add(e->getEstudiante());
    it->next();
  }
  delete it;
  return ret;
}
ICollection* Sistema::listarEstudiantesInscriptos(int nroExp) {
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  ICollection* ret = new List();
  IIterator* it = estudiantes->getIterator();
  Estudiante* e;
  while (it->hasCurrent()) {
    e = (Estudiante*)it->getCurrent();
    if (e->estaVinculadoOferta(nroExp))
      ret->add(e->getEstudiante());
    it->next();
  }
  delete it;
  return ret;
}


// Caso de uso Alta Entrevista
void Sistema::altaEntrevista(string ci, int nroExp, string fecha) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  if (!checkEstudianteInscripto(ci, nroExp)) throw invalid_argument("Estudiante no inscripto");
  dtFecha* f = new dtFecha(fecha);
  if (f->menorQue(Sistema::getFechaActual())) throw invalid_argument("Fecha invalida");
  Estudiante* e = ((Estudiante*)(estudiantes->find(new String(ci.c_str()))));
  OfertaLaboral* o = ((OfertaLaboral*)(ofertas->find(new Integer(nroExp))));
  o->altaEntrevista(e, f);
}


// Caso de uso Asignar Oferta A Estudiante
bool Sistema::checkEstudianteInscripto(string ci, int nroExp) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  Estudiante* e = ((Estudiante*)(estudiantes->find(new String(ci.c_str()))));
  return e->estaVinculadoOferta(nroExp);
}
void Sistema::asignarOfertaEstudiante(string ci, int nroExp, float sueldo) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  if (!checkEstudianteInscripto(ci, nroExp)) throw invalid_argument("Estudiante ya inscripto");
  Estudiante* e = ((Estudiante*)(estudiantes->find(new String(ci.c_str()))));
  OfertaLaboral* o = ((OfertaLaboral*)(ofertas->find(new Integer(nroExp))));
  Efectivo* ef = new Efectivo(Sistema::getFechaActual(), sueldo, e, o);
  e->crearEfectivo(ef);
  o->crearEfectivo(ef);
}
void Sistema::inscribirEstudianteEnOferta(string ci, int nroExp) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  if (checkEstudianteInscripto(ci, nroExp)) throw invalid_argument("Estudiante ya inscripto");
  Estudiante* e = ((Estudiante*)(estudiantes->find(new String(ci.c_str()))));
  OfertaLaboral* o = ((OfertaLaboral*)(ofertas->find(new Integer(nroExp))));
  IIterator* it = o->listarAsignaturasOferta()->getIterator();
  while (it->hasCurrent()) {
    Asignatura* a = (Asignatura*)(it->getCurrent());
    if(!e->checkAsignatura(a->getCodigo())) throw invalid_argument("Estudiante no cumple con los requisitos");
    it->next();
  }
  o->inscribirEstudianteEnOferta(e, Sistema::getFechaActual());
}

//  --> primer Diagrama de comunicacion
ICollection* Sistema::listarEmpresas() {
  ICollection* ret = new List();
  IIterator* it = this->empresas->getIterator();
  while (it->hasCurrent()) {
    Empresa* empresa = (Empresa*)(it->getCurrent());
    ret->add(empresa->getInfoEmpresa());
    it->next();
  }
  delete it;
  return ret;
}
ICollection* Sistema::listarSucursales(string rut) {
  if(!checkRUT(rut)) throw invalid_argument("Empresa no encontrada");
  Empresa* e = ((Empresa*)(this->empresas->find(new String(rut.c_str()))));
  return e->listarSucursales();
}
ICollection* Sistema::listarSecciones(string rut, string nombreSucursal) {
  if (!checkRUT(rut)) throw invalid_argument("Empresa no encontrada");
  Empresa* e = ((Empresa*)(this->empresas->find(new String(rut.c_str()))));
  return e->listarSecciones(nombreSucursal);
}
ICollection* Sistema::listarAsignaturas() {
  ICollection* ret = new List();
  IIterator* it = this->asignaturas->getIterator();
  while (it->hasCurrent()) {
    Asignatura* asignatura = (Asignatura*)(it->getCurrent());
    ret->add(asignatura->getInfoAsignatura());
    it->next();
  }
  delete it;
  return ret;
}
ICollection* Sistema::listarOfertasActivas() {
  ICollection* ret = new List();
  IIterator* it = ofertas->getIterator();
  while (it->hasCurrent()) {
    OfertaLaboral* o = (OfertaLaboral*)it->getCurrent();
    if (o->getFechaInicio()->menorQue(Sistema::getFechaActual()) && o->getFechaFin()->mayorQue(Sistema::getFechaActual()))
      ret->add(o->getInfoOfertaLaboral());
    it->next();
  }
  delete it;
  return ret;
}

// --> cuarto Diagrama de comunicacion
ICollection* Sistema::listarEstudiantes() {
  ICollection* ret = new List();
  IIterator* it = this->estudiantes->getIterator();
  while (it->hasCurrent()) {
    Estudiante* estudiante = (Estudiante*)(it->getCurrent());
    ret->add(estudiante->getEstudiante());
    it->next();
  }
  delete it;
  return ret;
}
dtEstudianteTodo* Sistema::mostrarEstudiante(string ci) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  return ((Estudiante*)(estudiantes->find(new String(ci.c_str()))))->getEstudianteTodo();
}
ICollection* Sistema::mostrarAsignaturas(string ci) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  return ((Estudiante*)(estudiantes->find(new String(ci.c_str()))))->mostrarAsignaturas();
}
ICollection* Sistema::mostrarLlamadoEstudiante(string ci) {
  if (!checkEstudiante(ci)) throw invalid_argument("Estudiante no encontrado");
  return ((Estudiante*)(estudiantes->find(new String(ci.c_str()))))->mostrarLlamadosEstudiante();
}
dtSeccion* Sistema::mostrarInfoSeccionDeOferta(int nroExp) {
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  return ((OfertaLaboral*)(ofertas->find(new Integer(nroExp))))->mostrarInfoSeccion();
}
dtSucursal* Sistema::mostrarInfoSucursalDeOferta(int nroExp) {
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  return ((OfertaLaboral*)(ofertas->find(new Integer(nroExp))))->mostrarInfoSucursal();
}
dtEmpresa* Sistema::mostrarInfoEmpresaDeOferta(int nroExp) {
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  return ((OfertaLaboral*)(ofertas->find(new Integer(nroExp))))->mostrarInfoEmpresa();
}

// --> quinto Diagrama de comunicacion
void Sistema::darBajaOferta(string rut, string nombreSuc, string nombreSec, int nroExp) {
  if (!checkRUT(rut)) throw invalid_argument("Empresa no encontrada");
  Empresa* e = ((Empresa*)(empresas->find(new String(rut.c_str()))));
  try {
    e->darBajaOferta(nombreSuc, nombreSec, nroExp);
    OfertaLaboral* o = (OfertaLaboral*)(ofertas->find(new Integer(nroExp)));
    ofertas->remove(new Integer(nroExp));
    delete o;
  } catch (invalid_argument& e) {
    throw e;
  }
}
void Sistema::darBajaOferta(int nroExp) {
  if (!checkOferta(nroExp)) throw invalid_argument("Oferta no encontrada");
  OfertaLaboral* o = (OfertaLaboral*)(ofertas->find(new Integer(nroExp)));
  o->desvincularSeccion();
  ofertas->remove(new Integer(nroExp));
  delete o;
}