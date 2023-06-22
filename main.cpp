#include <iostream>
#include <iomanip> 
#include <sstream>
using namespace std;
#include "src/header/Factory.h"
#ifdef _WIN32
  const char* clear = "cls";
#elif defined(__unix__) || defined(__unix)
  const char* clear = "clear";
#endif

ISistema* sis = Factory::getISistema();


// separar a otro archivo
bool esNumero (const string s) {
  return !s.empty() && s.find_first_not_of("0123456789") == string::npos;
}
void esperarParaContinuar(bool c = true) {
  cout<<"\n\nPresione enter para continuar...\n";
  cin.get();
  system(clear);
}
bool esFecha(string fecha) {
  if (fecha.length() != 10) return false;
  if (fecha[2] != '/' || fecha[5] != '/') return false;
  string dia = fecha.substr(0, 2);
  string mes = fecha.substr(3, 2);
  string anio = fecha.substr(6, 4);
  if (!esNumero(dia) || !esNumero(mes) || !esNumero(anio)) return false;
  int d = stoi(dia);
  int m = stoi(mes);
  int a = stoi(anio);
  if (d < 1 || d > 31) return false;
  if (m < 1 || m > 12) return false;
  if (a < 2022) return false;
  return true;
}
bool esMayorFecha(string fecha1, string fecha2) {
  string dia1 = fecha1.substr(0, 2);
  string mes1 = fecha1.substr(3, 2);
  string anio1 = fecha1.substr(6, 4);
  string dia2 = fecha2.substr(0, 2);
  string mes2 = fecha2.substr(3, 2);
  string anio2 = fecha2.substr(6, 4);
  int d1 = stoi(dia1);
  int m1 = stoi(mes1);
  int a1 = stoi(anio1);
  int d2 = stoi(dia2);
  int m2 = stoi(mes2);
  int a2 = stoi(anio2);
  if (a1 > a2) return true;
  if (a1 < a2) return false;
  if (m1 > m2) return true;
  if (m1 < m2) return false;
  if (d1 > d2) return true;
  if (d1 < d2) return false;
  return false;
}
// hasta aca

void listarEmpresas(bool i = true) {
  IIterator* it = sis->listarEmpresas()->getIterator();
  if (!it->hasCurrent()) {
    cout << "No hay empresas" << endl;
    delete it;
    esperarParaContinuar();
    return;
  }
  cout << "  RUT  | Nombre " << endl;
  cout << "------------------" << endl;
  while (it->hasCurrent()) {
    dtEmpresa* e = (dtEmpresa*)(it->getCurrent());
    cout << left << setw(7) << e->getRUT() << "| " << setw(6) << e->getNombre() << endl;
    it->next();
  }
  delete it;
  if (i)
    esperarParaContinuar();
}
void ingresarEmpresa() {
  cout << "Opcion seleccionada: Crear Empresa" << endl;

  cout << "Ingrese el RUT de la empresa: ";
  string rut;
  getline(cin, rut);
  while (rut.empty()) {
    system(clear);
    cout << "El RUT no puede estar vacio. Por favor, ingrese un RUT: ";
    getline(cin, rut);
  }
  if(sis->checkRUT(rut)) {
    cout << "El RUT ya existe.\n";
    esperarParaContinuar();
    return;
  }

  cout << "Ingrese el nombre de la empresa: ";
  string nombre;
  getline(cin, nombre);
  while (nombre.empty()) {
    system(clear);
    cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre: ";
    getline(cin, nombre);
  }

  try {
    sis->altaEmpresa(nombre, rut);
  } catch(const exception& e) {
    cerr << "Error: " << e.what() << '\n';
  }

}
void eliminarEmpresa() {
  cout << "Opcion seleccionada: Eliminar empresa" << endl;
  cout << "Ingrese el RUT de la empresa: ";
  string rut;
  getline(cin, rut);
  while (rut.empty()) {
    system(clear);
    cout << "El RUT no puede estar vacio. Por favor, ingrese un RUT: ";
    getline(cin, rut);
  }
  if(!sis->checkRUT(rut)) {
    cout << "La empresa " << rut << " no existe\n";
    esperarParaContinuar();
    return;
  }
  try {
    sis->bajaEmpresa(rut);
  } catch(const exception& e) {
    cerr << "Error: " << e.what() << '\n';
  }
}
void subMenuEmpresa() {
  string opcion;
  do {
    cout << "----- Sub Menu Empresa -----" << endl;
    cout << "1. Listar empresas" << endl;
    cout << "2. Crear empresa" << endl;
    cout << "3. Eliminar empresa" << endl;
    cout << "0. Volver al menu principal" << endl;
    getline(cin, opcion);
    int opt; 
    if (esNumero(opcion)) opt = stoi(opcion);
    else opt = -1;
    system(clear);
    switch (opt) {
      case 1:
        listarEmpresas();
        break;
      case 2:
        ingresarEmpresa();
        break;
      case 3:
        eliminarEmpresa();
        break;
      case 0:
        return;
      default:
        system(clear);
        cout << "Opcion invalida. Por favor, ingrese una opcion valida." << endl;
        esperarParaContinuar();
        system(clear);
        break;
    }
  } while(opcion != "0");
}


void listarSucursales(string r = "", bool c = true) {
  string rut;
  if (c) {
    cout << "Opcion seleccionada: Listar sucursales" << endl;
    cout << "Ingrese el RUT de la empresa: ";
    getline(cin, rut);
    while (rut.empty()) {
      system(clear);
      cout << "El RUT no puede estar vacio. Por favor, ingrese un RUT: ";
      getline(cin, rut);
    }
    if (!sis->checkRUT(rut)) {
      cout << "La empresa " << rut << " no existe";
      esperarParaContinuar();
      return;
    }
  } else rut = r;

  ICollection* sucursales = sis->listarSucursales(rut);

  if (sucursales->isEmpty()) {
    cout << "La empresa " << rut << " no tiene sucursales";
    delete sucursales;
    esperarParaContinuar();
    return;
  }
  IIterator* it = sucursales->getIterator();
  cout << "  Nombre  | Telefono |  Calle   |  Numero  " << endl;
  cout << "-------------------------------------------" << endl;
  while (it->hasCurrent()) {
    dtSucursal* s = (dtSucursal*)(it->getCurrent());
    cout << left << setw(10) << s->getNombre() << "| " << setw(9) << s->getTelefono() << "| " << setw(9) << s->getDireccion()->getCalle() << "| " << setw(10) << s->getDireccion()->getNumero() << endl;
    it->next();
  }
  delete sucursales;
  delete it;
  if (c)
    esperarParaContinuar();
}
void ingresarSucursal() {
  cout << "Opcion seleccionada: Crear Sucursal" << endl;
  cout << "Ingrese el RUT de la empresa a la que agregara la Sucursal: ";
  string rut;
  getline(cin, rut);
  while (rut.empty()) {
    system(clear);
    cout << "El RUT no puede estar vacio y debe existir. Por favor, ingrese un RUT correcto: ";
    getline(cin, rut);
  }
  if (!sis->checkRUT(rut)) {
    cout << "La empresa " << rut << " no existe\n";
    esperarParaContinuar();
    return;
  }

  cout << "Ingrese el nombre de la sucursal: ";
  string nombre;
  getline(cin, nombre);
  while (nombre.empty() || sis->checkSucursal(rut, nombre)) {
    system(clear);
    cout << "El nombre no puede estar vacio ni ya existir. Por favor, ingrese un nombre correcto: ";
    getline(cin, nombre);
  }

  if (sis->checkSucursal(rut, nombre)) {
    cout << "El nombre ya existe.\n";
    esperarParaContinuar();
    return;
  }


  cout << "Ingrese el telefono de la sucursal: ";
  string telefono;
  getline(cin, telefono);
  while (telefono.empty() || !esNumero(telefono)) {
    system(clear);
    cout << "El telefono no puede estar vacio y deben ser numeros. Por favor, ingrese un telefono correcto: ";
    getline(cin, telefono);
  }

  cout << "Ingrese el nombre de la calle: ";
  string nombreCalle;
  getline(cin, nombreCalle);
  while (nombreCalle.empty()) {
    system(clear);
    cout << "El nombre de la calle no puede estar vacio. Por favor, ingrese un nombre correcto: ";
    getline(cin, nombreCalle);
  }

  cout << "Ingrese el numero de calle: ";
  string nroCalle;
  getline(cin, nroCalle);
  while (nroCalle.empty() || !esNumero(nroCalle)) {
    system(clear);
    cout << "El numero de calle no puede estar vacio y deben ser numeros. Por favor, ingrese un numero de calle correcto: ";
    getline(cin, nroCalle);
  }
  try {
    sis->altaSucursal(rut, nombre, telefono, new dtDireccion(nombreCalle, stoi(nroCalle)));
  } catch(const exception& e) {
    cerr << "Error: " << e.what() << '\n';
  }
}
void eliminarSucursal() {
  cout << "Opcion seleccionada: Eliminar Sucursal" << endl;
  cout << "Ingrese el RUT de la empresa a la que eliminara la Sucursal: ";
  string rut;
  getline(cin, rut);
  while (rut.empty()) {
    system(clear);
    cout << "El RUT no puede estar vacio. Por favor, ingrese un RUT correcto: ";
    getline(cin, rut);
  }

  if (!sis->checkRUT(rut)) {
    cout << "La empresa " << rut << " no existe\n";
    esperarParaContinuar();
    return;
  }

  cout << "Ingrese el nombre de la sucursal: ";
  string nombre;
  getline(cin, nombre);
  while (nombre.empty()) {
    system(clear);
    cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
    getline(cin, nombre);
  }

  if (!sis->checkSucursal(rut, nombre)) {
    cout << "En la empresa " << rut << " no existe una sucursal con el nombre " << nombre << endl;
    esperarParaContinuar();
    return;
  }

  try {
    sis->bajaSucursal(rut, nombre);
  } catch(const exception& e) {
    cerr << "Error: " << e.what() << '\n';
  }
}
void subMenuSucursal() {
  string opcion;
  do {
    cout << "----- Sub Menu Sucursal -----" << endl;
    cout << "1. Listar sucursales" << endl;
    cout << "2. Crear sucursal" << endl;
    cout << "3. Eliminar sucursal" << endl;
    cout << "0. Volver al menu principal" << endl;
    getline(cin, opcion);
    int opt; 
    if (esNumero(opcion)) opt = stoi(opcion);
    else opt = -1;
    system(clear);
    switch (opt) {
      case 1:
        listarSucursales();
        break;
      case 2:
        ingresarSucursal();
        break;
      case 3:
        eliminarSucursal();
        break;
      case 0:
        return;
      default:
        system(clear);
        cout << "Opcion invalida. Por favor, ingrese una opcion valida." << endl;
        esperarParaContinuar();
        system(clear);
        break;
    }
  } while (opcion != "0");
}


