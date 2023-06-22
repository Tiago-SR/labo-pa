#include "../header/Factory.h"
ISistema* Factory::getISistema() {
  return Sistema::getInstance();
}