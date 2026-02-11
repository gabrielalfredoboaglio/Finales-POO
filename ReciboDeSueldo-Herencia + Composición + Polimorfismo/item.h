#ifndef ITEM_H
#define ITEM_H

#include "empleado.h"
using namespace std;

// Ejercicio 1: Clase abstracta Item (polimorfismo)
class Item {
public:
    Item();
    virtual ~Item();
    virtual double calcular(Empleado& empleado) = 0;
    virtual char* getNombreItem() = 0;
    // ========== agregar para punto libre ==========
    virtual char getTipo() = 0;
};

#endif