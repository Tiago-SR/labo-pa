#ifndef EMPRESA_H
#define EMPRESA_H
#include <iostream>
using namespace std;

#include "../../ICollection/interfaces/ICollectible.h"
#include "../../ICollection/interfaces/IDictionary.h"
#include "../../ICollection/interfaces/ICollection.h"
#include "../../ICollection/collections/List.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../ICollection/String.h"


#include "../datatype/dtEmpresa.h"
#include "../datatype/dtDireccion.h"


#include "Sucursal.h"
#include "OfertaLaboral.h"


class Sucursal;
class OfertaLaboral;

class Empresa : public ICollectible {
  private:
    string nombre;
    string RUT;
    IDictionary* sucursales; // --> de tipo Sucursal  
  public:
    Empresa(string, string);
    void setNombre(string);
    // void setRUT(string); no creo que se deba poder cambiar el rut
    string getNombre();
    string getRUT();

    bool checkSucursal(string);
    void agregarSucursal(string, string, dtDireccion*);
    void bajaSucursal(string);

    bool checkSeccion(string, string);
    void agregarSeccion(string, string, string);
    void bajaSeccion(string, string);

    Sucursal* getSucursal(string);

    ICollection* listarSucursales();
    ICollection* listarSecciones(string);

    void altaOfertaLaboral(string, string, OfertaLaboral*);
    void darBajaOferta(string, string, int);
    
  
    ICollection* listarInfoSucursales() { return nullptr; }; // --> el ICollection tiene dtSucursal
    ICollection* listarInfoSecciones(string) { return nullptr; }; // -> el ICollection tiene dtSeccion
    
    dtEmpresa* getInfoEmpresa();

    ~Empresa();
};
#endif