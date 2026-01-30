#ifndef DESCUENTOB_H
#define DESCUENTOB_H

#include "Descuento.h"

// ESTRATEGIA CONCRETA TIPO B
// Solo aplica descuento por monto anual
class DescuentoB : public Descuento {
public:
    DescuentoB();
    ~DescuentoB();

    double calcularDescuento(int cantTotal, double montoTotal) const override;
    char getTipo() const override;
};

#endif
