#ifndef DESCUENTOA_H
#define DESCUENTOA_H

#include "descuento.h"
using namespace std;

// ========== EJERCICIO 1: Tipo A - Suma ambos descuentos ==========

class DescuentoA : public Descuento {
public:
    DescuentoA();
    ~DescuentoA();

    double calcularDescuento(int cantTotal, double montoTotal);
    char getTipo();
};

#endif
