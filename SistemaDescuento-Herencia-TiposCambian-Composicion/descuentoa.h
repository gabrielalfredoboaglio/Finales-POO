#ifndef DESCUENTOA_H
#define DESCUENTOA_H

#include "Descuento.h"

// ESTRATEGIA CONCRETA TIPO A
// Aplica TODOS los descuentos (suma cantidad + monto)
class DescuentoA : public Descuento {
public:
    DescuentoA();
    ~DescuentoA();

    double calcularDescuento(int cantTotal, double montoTotal) const override;
    char getTipo() const override;
};

#endif
