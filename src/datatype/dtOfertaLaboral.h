#ifndef DTOFERTALABORAL_H
#define DTOFERTALABORAL_H


#include <iostream>
using namespace std;
#include "../../ICollection/interfaces/ICollectible.h"
#include "dtRangoSalario.h"
#include "dtFecha.h"

class dtOfertaLaboral : public ICollectible {
private:
  int nroExpediente;
  string titulo;
  string desc;
  int cantHoras;
  dtRangoSalario* salario;
  dtFecha* fechaInicio;
  dtFecha* fechaFin;
  int cantPuestos;

public:
  dtOfertaLaboral(int nroExpediente, string titulo, string desc, int cantHoras, dtRangoSalario* salario, dtFecha* fechaInicio, dtFecha* fechaFin, int cantPuestos);
  int getNroExpediente();
  string getTitulo();
  string getDesc();
  int getCantHoras();
  dtRangoSalario* getSalario();
  dtFecha* getFechaInicio();
  dtFecha* getFechaFin();
  int getCantPuestos();
};

#endif