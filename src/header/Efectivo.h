#ifndef EFECTIVO_H
#define EFECTIVO_H
#include <iostream>
using namespace std;

#include "../datatype/dtFecha.h"
#include "../datatype/dtOfertaLaboral.h"

#include "Estudiante.h"
#include "OfertaLaboral.h"

class Estudiante;
class Efectivo : public ICollectible {
  private:
    dtFecha* fecha;
    float sueldo;
    Estudiante * estudiante;
    OfertaLaboral * ofertaLaboral;
  public:
    Efectivo(dtFecha*, float, Estudiante*, OfertaLaboral*);
    void setFecha(dtFecha*);
    void setSueldo(float sueldo);
    string getFecha();
    float getSueldo();
    Estudiante * getEstudiante();
    OfertaLaboral * getOfertaLaboral();

    dtOfertaLaboral* mostrarLlamadoEstudiante(); // es como getOfertaLaboral pero devolviendo datatype
    

    ~Efectivo() {};
};

#endif