void listarSecciones(string r = "", string s = "", bool c = true) {
  string rut, nombreSucursal;
  if (c) { 
    cout << "Opcion seleccionada: Listar secciones" << endl;
    cout << "Ingrese el RUT de la empresa: ";
    getline(cin, rut);
    while (rut.empty()) {
      system(clear);
      cout << "El RUT no puede estar vacio. Por favor, ingrese un RUT correcto: ";
      getline(cin, rut);
    }
    if (!sis->checkRUT(rut)) {
      cout << "La empresa " << rut << " no existe\n";
      esperarParaContinuar();
      return;
    }

    cout << "Ingrese el nombre de la sucursal: ";
    getline(cin, nombreSucursal);
    while (nombreSucursal.empty()) {
      system(clear);
      cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
      getline(cin, nombreSucursal);
    }

    if (!sis->checkSucursal(rut, nombreSucursal)) {
      cout << "En la empresa " << rut << " no existe una sucursal con el nombre " << nombreSucursal << endl;
      esperarParaContinuar();
      return;
    }
  } else {
    rut = r;
    nombreSucursal = s;
  }

  
  IIterator* it = sis->listarSecciones(rut, nombreSucursal)->getIterator();
  if (!it->hasCurrent()) {
    cout << "La empresa " << rut << " en la sucursal " << nombreSucursal << " no tiene secciones\n";
    delete it;
    esperarParaContinuar();
    return;
  }
  cout << "  Nombre  | Interno |" << endl;
  cout << "---------------------" << endl;
  while (it->hasCurrent()) {
    dtSeccion* s = (dtSeccion*)(it->getCurrent());
    cout << left << setw(10) << s->getNombre() << "| " << setw(9) << s->getInterno() << endl;
    it->next();
  }
  delete it;
  if (c) 
    esperarParaContinuar();
}
void ingresarSeccion() {
  cout << "Opcion seleccionada: Crear Seccion" << endl;
  string rut, nombreSucursal, nombreSeccion, interno;
  cout << "Ingrese el RUT de la empresa a la que agregara la Seccion: ";
  getline(cin, rut);
  while (rut.empty()) {
    system(clear);
    cout << "El RUT no puede estar vacio. Por favor, ingrese un RUT correcto: ";
    getline(cin, rut);
  }
  if (!sis->checkRUT(rut)) {
    cout << "La empresa " << rut << " no existe\n";
    esperarParaContinuar();
    return;
  }

  cout << "Ingrese el nombre de la sucursal: ";
  getline(cin, nombreSucursal);
  while (nombreSucursal.empty()) {
    system(clear);
    cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
    getline(cin, nombreSucursal);
  }

  if (!sis->checkSucursal(rut, nombreSucursal)) {
    cout << "En la empresa " << rut << " no existe una sucursal con el nombre " << nombreSucursal << endl;
    esperarParaContinuar();
    return;
  }

  cout << "Ingrese el nombre de la seccion: ";
  getline(cin, nombreSeccion);
  while (nombreSeccion.empty()) {
    system(clear);
    cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
    getline(cin, nombreSeccion);
  }

  cout << "Ingrese el numero interno: ";
  getline(cin, interno);
  while (interno.empty()) {
    system(clear);
    cout << "El numero interno no puede estar vacio. Por favor, ingrese un numero interno correcto: ";
    getline(cin, interno);
  }
  try {
    sis->altaSeccion(rut, nombreSucursal, nombreSeccion, interno);
  } catch(const exception& e) {
    cerr << "Error: " << e.what() << '\n';
  }

}
void eliminarSeccion() {
  cout << "Opcion seleccionada: Eliminar Seccion" << endl;
  string rut, nombreSucursal, nombreSeccion;
  cout << "Ingrese el RUT de la empresa a la que eliminara la Seccion: ";
  getline(cin, rut);
  while (rut.empty()) {
    system(clear);
    cout << "El RUT no puede estar vacio. Por favor, ingrese un RUT correcto: ";
    getline(cin, rut);
  }

  if (!sis->checkRUT(rut)) {
    cout << "La empresa " << rut << " no existe\n";
    esperarParaContinuar();
    return;
  }

  cout << "Ingrese el nombre de la sucursal: ";
  getline(cin, nombreSucursal);
  while (nombreSucursal.empty()) {
    system(clear);
    cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
    getline(cin, nombreSucursal);
  }

  if (!sis->checkSucursal(rut, nombreSucursal)) {
    cout << "En la empresa " << rut << " no existe una sucursal con el nombre " << nombreSucursal << endl;
    esperarParaContinuar();
    return;
  }

  cout << "Ingrese el nombre de la seccion a borrar: ";
  getline(cin, nombreSeccion);
  while (nombreSeccion.empty()) {
    system(clear);
    cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
    getline(cin, nombreSeccion);
  }
  try {
    sis->bajaSeccion(rut, nombreSucursal, nombreSeccion);
  } catch(const exception& e) {
    cerr << "Error: " << e.what() << '\n';
  }
  esperarParaContinuar();
  system(clear);
}
void subMenuSeccion() {
  string opcion;
  do {
    cout << "----- Sub Menu Seccion -----" << endl;
    cout << "1. Listar secciones" << endl;
    cout << "2. Crear seccion" << endl;
    cout << "3. Eliminar seccion" << endl;
    cout << "0. Volver al menu principal" << endl;
    getline(cin, opcion);
    int opt; 
    if (esNumero(opcion)) opt = stoi(opcion);
    else opt = -1;
    system(clear);
    switch (opt) {
      case 1:
        listarSecciones();
        break;
      case 2:
        ingresarSeccion();
        break;
      case 3:
        eliminarSeccion();
        break;
      case 0:
        return;
      default:
        system(clear);
        cout << "Opcion invalida. Por favor, ingrese una opcion valida." << endl;
        esperarParaContinuar();
        system(clear);
        break;
    }
  } while (opcion != "0");
}


