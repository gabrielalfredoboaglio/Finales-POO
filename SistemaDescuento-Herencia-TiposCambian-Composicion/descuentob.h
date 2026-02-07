#ifndef DESCUENTOB_H
#define DESCUENTOB_H

#include "descuento.h"
using namespace std;

// ========== EJERCICIO 1: Tipo B - Solo descuento por monto ==========

class DescuentoB : public Descuento {
public:
    DescuentoB();
    ~DescuentoB();

    double calcularDescuento(int cantTotal, double montoTotal);
    char getTipo();
};

#endif
