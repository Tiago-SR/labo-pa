#include "dtRangoSalario.h"

dtRangoSalario::dtRangoSalario(float salarioMin, float salarioMax) {
  this->salarioMin = salarioMin;
  this->salarioMax = salarioMax;
}
float dtRangoSalario::getSalarioMin() {
  return salarioMin;
}
float dtRangoSalario::getSalarioMax() {
  return salarioMax;
}