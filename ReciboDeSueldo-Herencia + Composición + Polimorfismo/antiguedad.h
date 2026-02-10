#ifndef ANTIGUEDAD_H
#define ANTIGUEDAD_H

#include "item.h"
using namespace std;

// Ejercicio 1: Item Antiguedad = sueldoNeto * anios / 100
class Antiguedad : public Item {
public:
    Antiguedad();
    double calcular(Empleado& empleado);
    char* getNombreItem();
};

#endif