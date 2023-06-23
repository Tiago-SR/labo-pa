#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <iostream>
using namespace std;
#include "Empresa.h"
#include "../datatype/dtDireccion.h"
#include "../datatype/dtFecha.h"
#include "../datatype/dtOfertaLaboral.h"
#include "../datatype/dtEstudianteTodo.h"
#include "../datatype/dtSeccion.h"
#include "../datatype/dtSucursal.h"
#include "../datatype/dtEmpresa.h"
#include "../../ICollection/interfaces/ICollection.h"
#include "../../ICollection/interfaces/IDictionary.h"

class ISistema {
  public:
    virtual ~ISistema(){};
    
    virtual void altaEmpresa(string, string) = 0;
    virtual void bajaEmpresa(string) = 0;
    virtual bool checkRUT(string) = 0;
    virtual Empresa* getEmpresa(string) = 0;

    virtual void altaSucursal(string, string, string, dtDireccion*) = 0;
    virtual void bajaSucursal(string, string) = 0;
    virtual bool checkSucursal(string, string) = 0;

    virtual bool checkSeccion(string, string, string) = 0;
    virtual void altaSeccion(string, string, string, string) = 0;
    virtual void bajaSeccion(string, string, string) = 0;

    virtual bool checkAsignatura(int) = 0;
    virtual void altaAsignatura(int, string, int) = 0;
    virtual void bajaAsignatura(int) = 0;

    virtual bool checkOferta(int) = 0;
    virtual ICollection* listarOfertasActivasDeEmpresa(string) = 0;

    virtual bool checkEstudiante(string) = 0;
    virtual void altaEstudiante(string, string, string, string, dtDireccion*, dtFecha*, int) = 0;
    virtual void bajaEstudiante(string) = 0;
    virtual bool checkAsignaturaDeEstudiante(string, int) = 0;


    // Casos de uso Modificar Llamado
    virtual dtOfertaLaboral* getOfertaLaboral(int) = 0;
    virtual void modificarLlamado(int, string, string, string, string, string, string, string, string) = 0;


    // Caso de uso Baja Llamado
    virtual ICollection* listarAsignaturasDeOferta(int) = 0;

    // Caso de uso Asignar Oferta A Estudiante
    virtual void asignarOfertaEstudiante(string, int, float) = 0;

    // Caso de uso Alta Entrevista
    virtual void altaEntrevista(string ci, int nroExp, string fecha) = 0;


    //  --> primer Diagrama de comunicacion
    virtual ICollection* listarEmpresas() = 0;
    virtual ICollection* listarSucursales(string rut) = 0;
    virtual ICollection* listarSecciones(string rut, string nombreSucursal) = 0;
    virtual ICollection* listarAsignaturas() = 0;
    virtual void altaOfertaLaboral(string, string, string, dtOfertaLaboral*) = 0;
    virtual void seleccionarAsignatura(int, int) = 0;

    // --> segundo Diagrama de comunicacion
    virtual ICollection* listarOfertasActivas() = 0; // dtOfertaLaboral  --> tambien es del tercer y quinto diagrama
    virtual ICollection* listarEstudiantesNoInscriptos(int) = 0;
    virtual ICollection* listarEstudiantesInscriptos(int) = 0;
    virtual void inscribirEstudianteEnOferta(string, int) = 0;

    // --> cuarto Diagrama de comunicacion
    virtual ICollection* listarEstudiantes() = 0;
    virtual dtEstudianteTodo* mostrarEstudiante(string) = 0;
    virtual ICollection* mostrarAsignaturas(string) = 0; // -> recuerda la ci de mostrarEstudiante()
    virtual ICollection* mostrarLlamadoEstudiante(string) = 0; // -> recuerda la ci de mostrarEstudiante()
    virtual dtSeccion* mostrarInfoSeccionDeOferta(int) = 0;
    virtual dtSucursal* mostrarInfoSucursalDeOferta(int) = 0;
    virtual dtEmpresa* mostrarInfoEmpresaDeOferta(int) = 0;

    // --> quinto Diagrama de comunicacion
    virtual void darBajaOferta(string, string, string, int) = 0;
    virtual void darBajaOferta(int) = 0;
};
#endif