void listarAsignaturas(bool c = true) {
  IIterator* it = sis->listarAsignaturas()->getIterator();
  if (!it->hasCurrent()) {
    cout << "No hay asignaturas registradas" << endl;
    delete it;
    esperarParaContinuar();
    return;
  }
  cout << left << setw(10) << "Codigo" << "| " << setw(10) << "Nombre" << "| " << setw(8) << "Creditos" << endl;
  cout << "--------------------------------" << endl;
  while (it->hasCurrent()) {
    dtAsignatura* a = (dtAsignatura*)(it->getCurrent());
    cout << left << setw(10) << a->getCodigo() << "| " << setw(10) << a->getNombre() << "| " << setw(8) << a->getCreditos() << endl;
    it->next();
  }
  delete it;
  if (c)
    esperarParaContinuar();
}
void ingresarAsignatura() {
  cout << "Opcion seleccionada: Crear asignatura" << endl;

  cout << "Ingrese el codigo de la asignatura: ";
  string codigo;
  getline(cin, codigo);
  while (codigo.empty() || !esNumero(codigo)) {
    system(clear);
    cout << "El codigo no puede estar vacio y debe ser un numero. Por favor, ingrese un codigo correcto: ";
    getline(cin, codigo);
  }
  if(sis->checkAsignatura(stoi(codigo))) {
    cout << "El codigo ya existe.\n";
    esperarParaContinuar();
    return;
  }

  cout << "Ingrese el nombre de la asignatura: ";
  string nombre;
  getline(cin, nombre);
  while (nombre.empty()) {
    system(clear);
    cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
    getline(cin, nombre);
  }

  cout << "Ingrese la cantidad de creditos: ";
  string creditos;
  getline(cin, creditos);
  while (creditos.empty() || !esNumero(creditos) || stoi(creditos) < 0) {
    system(clear);  
    cout << "La cantidad de creditos no puede estar vacia y debe ser un numero mayor a 0. Por favor, ingrese una cantidad de creditos correcta: ";
    getline(cin, creditos);
  }

  try {
    sis->altaAsignatura(stoi(codigo), nombre, stoi(creditos));
    cout << "Asignatura creada con exito.\n";
    esperarParaContinuar();

  } catch(const std::exception& e) {
    cerr << "Error: " << e.what() << '\n';
  }

}
void eliminarAsignatura() {
  cout << "Opcion seleccionada: Eliminar asignatura" << endl;

  cout << "Ingrese el codigo de la asignatura: ";
  string codigo;
  getline(cin, codigo);
  while (codigo.empty() || !esNumero(codigo)) {
    system(clear);
    cout << "El codigo no puede estar vacio y debe ser un numero. Por favor, ingrese un codigo correcto: ";
    getline(cin, codigo);
  }
  if(!sis->checkAsignatura(stoi(codigo))) {
    cout << "El codigo no existe.\n";
    esperarParaContinuar();
    return;
  }


  try {
    sis->bajaAsignatura(stoi(codigo));
  }catch(const std::exception& e) {
    cerr << "Error: " << e.what() << '\n';
  }
}
void subMenuAsignaturas() {
  string opcion;
  do {
    cout << "----- Sub Menu Seccion -----" << endl;
    cout << "1. Listar asignatuas" << endl;
    cout << "2. Crear asignatua" << endl;
    cout << "3. Eliminar asignatua" << endl;
    cout << "0. Volver al menu principal" << endl;
    getline(cin, opcion);
    int opt; 
    if (esNumero(opcion)) opt = stoi(opcion);
    else opt = -1;
    system(clear);
    switch (opt) {
      case 1:
        listarAsignaturas();
        break;
      case 2:
        ingresarAsignatura();
        break;
      case 3:
        eliminarAsignatura();
        break;
      case 0:
        return;
      default:
        system(clear);
        cout << "Opcion invalida. Por favor, ingrese una opcion valida." << endl;
        esperarParaContinuar();
        system(clear);
        break;
    }
  } while (opcion != "0");
}


