#ifndef OFERTALABORAL_H
#define OFERTALABORAL_H

#include <iostream>
using namespace std;

#include "../../ICollection/Integer.h"

#include "../datatype/dtRangoSalario.h"
#include "../datatype/dtFecha.h"
#include "../datatype/dtOfertaLaboral.h"
#include "../datatype/dtSeccion.h"
#include "../datatype/dtSucursal.h"
#include "../datatype/dtEmpresa.h"

#include "Asignatura.h"
#include "Seccion.h"
#include "Estudiante.h"
#include "Anotarse.h"
#include "Efectivo.h"

class Efectivo;
class Anotarse;
class Estudiante;
class Seccion;
class OfertaLaboral : public ICollectible {
  private:
    int nroExpediente;
    string titulo;
    string desc;
    int cantHoras;
    dtRangoSalario* salario;
    dtFecha* fechaInicio;
    dtFecha* fechaFin;
    int cantPuestos;

    Seccion* seccionOferta;

    IDictionary* asignaturas; // --> de tipo Asignatura
    IDictionary* efectivos; // --> de tipo Efectivo
    IDictionary* anotarse; // --> de tipo Anotarse
    
  public:
    OfertaLaboral(int, string, string, int, dtRangoSalario*, dtFecha*, dtFecha*, int, Seccion*);
    OfertaLaboral(dtOfertaLaboral*, Seccion*);
    // void setNroExpediente(int); no creo que se deba cambiar el nroExpediente
    void setAsignaturas(IDictionary*);
    void setTitulo(string);
    void setDesc(string);
    void setCantHoras(int);
    void setSalario(dtRangoSalario*);
    void setFechaInicio(dtFecha*);
    void setFechaFin(dtFecha*);
    void setCantPuestos(int);
    int getNroExpediente();
    string getTitulo();
    string getDesc();
    int getCantHoras();
    dtRangoSalario* getSalario();
    dtFecha* getFechaInicio();
    dtFecha* getFechaFin();
    int getCantPuestos();

    bool checkAsignatura(int);
    bool checkEstudiante(string);

    dtOfertaLaboral* getInfoOfertaLaboral();
    ICollection* listarAsignaturasOferta();

    void altaEntrevista(Estudiante*, dtFecha*);

    void modificarLlamado(string, string, string, string, string, string, string, string);
    void crearEfectivo(Efectivo*);

    void asignarAsignatura(Asignatura *);
    ICollection* listarAsignaturas();

    void inscribirEstudianteEnOferta(Estudiante*, dtFecha*);
    dtSeccion* mostrarInfoSeccion();
    dtSucursal* mostrarInfoSucursal();
    dtEmpresa* mostrarInfoEmpresa();
    void desvincularSeccion();

    ~OfertaLaboral();

};
#endif