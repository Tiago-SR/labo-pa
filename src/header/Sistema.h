#ifndef SISTEMA_H
#define SISTEMA_H
#include <ctime>
#include <iostream>
using namespace std;

#include "ISistema.h"

#include "../datatype/dtFecha.h"
#include "../datatype/dtDireccion.h"
#include "../datatype/dtOfertaLaboral.h"
#include "../datatype/dtEstudianteTodo.h"
#include "../datatype/dtSeccion.h"
#include "../datatype/dtSucursal.h"
#include "../datatype/dtEmpresa.h"
#include "../datatype/dtRangoSalario.h"

#include "../../ICollection/interfaces/IDictionary.h"
#include "../../ICollection/interfaces/ICollection.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../ICollection/collections/List.h"
#include "../../ICollection/String.h"
#include "../../ICollection/Integer.h"

#include "Empresa.h"
#include "Sucursal.h"
#include "Seccion.h"
#include "Asignatura.h"
#include "OfertaLaboral.h"
#include "Estudiante.h"
#include "Efectivo.h"
#include "Carrera.h"



class Sistema : public ISistema {
  private:
    Sistema();
    static Sistema* instance;
    IDictionary* empresas;
    IDictionary* estudiantes;
    IDictionary* asignaturas;
    IDictionary* ofertas;
    IDictionary* carreras;
  public:
    virtual ~Sistema() {};
    static Sistema* getInstance();
    static dtFecha* getFechaActual();

    void parseCsv();

    // --> empresas
    void altaEmpresa(string, string);
    void bajaEmpresa(string);
    bool checkRUT(string);
    Empresa* getEmpresa(string);

    // --> sucursales
    void altaSucursal(string, string, string, dtDireccion*);
    void bajaSucursal(string, string);
    bool checkSucursal(string, string);

    // --> secciones
    bool checkSeccion(string, string, string);
    void altaSeccion(string, string, string, string);
    void bajaSeccion(string, string, string);

    // --> asignaturas
    bool checkAsignatura(int);
    void altaAsignatura(int, string, int);
    void bajaAsignatura(int);
    Asignatura* getAsignatura(int);

    // --> ofertas laborales
    bool checkOferta(int);
    ICollection* listarOfertasActivasDeEmpresa(string);
    OfertaLaboral* getOferta(int);

    // --> estudiantes
    bool checkEstudiante(string);
    void altaEstudiante(string, string, string, string, dtDireccion*, dtFecha*, int);
    void bajaEstudiante(string);
    bool checkAsignaturaDeEstudiante(string, int);
    Estudiante* getEstudiante(string);

    // --> carreras
    bool checkCarrera(int);
    bool checkCarreraDeEstudiante(string, int);
    void altaCarrera(int, string, int, IDictionary*);
    void agregarCarreraEstudiante(string, int);
    void quitarCarreraDeEstudiante(string, int);
    IDictionary* getCarreras();
    Carrera* getCarrera(int);
    ICollection* mostrarCarreras();
    ICollection* mostrarCarrerasDeEstudiante(string);

    // Caso de uso Modificar Llamado
    dtOfertaLaboral* getOfertaLaboral(int);
    void modificarLlamado(int, string, string, string, string, string, string, string, string);

    // Caso de uso Baja Llamado
    ICollection* listarAsignaturasDeOferta(int);

    // Caso de uso Inscribir Estudiante


    // Caso de uso Alta Entrevista
    void altaEntrevista(string ci, int nroExp, string fecha);

    // Caso de uso Asignar Oferta A Estudiante
    bool checkEstudianteInscripto(string, int);
    
    void asignarOfertaEstudiante(string, int, float);

    // --> primer Diagrama de comunicacion
    ICollection* listarEmpresas();
    ICollection* listarSucursales(string rut);
    ICollection* listarSecciones(string rut, string nombreSucursal);
    ICollection* listarAsignaturas();
    void altaOfertaLaboral(string, string, string, dtOfertaLaboral*);
    void seleccionarAsignatura(int, int);

    // --> segundo Diagrama de comunicacion
    ICollection* listarOfertasActivas(); // dtOfertaLaboral  --> tambien es del tercer y quinto diagrama
    ICollection* listarEstudiantesNoInscriptos(int);
    ICollection* listarEstudiantesInscriptos(int);
    void inscribirEstudianteEnOferta(string, int);

    // --> cuarto Diagrama de comunicacion
    ICollection* listarEstudiantes();
    dtEstudianteTodo* mostrarEstudiante(string);
    ICollection* mostrarAsignaturas(string); // -> recuerda la ci de mostrarEstudiante()
    ICollection* mostrarLlamadoEstudiante(string); // -> recuerda la ci de mostrarEstudiante()
    dtSeccion* mostrarInfoSeccionDeOferta(int);
    dtSucursal* mostrarInfoSucursalDeOferta(int);
    dtEmpresa* mostrarInfoEmpresaDeOferta(int);

    // --> quinto Diagrama de comunicacion
    void darBajaOferta(string, string, string, int);
    void darBajaOferta(int);
};


#endif