void listarOfertas(bool c = true) {
  IIterator* it = sis->listarOfertasActivas()->getIterator(), *itAsig;
  if (!it->hasCurrent()) {
    cout << "No hay ofertas registradas" << endl;
    delete it;
    esperarParaContinuar();
    return;
  }
  while (it->hasCurrent()) {
    dtOfertaLaboral* o = (dtOfertaLaboral*)(it->getCurrent());
    cout << "Nro Expediente: " << o->getNroExpediente() << endl;
    cout << "\tTitulo: " << o->getTitulo() << endl;
    cout << "\tDescripcion: " << o->getDesc() << endl;
    cout << "\tCantidad de horas semanales: " << o->getCantHoras() << endl;
    cout << "\tSalario min/max: $" << o->getSalario()->getSalarioMin() << "/$" << o->getSalario()->getSalarioMax() << endl;
    cout << "\tFecha de inicio: " << o->getFechaInicio()->getFecha() << endl;
    cout << "\tFecha de fin: " << o->getFechaFin()->getFecha() << endl;
    cout << "\tCant. de puestos disponibles: " << o->getCantPuestos() << endl;
    cout << "\tAsignaturas requeridas:\n";
    itAsig = sis->listarAsignaturasDeOferta(o->getNroExpediente())->getIterator();
    if (!itAsig->hasCurrent()) {
      cout << "\t\tNo hay asignaturas registradas\n\n";
      it->next();
      continue;
    }
    while(itAsig->hasCurrent()) {
      cout << "\t\t" << ((dtAsignatura*)(itAsig->getCurrent()))->getNombre() << endl;
      itAsig->next();
    }
    cout << endl; 
    it->next();
  }
  delete it;
  if (c)
    esperarParaContinuar();
}
void listarOfertaDeEmpresa() {
  cout << "Opcion seleccionada: Listar ofertas activas de una empresa" << endl;

  cout << "Ingrese el RUT de la empresa: ";
  string rut;
  getline(cin, rut);
  while (rut.empty()) {
    system(clear);
    cout << "El rut no puede estar vacio. Por favor, ingrese un rut correcto: ";
    getline(cin, rut);
  }
  if(!sis->checkRUT(rut)) {
    cout << "La empresa " << rut << " no existe.\n";
    esperarParaContinuar();
    return;
  }

  IIterator* it = sis->listarOfertasActivasDeEmpresa(rut)->getIterator();
  if (!it->hasCurrent()) {
    cout << "La empresa " << rut << " no tiene ofertas registradas" << endl;
    delete it;
    esperarParaContinuar();
    return;
  }
  cout << "NroExp | Titulo" << endl;
  cout << "-------|-------" << endl;
  while (it->hasCurrent()) {
    dtOfertaLaboral* o = (dtOfertaLaboral*)(it->getCurrent());
    cout << left << setw(7) << o->getNroExpediente() << "| " << setw(15) << o->getTitulo() << endl;
    it->next();
  }
  delete it;
  esperarParaContinuar();
}
void ingresarOferta(string r = "", string nSuc = "", string nSec = "", string nExp = "", bool c = true) {
  cout << "Opcion seleccionada: Crear Oferta Laboral" << endl;

  //rut, nombre seccion y nombre suc
  string rut;
  string nombreSuc;
  string nombreSec;
  string nroExp;

  if (c) {
    cout << "Ingrese el RUT de la empresa: ";
    getline(cin, rut);
    while (rut.empty()) {
      system(clear);
      cout << "El rut no puede estar vacio. Por favor, ingrese un rut correcto: ";
      getline(cin, rut);
    }
    if(!sis->checkRUT(rut)) {
      cout << "La empresa " << rut << " no existe.\n";
      esperarParaContinuar();
      return;
    }
    cout << "Ingrese el nombre de la sucursal: ";
    getline(cin, nombreSuc);
    while (nombreSuc.empty()) {
      system(clear);
      cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
      getline(cin, nombreSuc);
    }
    if(!sis->checkSucursal(rut, nombreSuc)) {
      cout << "Dentro de la empresa " << rut << " no existe una sucursal con el nombre " << nombreSuc << ".\n";
      esperarParaContinuar();
      return;
    }
    cout << "Ingrese el nombre de la seccion: ";
    getline(cin, nombreSec);
    while (nombreSec.empty()) {
      system(clear);
      cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
      getline(cin, nombreSec);
    }
    if(!sis->checkSeccion(rut, nombreSuc, nombreSec)) {
      cout << "Dentro de la sucursal " << nombreSuc << " de la empresa " << rut << " no existe una seccion con el nombre " << nombreSec << ".\n";
      esperarParaContinuar();
      return;
    }
    cout << "Ingrese el numero de expediente de la oferta: ";
    getline(cin, nroExp);
    while (nroExp.empty() || !esNumero(nroExp)) {
      system(clear);
      cout << "El numero de expediente no puede estar vacio y debe ser un numero. Por favor, ingrese un numero correcto: ";
      getline(cin, nroExp);
    }
    if(sis->checkOferta(stoi(nroExp))) {
      cout << "El codigo ya existe.\n";
      esperarParaContinuar();
      return;
    }
  }else {
    rut = r;
    nombreSuc = nSuc;
    nombreSec = nSec;
    nroExp = nExp;
  }


  cout << "Ingrese el titulo de la oferta: ";
  string titulo;
  getline(cin, titulo);
  while (titulo.empty()) {
    system(clear);
    cout << "El titulo no puede estar vacio. Por favor, ingrese un titulo correcto: ";
    getline(cin, titulo);
  }

  cout << "Ingrese la descripcion de la oferta: ";
  string desc;
  getline(cin, desc);
  while (desc.empty()) {
    system(clear);
    cout << "La descripcion no puede estar vacia. Por favor, ingrese una descripcion correcta: ";
    getline(cin, desc);
  }

  cout << "Ingrese el sueldo minimo de la oferta: ";
  string sueldoMin;
  getline(cin, sueldoMin);
  while (sueldoMin.empty() || !esNumero(sueldoMin) || stoi(sueldoMin) < 0) {
    system(clear);
    cout << "El sueldo minimo no puede estar vacio y debe ser un numero mayor a 0. Por favor, ingrese un sueldo minimo correcto: ";
    getline(cin, sueldoMin);
  }

  cout << "Ingrese el sueldo maximo de la oferta: ";
  string sueldoMax;
  getline(cin, sueldoMax);
  while (sueldoMax.empty() || !esNumero(sueldoMax) || (stoi(sueldoMax) < stoi(sueldoMin))) {
    system(clear);
    cout << "El sueldo maximo no puede estar vacio y debe ser un numero mayor a " << sueldoMin << ". Por favor, ingrese un sueldo maximo correcto: ";
    getline(cin, sueldoMax);
  }

  cout << "Ingrese la cantidad de horas semanales de la oferta: ";
  string horas;
  getline(cin, horas);
  while (horas.empty() || !esNumero(horas) || stoi(horas) < 0) {
    system(clear);
    cout << "La cantidad de horas semanales no puede estar vacia y debe ser un numero mayor a 0. Por favor, ingrese una cantidad de horas semanales correcta: ";
    getline(cin, horas);
  }

  cout << "Ingrese la cantidad de puestos de trabajo de la oferta: ";
  string puestos;
  getline(cin, puestos);
  while (puestos.empty() || !esNumero(puestos) || stoi(puestos) < 0) {
    system(clear);
    cout << "La cantidad de puestos de trabajo no puede estar vacia y debe ser un numero mayor a 0. Por favor, ingrese una cantidad de puestos de trabajo correcta: ";
    getline(cin, puestos);
  }

  cout << "Ingrese la fecha de inicio de la oferta (dd/mm/aaaa): ";
  string fechaInicio;
  getline(cin, fechaInicio);
  while (fechaInicio.empty() || !esFecha(fechaInicio)) {
    system(clear);
    cout << "La fecha de inicio no puede estar vacia y debe tener el formato dd/mm/aaaa. Por favor, ingrese una fecha de inicio correcta: ";
    getline(cin, fechaInicio);
  }

  cout << "Ingrese la fecha de fin de la oferta (dd/mm/aaaa): ";
  string fechaFin;
  getline(cin, fechaFin);
  while (fechaFin.empty() || !esFecha(fechaFin) || !esMayorFecha(fechaFin, fechaInicio)) {
    system(clear);
    cout << "La fecha de fin no puede estar vacia, debe tener el formato dd/mm/aaaa y debe ser mayor a la fecha de inicio. Por favor, ingrese una fecha de fin correcta: ";
    getline(cin, fechaFin);
  }

  try {
    dtOfertaLaboral* dtOferta = new dtOfertaLaboral(
      stoi(nroExp),
      titulo,
      desc,
      stoi(horas),
      new dtRangoSalario(stoi(sueldoMin), stoi(sueldoMax)),
      new dtFecha(fechaInicio),
      new dtFecha(fechaFin),
      stoi(puestos)
    );
    sis->altaOfertaLaboral(rut, nombreSuc, nombreSec, dtOferta);
    cout << "La oferta se ha creado correctamente." << endl;
  } catch (invalid_argument& e) {
    cout << "Error: " << e.what() << endl;
  }
}
void eliminarOferta(bool c = true) {
  cout << "Opcion seleccionada: Eliminar Oferta Laboral" << endl;
  string rut, nombreSuc, nombreSec;
  if (c) {
    cout << "Ingrese el RUT de la empresa: ";
    getline(cin, rut);
    while (rut.empty()) {
      system(clear);
      cout << "El rut no puede estar vacio. Por favor, ingrese un rut correcto: ";
      getline(cin, rut);
    }
    if(!sis->checkRUT(rut)) {
      cout << "La empresa " << rut << " no existe.\n";
      esperarParaContinuar();
      return;
    }
    cout << "Ingrese el nombre de la sucursal: ";
    getline(cin, nombreSuc);
    while (nombreSuc.empty()) {
      system(clear);
      cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
      getline(cin, nombreSuc);
    }
    if(!sis->checkSucursal(rut, nombreSuc)) {
      cout << "Dentro de la empresa " << rut << " no existe una sucursal con el nombre " << nombreSuc << ".\n";
      esperarParaContinuar();
      return;
    }
    cout << "Ingrese el nombre de la seccion: ";
    getline(cin, nombreSec);
    while (nombreSec.empty()) {
      system(clear);
      cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
      getline(cin, nombreSec);
    }
    if(!sis->checkSeccion(rut, nombreSuc, nombreSec)) {
      cout << "Dentro de la sucursal " << nombreSuc << " de la empresa " << rut << " no existe una seccion con el nombre " << nombreSec << ".\n";
      esperarParaContinuar();
      return;
    }
  }

  cout << "Ingrese el numero de expediente de la oferta a eliminar: ";
  string nroExp;
  getline(cin, nroExp);
  while (nroExp.empty() || !esNumero(nroExp)) {
    system(clear);
    cout << "El numero de expediente no puede estar vacio y debe ser un numero. Por favor, ingrese un numero correcto: ";
    getline(cin, nroExp);
  }
  if(!sis->checkOferta(stoi(nroExp))) {
    cout << "El codigo no existe.\n";
    esperarParaContinuar();
    return;
  }
  try {
    if (c)
      sis->darBajaOferta(rut, nombreSuc, nombreSec, stoi(nroExp));
    else
      sis->darBajaOferta(stoi(nroExp));
    system(clear);
    cout << "Oferta eliminada correctamente." << endl;
    esperarParaContinuar();
  } catch (invalid_argument& e) {
    cout << "Error: " << e.what() << endl;
  }
}
void subMenuOfertas() {
  string opcion;
  do {
    cout << "----- Sub Menu Ofertas -----" << endl;
    cout << "1. Listar ofertas" << endl;
    cout << "2. Crear oferta" << endl;
    cout << "3. Eliminar oferta" << endl;
    cout << "4. Listar ofertas de una empresa" << endl;
    cout << "0. Volver al menu principal" << endl;
    getline(cin, opcion);
    int opt; 
    if (esNumero(opcion)) opt = stoi(opcion);
    else opt = -1;
    system(clear);
    switch (opt) {
      case 1:
        listarOfertas();
        break;
      case 2:
        ingresarOferta();
        break;
      case 3:
        eliminarOferta();
        break;
      case 4:
        listarOfertaDeEmpresa();
        break;
      case 0:
        return;
      default:
        system(clear);
        cout << "Opcion invalida. Por favor, ingrese una opcion valida." << endl;
        esperarParaContinuar();
        system(clear);
        break;
    }
  } while (opcion != "0");
}


