#include "DescuentoA.h"

DescuentoA::DescuentoA() {
    // Constructor vacío
}

DescuentoA::~DescuentoA() {
    // Destructor vacío
}

double DescuentoA::calcularDescuento(int cantTotal, double montoTotal) const {
    // Descuento por cantidad: 1% cada 100 productos
    double descCantidad = (cantTotal / 100) * 1.0;

    // Descuento por monto
    double descMonto = 0;
    if (montoTotal > 20000) {
        descMonto = 25;
    } else if (montoTotal > 10000) {
        descMonto = 20;
    }

    // Tipo A suma ambos descuentos
    return descCantidad + descMonto;
}

char DescuentoA::getTipo() const {
    return 'A';
}
