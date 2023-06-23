#ifndef ANOTARSE_H
#define ANOTARSE_H

#include <iostream>
using namespace std;

#include "../../ICollection/interfaces/ICollection.h"
#include "../../ICollection/collections/List.h"

#include "../datatype/dtFecha.h"
#include "../datatype/dtOfertaLaboral.h"

#include "Estudiante.h"
#include "OfertaLaboral.h"

class OfertaLaboral;
class Estudiante;
class Anotarse : public ICollectible {
  private:
    dtFecha* fecha;
    ICollection* entrevista; // ->dtFecha
    Estudiante * estudiante;
    OfertaLaboral* ofertaLaboral;
  public:
    Anotarse() {};
    Anotarse(Estudiante*, OfertaLaboral*, dtFecha*);
    void setFecha(dtFecha*);
    dtFecha* getFecha();
    Estudiante * getEstudiante();
    OfertaLaboral * getOfertaLaboral();

    void altaEntrevista(dtFecha*);
    dtOfertaLaboral* mostrarLlamadoEstudiante(); // es como getOfertaLaboral pero devolviendo datatype

    ~Anotarse() {};
};

#endif