#ifndef SUCURSAL_H
#define SUCURSAL_H


#include "Empresa.h"
#include "Seccion.h"

#include "../datatype/dtDireccion.h"
#include "../datatype/dtSucursal.h"
#include "../datatype/dtEmpresa.h"

class Seccion;
class OfertaLaboral;
class Empresa;

class Sucursal : public ICollectible {
  private:
    string nombre;
    string telefonoSucursal;
    dtDireccion* direccionSucursal;

    Empresa* empresa;
    IDictionary* secciones;
  public:
    Sucursal(string nombre, string telefono, dtDireccion* direccion, Empresa*);
    // void setNombre(string); no creo que se deba poder cambiar el nombre
    void setTelefono(string);
    void setDireccion(dtDireccion* d);
    string getNombre();
    string getTelefonoSucursal();
    dtDireccion* getDireccionSucursal();

    Seccion* getSeccion(string);
    ICollection* listarSecciones();


    bool checkSeccion(string);
    void agregarSeccion(string, string);
    void bajaSeccion(string);

    void altaOfertaLaboral(string, OfertaLaboral*);
    void darBajaOferta(string, int);

    // ICollection* listarInfoSecciones();
    dtSucursal* getInfoSucursal();
    dtEmpresa* mostrarInfoEmpresa();

    ~Sucursal();
};
#endif