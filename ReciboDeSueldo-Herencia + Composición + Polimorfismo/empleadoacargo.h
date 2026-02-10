#ifndef EMPLEADOACARGO_H
#define EMPLEADOACARGO_H

#include "item.h"
using namespace std;

// Ejercicio 1: Item EmpleadoACargo = 1000 * cantidad
class EmpleadoACargo : public Item {
public:
    EmpleadoACargo();
    double calcular(Empleado& empleado);
    char* getNombreItem();
};

#endif