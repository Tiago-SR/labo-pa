#ifndef DTESTUDIANTETODO_H
#define DTESTUDIANTETODO_H

#include <iostream>
using namespace std;
#include "dtFecha.h"

class dtEstudianteTodo {
private:
  string ci;
  string nombre;
  string apellido;
  dtFecha* fechaNacimiento;
  string telefono;

public:
  dtEstudianteTodo(string ci, string nombre, string apellido, dtFecha* fechaNacimiento, string telefono);
  string getCI();
  string getNombre();
  string getApellido();
  dtFecha* getFechaNacimiento();
  string getTelefono();
};

#endif