void listarEstudiantes(bool c = true) {
  if (c) cout << "Opcion seleccionada: Listar estudiantes" << endl;
  cout << " Cedula | Nombre     | Apellido" << endl;
  cout << "--------|------------|----------" << endl;
  IIterator* it = sis->listarEstudiantes()->getIterator();
  while (it->hasCurrent()) {
    dtEstudiante* dtEst = (dtEstudiante*)(it->getCurrent());
    cout << left << " " << setw(7) << dtEst->getCI() << "| " << setw(11) << dtEst->getNombre() << "| " << setw(8) << dtEst->getApellido() << endl;
    it->next();
  }
  delete it;
  if (c)
    esperarParaContinuar();
}
void ingresarEstudiante() {
  cout << "Opcion seleccionada: Ingresar estudiante" << endl;
  cout << "Ingrese la cedula de identidad del estudiante: ";
  string ci;
  getline(cin, ci);
  while (ci.empty()) {
    system(clear);
    cout << "La cedula de identidad no puede estar vacia. Por favor, ingrese una cedula de identidad correcta: ";
    getline(cin, ci);
  }
  if(sis->checkEstudiante(ci)) {
    cout << "El estudiante con la cedula de identidad " << ci << " ya existe.\n";
    esperarParaContinuar();
    return;
  }

  cout << "Ingrese el nombre del estudiante: ";
  string nombre;
  getline(cin, nombre);
  while (nombre.empty()) {
    system(clear);
    cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
    getline(cin, nombre);
  }

  cout << "Ingrese el apellido del estudiante: ";
  string apellido;
  getline(cin, apellido);
  while (apellido.empty()) {
    system(clear);
    cout << "El apellido no puede estar vacio. Por favor, ingrese un apellido correcto: ";
    getline(cin, apellido);
  }

  cout << "Ingrese el telefono del estudiante: ";
  string telefono;
  getline(cin, telefono);
  while (telefono.empty() || !esNumero(telefono)) {
    system(clear);
    cout << "El telefono no puede estar vacio y debe ser un numero. Por favor, ingrese un telefono correcto: ";
    getline(cin, telefono);
  }

  cout << "Ingrese la calle de la direccion del estudiante: ";
  string calle;
  getline(cin, calle);
  while (calle.empty()) {
    system(clear);
    cout << "La calle no puede estar vacia. Por favor, ingrese una calle correcta: ";
    getline(cin, calle);
  }

  cout << "Ingrese el numero de la direccion del estudiante: ";
  string numero;
  getline(cin, numero);
  while (numero.empty() || !esNumero(numero)) {
    system(clear);
    cout << "El numero no puede estar vacio y debe ser un numero. Por favor, ingrese un numero correcto: ";
    getline(cin, numero);
  }

  cout << "Ingrese la fecha de nacimiento del estudiante en formato dd/mm/aaaa: ";
  string fechaNacimiento;
  getline(cin, fechaNacimiento);
  while (fechaNacimiento.empty() || !esFecha(fechaNacimiento)) {
    system(clear);
    cout << "La fecha de nacimiento no puede estar vacia y debe ser una fecha valida. Por favor, ingrese una fecha de nacimiento correcta: ";
    getline(cin, fechaNacimiento);
  }

  try {
    sis->altaEstudiante(ci, nombre, apellido, telefono, new dtDireccion(calle, stoi(numero)), new dtFecha(fechaNacimiento), 0);
  } catch (invalid_argument& e) {
    cout << "Error: " << e.what() << endl;
  }
}
void eliminarEstudiante() {
  cout << "Opcion seleccionada: Eliminar estudiante" << endl;
  cout << "Ingrese la ci del estudiante: ";
  string ci;
  getline(cin, ci);
  while (ci.empty()) {
    system(clear);
    cout << "La ci no puede estar vacio. Por favor, ingrese una ci valida: ";
    getline(cin, ci);
  }
  if(!sis->checkEstudiante(ci)) {
    cout << "El estudiante " << ci << " no existe\n";
    esperarParaContinuar();
    return;
  }
  try {
    sis->bajaEstudiante(ci);
  } catch(const exception& e) {
    cerr << "Error: " << e.what() << '\n';
  }
}
void subMenuEstudiantes() {
  string opcion;
  do {
    cout << "----- Sub Menu Estudiantes -----" << endl;
    cout << "1. Listar estudiantes" << endl;
    cout << "2. Ingresar estudiante" << endl;
    cout << "3. Eliminar estudiante" << endl;
    cout << "0. Volver al menu principal" << endl;
    getline(cin, opcion);
    int opt; 
    if (esNumero(opcion)) opt = stoi(opcion);
    else opt = -1;
    system(clear);
    switch (opt) {
      case 1:
        listarEstudiantes();
        break;
      case 2:
        ingresarEstudiante();
        break;
      case 3:
        eliminarEstudiante();
        break;
      case 0:
        return;
      default:
        system(clear);
        cout << "Opcion invalida. Por favor, ingrese una opcion valida." << endl;
        esperarParaContinuar();
        system(clear);
        break;
    }
  } while (opcion != "0");
}


void menu() {
  string opcion;
  do {
    cout << "----- Menu  -----" << endl;
    cout << "1. Empresas\n";
    cout << "2. Sucursales\n";
    cout << "3. Secciones\n";
    cout << "4. Asignaturas\n";
    cout << "5. Ofertas Laborales\n";
    cout << "0. Salir\n";
    getline(cin, opcion);
    int opt; 
    if (esNumero(opcion)) opt = stoi(opcion);
    else opt = -1;
    system(clear);
    switch (opt) {
      case 1:
        subMenuEmpresa();
        break;
      case 2:
        subMenuSucursal();
        break;
      case 3:
        subMenuSeccion();
        break;
      case 4:
        subMenuAsignaturas();
        break;
      case 5:
        subMenuOfertas();
        break;
      case 6:
        subMenuEstudiantes();
        break;
      case 0:
        cout << "Saliendo del programa..." << endl;
        return;
        break;
      default:
        system(clear);
        cout << "Opcion invalida. Por favor, ingrese una opcion valida." << endl;
        esperarParaContinuar();
        system(clear);
        break;
    }
  } while (opcion != "0");
}


