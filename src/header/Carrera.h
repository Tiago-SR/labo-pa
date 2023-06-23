#ifndef CARRERA_H
#define CARRERA_H

#include <iostream>
using namespace std;

#include "../../ICollection/interfaces/ICollectible.h"
#include "../../ICollection/interfaces/IDictionary.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../ICollection/Integer.h"

#include "Asignatura.h"


class Carrera : public ICollectible{
  private:
    int codigo;
    string nombre;
    int creditosNecesarios;
    IDictionary* asignaturas;
  public:
    Carrera(int codigo, string nombre, int creditosNecesarios);
    Carrera(int codigo, string nombre, int creditosNecesarios, IDictionary* asignaturas);
    virtual ~Carrera();

    int getCodigo();
    string getNombre();
    int getCreditosNecesarios();
    IDictionary* getAsignaturas();
    void agregarAsignatura(Asignatura* asignatura);

    void setCodigo(int codigo);
    void setNombre(string nombre);
    void setCreditosNecesarios(int creditosNecesarios);
    void setAsignaturas(IDictionary* asignaturas);
};
#endif
