#ifndef EMPLEADOACARGO_H
#define EMPLEADOACARGO_H

#include "item.h"


class EmpleadoACargo : public Item
{
public:
    EmpleadoACargo();
    double calcular(Empleado &empleado);
};

#endif // EMPLEADOACARGO_H