bool consultarSiModificara(string aMostrar) {
  cout << aMostrar << endl;
  string opcion;
  getline(cin, opcion);
  while (opcion.empty() || (opcion != "s" && opcion != "n")) {
    system(clear);
    cout << "La opcion ingresada no es valida. Por favor, ingrese una opcion valida (s/n): ";
    getline(cin, opcion);
  }
  return (opcion == "s");
}
void altaOfertaLaboral() {
  /*
    El caso de uso comienza cuando un Usuario desea dar de alta una Oferta
    Laboral en el Sistema. Para esto, el Sistema lista las Empresas existentes y
    el Usuario selecciona una. Luego se listan sus Sucursales, y el Usuario
    escoge la que desea. Elige la Sección que publica la Oferta de entre una
    lista desplegada por el Sistema. Luego indica un número de expediente, el
    título, descripción, la cantidad de horas semanales, el conjunto de
    asignaturas requeridas para que un Estudiante se pueda anotar al llamado,
    rango salarial, fecha de comienzo y fin del llamado y la cantidad de puestos
    que se necesitan.
    En todos los casos el Sistema controlará la existencia y validez de la
    Empresa, sucursal, Sección y asignaturas de la oferta, indicando el error en
    caso de que lo haya, o realiza el alta correspondiente.
  */
  listarEmpresas(false);
  cout << "\nIngrese el rut de la empresa: ";
  string rut;
  getline(cin, rut);
  while (rut.empty()) {
    system(clear);
    cout << "El rut no puede estar vacio. Por favor, ingrese un rut correcto: ";
    getline(cin, rut);
  }
  if(!sis->checkRUT(rut)) {
    cout << "La empresa " << rut << " no existe\n";
    esperarParaContinuar();
    return;
  }
  cout << endl;
  listarSucursales(rut, false);
  
  cout << "\nIngrese el nombre de la sucursal: ";
  string nombreSucursal;
  getline(cin, nombreSucursal);
  while (nombreSucursal.empty()) {
    system(clear);
    cout << "El nombre de la sucursal no puede estar vacio. Por favor, ingrese un nombre de sucursal correcto: ";
    getline(cin, nombreSucursal);
  }
  if(!sis->checkSucursal(rut, nombreSucursal)) {
    cout << "La sucursal " << nombreSucursal << " no existe\n";
    esperarParaContinuar();
    return;
  }
  cout << endl;
  listarSecciones(rut, nombreSucursal, false);

  cout << "\nIngrese el nombre de la seccion: ";
  string nombreSeccion;
  getline(cin, nombreSeccion);
  while (nombreSeccion.empty()) {
    system(clear);
    cout << "El nombre de la seccion no puede estar vacio. Por favor, ingrese un nombre de seccion correcto: ";
    getline(cin, nombreSeccion);
  }
  if(!sis->checkSeccion(rut, nombreSucursal, nombreSeccion)) {
    cout << "La seccion " << nombreSeccion << " no existe\n";
    esperarParaContinuar();
    return;
  }
  cout << endl;
  
  cout << "Ingrese el numero de expediente de la oferta: ";
  string nroExp;
  getline(cin, nroExp);
  while (nroExp.empty() || !esNumero(nroExp)) {
    system(clear);
    cout << "El numero de expediente no puede estar vacio y debe ser un numero. Por favor, ingrese un numero correcto: ";
    getline(cin, nroExp);
  }
  if(sis->checkOferta(stoi(nroExp))) {
    cout << "El codigo ya existe.\n";
    esperarParaContinuar();
    return;
  }

  ingresarOferta(rut, nombreSucursal, nombreSeccion, nroExp, false);

  do {
    cout << "Desea agregar una asignatura a la oferta laboral? (s/n): ";
    string opcion;
    getline(cin, opcion);
    while (opcion.empty() || (opcion != "s" && opcion != "n")) {
      system(clear);
      cout << "La opcion ingresada no es valida. Por favor, ingrese una opcion valida (s/n): ";
      getline(cin, opcion);
    }
    if (opcion == "n") break;

    listarAsignaturas(false);
    cout << "\nIngrese el codigo de la asignatura: ";
    string codigo;
    getline(cin, codigo);
    while (codigo.empty() || !esNumero(codigo)) {
      system(clear);
      cout << "El codigo de la asignatura no puede estar vacio y debe ser un numero. Por favor, ingrese un codigo de asignatura correcto: ";
      getline(cin, codigo);
    }
    if(!sis->checkAsignatura(stoi(codigo))) {
      cout << "La asignatura " << codigo << " no existe\n";
      esperarParaContinuar();
      return;
    }
    try {
      sis->seleccionarAsignatura(stoi(codigo), stoi(nroExp));
    } catch (invalid_argument& e) {
      cout << "Error " << e.what() << endl;
    }
  } while(true);
}
void modificarLlamado() {
  /*
    El caso de uso comienza cuando un Usuario desea modificar los datos de
    un llamado. Para esto el Sistema lista las Ofertas Laborales vigentes, el
    Usuario elige una, y el Sistema permite modificar todos los datos
    vinculados a la misma (menos el número de expediente y la Sección).
    En todos los casos el Sistema controlará la existencia y validez de la Oferta
    Laboral, indicando error en caso de que lo haya, o realiza la modificación
    correspondiente.
  */
  listarOfertas(false);
  cout << "\nIngrese el numero de expediente de la oferta: ";
  string nroExp;
  getline(cin, nroExp);
  while (nroExp.empty() || !esNumero(nroExp)) {
    system(clear);
    cout << "El numero de expediente no puede estar vacio y debe ser un numero. Por favor, ingrese un numero correcto: ";
    getline(cin, nroExp);
  }
  if(!sis->checkOferta(stoi(nroExp))) {
    cout << "La oferta " << nroExp << " no existe\n";
    esperarParaContinuar();
    return;
  }
  cout << endl;
  string titulo = "", desc = "", cantHoras = "", salarioMin = "", salarioMax = "", fechaInicio = "", fechaFin = "", cantPuestos = "";
  bool modifica;

  modifica = consultarSiModificara("Desea modificar el titulo de la oferta? (s/n): ");  
  if (modifica) {
    cout << "Ingrese el nuevo titulo: ";
    getline(cin, titulo);
    while (titulo.empty()) {
      system(clear);
      cout << "El titulo no puede estar vacio. Por favor, ingrese un titulo correcto: ";
      getline(cin, titulo);
    }
  }

  modifica = consultarSiModificara("Desea modificar la descripcion de la oferta? (s/n): ");
  if (modifica) {
    cout << "Ingrese la nueva descripcion: ";
    getline(cin, desc);
    while (desc.empty()) {
      system(clear);
      cout << "La descripcion no puede estar vacia. Por favor, ingrese una descripcion correcta: ";
      getline(cin, desc);
    }
  }

  modifica = consultarSiModificara("Desea modificar la cantidad de horas semanales de la oferta? (s/n): ");
  if (modifica) {
    cout << "Ingrese la nueva cantidad de horas semanales: ";
    getline(cin, cantHoras);
    while (cantHoras.empty() || !esNumero(cantHoras)) {
      system(clear);
      cout << "La cantidad de horas semanales no puede estar vacia y debe ser un numero. Por favor, ingrese una cantidad de horas semanales correcta: ";
      getline(cin, cantHoras);
    }
  }

  modifica = consultarSiModificara("Desea modificar el salario minimo y maximo de la oferta? (s/n): ");
  if (modifica) {
    cout << "Ingrese el nuevo salario minimo: ";
    getline(cin, salarioMin);
    while (salarioMin.empty() || !esNumero(salarioMin)) {
      system(clear);
      cout << "El salario minimo no puede estar vacio y debe ser un numero. Por favor, ingrese un salario minimo correcto: ";
      getline(cin, salarioMin);
    }
    cout << "Ingrese el nuevo salario maximo: ";
    getline(cin, salarioMax);
    while (salarioMax.empty() || !esNumero(salarioMax)) {
      system(clear);
      cout << "El salario maximo no puede estar vacio y debe ser un numero. Por favor, ingrese un salario maximo correcto: ";
      getline(cin, salarioMax);
    }
  }

  modifica = consultarSiModificara("Desea modificar la fecha de inicio y fin de la oferta? (s/n): ");
  if (modifica) {
    cout << "Ingrese la nueva fecha de inicio dd/mm/aaaa: ";
    getline(cin, fechaInicio);
    while (fechaInicio.empty() || !esFecha(fechaInicio)) {
      system(clear);
      cout << "La fecha de inicio no puede estar vacia y debe ser una fecha valida. Por favor, ingrese una fecha de inicio correcta: ";
      getline(cin, fechaInicio);
    }
    cout << "Ingrese la nueva fecha de fin dd/mm/aaaa: ";
    getline(cin, fechaFin);
    while (fechaFin.empty() || !esFecha(fechaFin) || !esMayorFecha(fechaFin, fechaInicio)) {
      system(clear);
      cout << "La fecha de fin no puede estar vacia y debe ser una fecha valida. Por favor, ingrese una fecha de fin correcta: ";
      getline(cin, fechaFin);
    }
  }

  modifica = consultarSiModificara("Desea modificar la cantidad de puestos de la oferta? (s/n): ");
  if (modifica) {
    cout << "Ingrese la nueva cantidad de puestos: ";
    getline(cin, cantPuestos);
    while (cantPuestos.empty() || !esNumero(cantPuestos)) {
      system(clear);
      cout << "La cantidad de puestos no puede estar vacia y debe ser un numero. Por favor, ingrese una cantidad de puestos correcta: ";
      getline(cin, cantPuestos);
    }
  }


  dtOfertaLaboral* dtOferta = sis->getOfertaLaboral(stoi(nroExp));
  system(clear);
  cout << "Segura que desea cambiar: \n";
  if (!titulo.empty())
    cout << "Titulo: " << dtOferta->getTitulo() << " --> " << titulo << endl;
  if (!desc.empty())
    cout << "Descripcion: " << dtOferta->getDesc() << " --> " << desc << endl;
  if (!cantHoras.empty()) 
    cout << "Cantidad de horas semanales: " << dtOferta->getCantHoras() << " --> " << cantHoras << endl;
  if (!salarioMin.empty() && !salarioMax.empty())
    cout << "Salario: " << dtOferta->getSalario()->getSalarioMin() << " - " << dtOferta->getSalario()->getSalarioMax() << " --> " << salarioMin << " - " << salarioMax << endl;
  if (!fechaInicio.empty() && !fechaFin.empty()) {
    cout << "Fecha de inicio: " << dtOferta->getFechaInicio()->getFecha() << " --> " << fechaInicio << endl;
    cout << "Fecha de fin: " << dtOferta->getFechaFin()->getFecha() << " --> " << fechaFin << endl;
  }
  if (!cantPuestos.empty())
    cout << "Cantidad de puestos: " << dtOferta->getCantPuestos() << " --> " << cantPuestos << endl;
  modifica = consultarSiModificara("Desea confirmar los cambios? (s/n): ");
  if (!modifica) {
    system(clear);
    cout << "No se realizara ningun cambio sobre la oferta " << nroExp << endl;
    return;
  }
  try {
    sis->modificarLlamado(stoi(nroExp), titulo, desc, cantHoras, salarioMin, salarioMax, fechaInicio, fechaFin, cantPuestos);
    cout << "La oferta " << nroExp << " se modifico correctamente\n";
  } catch (invalid_argument& e) {
    cout << "Error " << e.what() << endl;
  }
  
}
void darBajaLlamado() {
  /*
    El caso de uso comienza cuando un Usuario desea dar de baja una Oferta
    Laboral. Para esto el Sistema lista las Ofertas Laborales existentes, y el
    Usuario elige una para que el Sistema realice la baja.
    En todos los casos el Sistema controlará la existencia de la Oferta Laboral,
    indicando error en caso de que lo haya, o realiza la baja correspondiente.
  */
  listarOfertas(false);
  eliminarOferta(false);
}

