#ifndef VENDEDOR_H
#define VENDEDOR_H

#include "empleado.h"


class vendedor : public empleado {
public:
    vendedor();
    char getTipo() ;  // ← AGREGAR
    double calcularBono() ;
};

#endif // VENDEDOR_H
