#ifndef DTRANGOSALARIO_H
#define DTRANGOSALARIO_H

#include <iostream>

class dtRangoSalario {
private:
  float salarioMin;
  float salarioMax;
public:
  dtRangoSalario(float salarioMin, float salarioMax);
  float getSalarioMin();
  float getSalarioMax();
};
#endif