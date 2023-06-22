#ifndef SECCION_H
#define SECCION_H
#include <iostream>
using namespace std;



#include "Sucursal.h"
#include "OfertaLaboral.h"

#include "../datatype/dtSeccion.h"
#include "../datatype/dtSucursal.h"
#include "../datatype/dtEmpresa.h"

class OfertaLaboral;
class Sucursal;
class Seccion : public ICollectible {
  private:
    string nombre;
    string interno;
    Sucursal* sucursal;
    IDictionary* ofertasLaborales;
  public:
    Seccion() {};
    Seccion(string, string, Sucursal*);
    // void setNombre(string); no creo que se deba poder cambiar el nombre
    void setInterno(string);
    string getNombre();
    string getInterno();
    
    bool checkOfertaLaboral(int);
    dtSeccion* getInfoSeccion();
    void altaOfertaLaboral(OfertaLaboral*);
    void darBajaOferta(int);
    OfertaLaboral* getOfertaLaboral(int); 

    ICollection* listarOfertasLaborales();

    dtSucursal* mostrarInfoSucursal();
    dtEmpresa* mostrarInfoEmpresa();

    //void desvincularSeccion(int);

    ~Seccion();
};
#endif