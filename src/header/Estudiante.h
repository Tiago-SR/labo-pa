#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H
#include <iostream>
using namespace std;

#include "../../ICollection/interfaces/ICollection.h"
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../ICollection/interfaces/IDictionary.h"
#include "../../ICollection/Integer.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../ICollection/collections/List.h"

#include "../datatype/dtDireccion.h"
#include "../datatype/dtFecha.h"
#include "../datatype/dtEstudiante.h"
#include "../datatype/dtEstudianteTodo.h"

#include "Asignatura.h"
#include "Anotarse.h"
#include "Efectivo.h"
#include "Carrera.h"

class Anotarse;
class Efectivo;
class Estudiante : public ICollectible {
  private:
    string ci;
    string nombre;
    string apellido;
    string telefono;
    dtDireccion* direccion;
    dtFecha* fechaNacimiento;
    int creditos;
    IDictionary *asignaturas; // --> de tipo Asignatura
    IDictionary *efectivos; // --> de tipo OfertaLaboral
    IDictionary *anotarse; // --> de tipo Anotarse
    IDictionary *carreras;
  public:
    Estudiante(string, string, string, string, dtDireccion*, dtFecha*, int);
    // void setCi(string); no creo que deba poderse cambiar la ci
    void setTelefono(string);
    void setNombre(string);
    void setApellido(string);
    void setDireccion(dtDireccion*);
    void setFechaNacimiento(dtFecha*);
    void setCreditos(int);
    string getCi();
    string getNombre();
    string getApellido();
    string getTelefono();
    dtDireccion* getDireccion();
    dtFecha* getFechaNacimiento();
    int getCreditos();

    bool checkAsignatura(int);

    void quitarAsignatura(int);

    bool checkCarrera(int);
    void agregarCarrera(Carrera*);
    void quitarCarrera(int);
    bool tieneCarreras();
    ICollection* mostrarCarreras();

    void agregarAsignatura(Asignatura*);
    bool estaVinculadoOferta(int);
    void crearVinculo(Anotarse*);
    void crearEfectivo(Efectivo*);
    dtEstudiante* getEstudiante();
    dtEstudianteTodo* getEstudianteTodo();
    ICollection* mostrarAsignaturas();
    ICollection* mostrarLlamadosEstudiante();

    ~Estudiante();

};
#endif