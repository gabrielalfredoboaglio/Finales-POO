#ifndef ITEM_H
#define ITEM_H

#include "empleado.h"
class Item
{

public:
    Item();
    virtual double calcular(Empleado& empleado)  = 0;
};

#endif // ITEM_H