void consultarDatosDeEstudiante() {
  /*
    El caso de uso comienza cuando un Usuario desea ver los datos de un
    Estudiante en concreto, las Asignaturas que tiene aprobadas, los llamados a
    los que se inscribió y los datos de la Empresa (incluyendo datos de la
    Sucursal y Sección) asociada a cada llamado. Para esto el Sistema lista los
    Estudiantes registrados, y el Usuario ingresa el número de cédula del
    Estudiante a consultar.
    En todos los casos el Sistema controlará la existencia del Estudiante,
    indicando el error en caso de que lo haya, o realiza la consulta
    correspondiente
  */
  listarEstudiantes(false);
  string cedula;
  cout << "Ingrese la cedula del estudiante: ";
  getline(cin, cedula);
  while (cedula.empty() || !esNumero(cedula)) {
    system(clear);
    listarEstudiantes(false);
    cout << "La cedula no puede estar vacia y debe ser un numero. Por favor, ingrese una cedula correcta: ";
    getline(cin, cedula);
  }
  if (!sis->checkEstudiante(cedula)) {
    cout << "No existe un estudiante con la cedula " << cedula << endl;
    return;
  } 
  try {
    dtEstudianteTodo* infoEstudiante = sis->mostrarEstudiante(cedula);
    ICollection* asignaturasEstudiante = sis->mostrarAsignaturas(cedula);
    ICollection* llamadosEstudiante = sis->mostrarLlamadoEstudiante(cedula);

    system(clear);
    cout << ">>> Datos de Estudiante <<<\n";
    cout << "Cedula: " << infoEstudiante->getCI() << endl;
    cout << "Nombre: " << infoEstudiante->getNombre() << endl;
    cout << "Apellido: " << infoEstudiante->getApellido() << endl;
    cout << "Telefono: " << infoEstudiante->getTelefono() << endl;
    cout << "Fecha de nacimiento: " << infoEstudiante->getFechaNacimiento()->getFecha() << endl;
    cout << "Asignaturas aprobadas: " << endl;

    IIterator* it = asignaturasEstudiante->getIterator();
    if (!it->hasCurrent()) {
      cout << "\tNo tiene asignaturas aprobadas" << endl;
    } else {
      while (it->hasCurrent()) {
        dtAsignatura* dtAsig = (dtAsignatura*)(it->getCurrent());
        cout << "\tCodigo: " << dtAsig->getCodigo() << endl;
        cout << "\tNombre: " << dtAsig->getNombre() << endl;
        cout << "\tCreditos: " << dtAsig->getCreditos() << endl;
        it->next();
      }
    }

    cout << "Llamados a los que se postulo: " << endl;
    it = llamadosEstudiante->getIterator();
    if (!it->hasCurrent()) {
      cout << "\tNo se postulo a ningun llamado" << endl;
    } else {
      while (it->hasCurrent()) {
        dtOfertaLaboral* dtOferta = (dtOfertaLaboral*)(it->getCurrent());
        cout << "\tNumero de expediente: " << dtOferta->getNroExpediente() << endl;
        cout << "\tTitulo: " << dtOferta->getTitulo() << endl;
        cout << "\tDescripcion: " << dtOferta->getDesc() << endl;
        cout << "\tCantidad de horas semanales: " << dtOferta->getCantHoras() << endl;
        cout << "\tSalario: " << dtOferta->getSalario()->getSalarioMin() << " - " << dtOferta->getSalario()->getSalarioMax() << endl;
        cout << "\tFecha de inicio: " << dtOferta->getFechaInicio()->getFecha() << endl;
        cout << "\tFecha de fin: " << dtOferta->getFechaFin()->getFecha() << endl;
        cout << "\tCantidad de puestos: " << dtOferta->getCantPuestos() << endl;
        cout << "\tNombre de la seccion: " << sis->mostrarInfoSeccionDeOferta(dtOferta->getNroExpediente()) << endl;
        cout << "\tNombre de la sucursal: " << sis->mostrarInfoSucursalDeOferta(dtOferta->getNroExpediente()) << endl;
        cout << "\nNombre de la empresa: " << sis->mostrarInfoEmpresaDeOferta(dtOferta->getNroExpediente()) << endl;
        it->next();
      }
    }
    delete it;
    delete infoEstudiante;
    delete asignaturasEstudiante;
    delete llamadosEstudiante;
  } catch(invalid_argument& e) {
    cout << "Error " << e.what() << endl;
  }
}

void modificarEstudiante() {
  listarEstudiantes(false);
  cout << "Ingrese la cedula del estudiante: ";
  string cedula;
  getline(cin, cedula);
  while (cedula.empty() || !esNumero(cedula)) {
    system(clear);
    listarEstudiantes(false);
    cout << "La cedula no puede estar vacia y debe ser un numero. Por favor, ingrese una cedula correcta: ";
    getline(cin, cedula);
  }
  if (!sis->checkEstudiante(cedula)) {
    cout << "No existe un estudiante con la cedula " << cedula << endl;
    return;
  }
  string nombre, apellido, telefono, fechaNacimiento, codigo;
  ICollection* asignaturasAgregar = new List();
  bool mod;
  if (consultarSiModificara("Desea modificar el nombre del estudiante? (s/n): ")) {
    cout << "Ingrese el nombre del estudiante: ";
    getline(cin, nombre);
    while (nombre.empty()) {
      system(clear);
      cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre correcto: ";
      getline(cin, nombre);
    }
  }
  if (consultarSiModificara("Desea modificar el apellido del estudiante? (s/n): ")) {
    cout << "Ingrese el apellido del estudiante: ";
    getline(cin, apellido);
    while (apellido.empty()) {
      system(clear);
      cout << "El apellido no puede estar vacio. Por favor, ingrese un apellido correcto: ";
      getline(cin, apellido);
    }
  }
  if (consultarSiModificara("Desea modificar el telefono del estudiante? (s/n): ")) {
    cout << "Ingrese el telefono del estudiante: ";
    getline(cin, telefono);
    while (telefono.empty() || !esNumero(telefono)) {
      system(clear);
      cout << "El telefono no puede estar vacio y debe ser un numero. Por favor, ingrese un telefono correcto: ";
      getline(cin, telefono);
    }
  }
  if (consultarSiModificara("Desea modificar la fecha de nacimiento del estudiante? (s/n): ")) {
    cout << "Ingrese la fecha de nacimiento del estudiante: ";
    getline(cin, fechaNacimiento);
    while (fechaNacimiento.empty() || !esFecha(fechaNacimiento)) {
      system(clear);
      cout << "La fecha de nacimiento no puede estar vacia y debe ser una fecha valida. Por favor, ingrese una fecha correcta (dd/mm/aaaa): ";
      getline(cin, fechaNacimiento);
    }
  }
  if (consultarSiModificara("Desea modificar las asignaturas aprobadas? (s/n): ")) {
    mod = true;
    while (mod) {
      system(clear);
      listarAsignaturas();
      cout << "Ingrese el codigo de la asignatura aprobada: ";
      getline(cin, codigo);
      while (codigo.empty()) {
        system(clear);
        listarAsignaturas();
        cout << "El codigo no puede estar vacio. Por favor, ingrese un codigo correcto: ";
        getline(cin, codigo);
      }
      if (!sis->checkAsignatura(stoi(codigo))) {
        cout << "No existe una asignatura con el codigo " << codigo << endl;
        continue;
      }
      if (sis->checkAsignaturaDeEstudiante(cedula, stoi(codigo))) {
        cout << "El estudiante ya tiene aprobada la asignatura con el codigo " << codigo << endl;
        continue;
      }
      if (asignaturasAgregar->member(new Integer(stoi(codigo)))) {
        cout << "Ya agrego esa asignatura aprobada" << endl;
        continue;
      }
      asignaturasAgregar->add(new Integer(stoi(codigo)));
      mod = consultarSiModificara("Desea agregar otra asignatura aprobada? (s/n): ");
    }
  }
  if (consultarSiModificara("Desea eliminar asignaturas aprobadas? (s/n): ")) {
    mod = true;
    while (mod) {
      


      mod = consultarSiModificara("Desea eliminar otra asignatura aprobada? (s/n): ");
    }
  }
}

