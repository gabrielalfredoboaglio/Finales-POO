#include "DescuentoB.h"

DescuentoB::DescuentoB() {
    // Constructor vacío
}

DescuentoB::~DescuentoB() {
    // Destructor vacío
}

double DescuentoB::calcularDescuento(int cantTotal, double montoTotal) const {
    // Tipo B solo considera el monto, ignora la cantidad
    if (montoTotal > 20000) {
        return 25;
    }
    if (montoTotal > 10000) {
        return 20;
    }
    return 0;
}

char DescuentoB::getTipo() const {
    return 'B';
}
