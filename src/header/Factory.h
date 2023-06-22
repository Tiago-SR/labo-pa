#ifndef FACTORY_H
#define FACTORY_H
#include <iostream>

#include "ISistema.h"
#include "Sistema.h"

class Factory {
  public:
    static ISistema* getISistema();
};


#endif