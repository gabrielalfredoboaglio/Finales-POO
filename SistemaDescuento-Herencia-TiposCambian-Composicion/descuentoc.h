#ifndef DESCUENTOC_H
#define DESCUENTOC_H

#include "Descuento.h"

// ESTRATEGIA CONCRETA TIPO C
// Calcula ambos descuentos y retorna el MAYOR
class DescuentoC : public Descuento {
public:
    DescuentoC();
    ~DescuentoC();

    double calcularDescuento(int cantTotal, double montoTotal) const override;
    char getTipo() const override;
};

#endif
