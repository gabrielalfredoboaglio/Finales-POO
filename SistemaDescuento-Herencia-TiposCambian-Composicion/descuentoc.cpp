#include "DescuentoC.h"
#include <algorithm>  // Para std::max

DescuentoC::DescuentoC() {
    // Constructor vacío
}

DescuentoC::~DescuentoC() {
    // Destructor vacío
}

double DescuentoC::calcularDescuento(int cantTotal, double montoTotal) const {
    // Descuento por cantidad
    double descCantidad = (cantTotal / 100) * 1.0;

    // Descuento por monto
    double descMonto = 0;
    if (montoTotal > 20000) {
        descMonto = 25;
    } else if (montoTotal > 10000) {
        descMonto = 20;
    }

    // Tipo C retorna el MAYOR de los dos
    return std::max(descCantidad, descMonto);
}

char DescuentoC::getTipo() const {
    return 'C';
}
