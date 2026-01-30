#ifndef MONTO_H
#define MONTO_H

#include "item.h"


class Monto: public Item
{
public:
    Monto();

    double calcular(Empleado &empleado);
};

#endif // MONTO_H
