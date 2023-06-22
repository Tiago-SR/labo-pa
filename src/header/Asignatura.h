#ifndef ASIGNATURA_H
#define ASIGNATURA_H
#include <iostream>
using namespace std;


#include "../datatype/dtAsignatura.h"

class Asignatura : public ICollectible {
  private:
    int codigo;
    string nombre;
    int creditos;
  public:
    Asignatura(int, string, int);
    // void setCodigo(int); no creo que se deba poder cambiar el codigo de la asignatura
    void setNombre(string);
    void setCreditos(int);
    int getCodigo();
    string getNombre();
    int getCreditos();

    dtAsignatura* getInfoAsignatura();

};
#endif