bool listarEstudiantesInscriptos(string n = "", bool c = true) {
  string nro;
  if (c) {
    cout << "Opcion seleccionada: Listar Estudiantes inscriptos" << endl;
    cout << "Ingrese el Numero de expediente: ";
    getline(cin, nro);
    while (nro.empty()) {
      system(clear);
      cout << "El numero no puede estar vacio. Por favor, ingrese un numero: ";
      getline(cin, nro);
    }
    if (!sis->checkOferta(stoi(nro))) {
      cout << "La oferta " << nro << " no existe";
      esperarParaContinuar();
      return false;
    }
  } else {
    nro = n;
  }

  IIterator* it = sis->listarEstudiantesInscriptos(stoi(nro))->getIterator();
  if (!it->hasCurrent()) {
    cout << "No hay estudiantes inscriptos en la oferta " << nro << endl;
    esperarParaContinuar();
    return false;
  }
  cout << "  Cedula  | Nombre | Apellido |" << endl;
  cout << "--------------------------------" << endl;
  dtEstudiante* e;
  while (it->hasCurrent()) {
    e = (dtEstudiante*)(it->getCurrent());
    cout << left << setw(10) << e->getCI() << "| " << setw(8) << e->getNombre() << "| " << setw(10) << e->getApellido() << endl;
    it->next();
  }
  delete it;
  if (c)
    esperarParaContinuar();
  return true;
}
bool listarEstudiantesNoInscriptos(string n = "", bool c = true) {
  string nro;
  if (c) {
    cout << "Opcion seleccionada: Listar Estudiantes No Inscriptos" << endl;
    cout << "Ingrese el Numero de expediente: ";
    getline(cin, nro);
    while (nro.empty()) {
      system(clear);
      cout << "El numero no puede estar vacio. Por favor, ingrese un numero: ";
      getline(cin, nro);
    }
    if (!sis->checkOferta(stoi(nro))) {
      cout << "La oferta " << nro << " no existe";
      esperarParaContinuar();
      return false;
    }
  } else {
    nro = n;
  }
  IIterator* it = sis->listarEstudiantesNoInscriptos(stoi(nro))->getIterator();
  if (!it->hasCurrent()) {
    cout << "No hay estudiantes no inscriptos en la oferta " << nro << endl;
    esperarParaContinuar();
    return false;
  }
  cout << "  Cedula  | Nombre | Apellido |" << endl;
  cout << "--------------------------------" << endl;
  dtEstudiante* e;
  while (it->hasCurrent()) {
    e = (dtEstudiante*)(it->getCurrent());
    cout << left << setw(10) << e->getCI() << "| " << setw(8) << e->getNombre() << "| " << setw(10) << e->getApellido() << endl;
    it->next();
  }
  delete it;
  if (c)
    esperarParaContinuar();
  return true;
}

void asignarOfertaEstudiante() {
  /*
    El caso de uso comienza cuando un Usuario desea asignar a un Estudiante
    como quien toma uno de los cargos de una Oferta Laboral. Para esto el
    Sistema lista las Ofertas Laborales vigentes, y el Usuario elige una. Luego
    se despliegan los Estudiantes inscriptos en la Oferta Laboral, y el Usuario
    elige uno. Finalmente, el Sistema da de alta la asignación del cargo.
    En todos los casos el Sistema controlará la existencia y validez del
    Estudiante y el llamado, indicando el error en caso de que lo haya, o realiza
    el alta correspondiente.
    - listarOfertasVigentes ✅
    - seleccionar oferta ✅
    - listarEstudiantesInscriptos ✅
    - seleccionar estudiante ✅
    - dar alta en efectivo
  */
  listarOfertas(false);
  cout << "\nIngrese el numero de expediente de la oferta: ";
  string nroExp;
  getline(cin, nroExp);
  while (nroExp.empty() || !esNumero(nroExp)) {
    system(clear);
    cout << "El numero de expediente no puede estar vacio y debe ser un numero. Por favor, ingrese un numero correcto: ";
    getline(cin, nroExp);
  }
  if(!sis->checkOferta(stoi(nroExp))) {
    cout << "La oferta " << nroExp << " no existe\n";
    esperarParaContinuar();
    return;
  }

  if (!listarEstudiantesInscriptos(nroExp, false)) return;
  cout << "\nIngrese la cedula del estudiante: ";
  string cedula;
  getline(cin, cedula);
  while (cedula.empty() || !esNumero(cedula)) {
    system(clear);
    cout << "La cedula no puede estar vacia y debe ser un numero. Por favor, ingrese un numero correcto: ";
    getline(cin, cedula);
  }
  if(!sis->checkEstudiante(cedula)) {
    cout << "El estudiante " << cedula << " no existe\n";
    esperarParaContinuar();
    return;
  }

  try {
    sis->asignarOfertaEstudiante(cedula, stoi(nroExp));
  } catch (const std::exception& e) {
    cerr << "Error: "<< e.what() << '\n';
  }
}

void inscripcionOfertaLaboral(){
	string ci, nro;
	
	cout << "Seleccione una de las siguientes ofertas:" << endl;
	listarOfertas(false);
  cout << "Ingrese el numero de expediente:";
	getline(cin, nro);
	while(nro.empty()) {
		system(clear);
		cout << "El Numero de Expediente no puede estar vacio. Por favor, ingrese un numero: ";
		getline(cin, nro);
	}
	if (!sis->checkOferta(stoi(nro))) {
		cout << "La oferta de expediente " << nro << " no existe";
		esperarParaContinuar();
		return;
  }
	cout << "Estudiantes no inscriptos: "<< endl;
	if (!listarEstudiantesNoInscriptos(nro, false)) return;
	cout << "\nIngrese una cedula:" << endl;
	getline(cin,ci);
	while(ci.empty()){
		system(clear);
		cout << "La Cedula no puede estar vacia. Por favor, ingrese una cedula: ";
		getline(cin, ci);
	}
	if (!sis->checkEstudiante(ci)) {
		cout << "La cedula " << ci << " no existe";
		esperarParaContinuar();
		return;
  }
	try {
    sis->inscribirEstudianteEnOferta(ci,stoi(nro));
  } catch (const exception& e) {
    cerr << "Error: "<< e.what() << '\n';
  }
}

// void altaEntrevista(){
// 	string ci;
// 	int nro;
// 	string fecha;
// 	cout << "Seleccione una de las siguientes ofertas:" << endl;
// 	listarOfertas();
// 	getline(cin, nro);
// 	while(nro.empty()){
// 		system(clear);
// 		cout << "El Numero de Expediente no puede estar vacio. Por favor, ingrese un numero: ";
// 		getline(cin, nro);
// 	}
// 	if (!sis->checkOferta(nro)) {
// 		cout << "La oferta de expediente " << nro << " no existe";
// 		esperarParaContinuar();
// 		return;
//     }
// 	cout << "Estudiantes inscriptos a esa oferta: "<< endl;
// 	listarEstudiantesInscriptos(nro);
// 	cout << "Ingrese una cedula del estudiante que desea entrevistar:";
// 	getline(cin,ci);
// 	while(ci.empty()){
// 		system(clear);
// 		cout << "La Cedula no puede estar vacia. Por favor, ingrese una cedula: ";
// 		getline(cin, ci);
// 	}
// 	if (!sis->checkEstudiante(ci)) {
// 		cout << "La cedula " << ci << " no existe";
// 		esperarParaContinuar();
// 		return;
//     }
// 	cout << "Ingrese la fecha en la cual se realizara la entrevista (dd/mm/aaaa): ";
// 	getline(cin,fecha);
// 	while (fecha.empty() || !esFecha(fecha)) {
//     system(clear);
//     cout << "La fecha no puede estar vacia y debe tener el formato dd/mm/aaaa. Por favor, ingrese una fecha de inicio correcta: ";
//     getline(cin, fecha);
//   }
// 	sis->altaEntrevista(ci,nro,fecha);
// }

int main () {
  // menu();
  /*
  ==> Mis casos de uso completos <==
    altaOfertaLaboral(); ✅
    modificarLlamado();  ✅
    darBajaLlamado();    ✅

  ==> Casos de uso de Denis completos <==
    consultarDatosDeEstudiante(); ✅
    listarOfertas();              ✅
  */

  /*
  ==> Casos de uso de Matias <==
    Modificar Estudiante
    Alta Estudiante --> ingresarEstudiante(); ✅
    Asignación de Oferta a Estudiante
  */

  /*
  ==> Casos de uso de Cristian <==
    Alta Entrevista
    Inscripción Oferta Laboral
  */
  cout << "Bienvenido al Sistema de Ofertas Laborales" << endl;

  // asignarOfertaEstudiante();
  inscripcionOfertaLaboral();

  listarEstudiantesInscriptos("1", false);

  
  cout<<"\nFin Main\n";
  return 0;
}