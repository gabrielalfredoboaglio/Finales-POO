#ifndef ANTIGUEDAD_H
#define ANTIGUEDAD_H

#include "item.h"


class Antiguedad : public Item
{
public:
    Antiguedad();
    double calcular(Empleado &empleado);
};

#endif // ANTIGUEDAD_H
