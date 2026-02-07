#ifndef DESCUENTOC_H
#define DESCUENTOC_H

#include "descuento.h"
using namespace std;

// ========== LIBRE: Tipo C - Obtiene el mayor de los dos descuentos ==========

class DescuentoC : public Descuento {
public:
    DescuentoC();
    ~DescuentoC();

    double calcularDescuento(int cantTotal, double montoTotal);
    char getTipo();
};

#endif
