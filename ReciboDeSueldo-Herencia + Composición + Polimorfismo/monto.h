#ifndef MONTO_H
#define MONTO_H

#include "item.h"
using namespace std;

// Ejercicio 1: Item Monto = sueldo neto
class Monto : public Item {
public:
    Monto();
    double calcular(Empleado& empleado);
    char* getNombreItem();
};

#endif