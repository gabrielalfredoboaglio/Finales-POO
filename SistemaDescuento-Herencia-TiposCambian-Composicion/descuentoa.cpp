#include "descuentoa.h"

using namespace std;

DescuentoA::DescuentoA() {
}

DescuentoA::~DescuentoA() {
}

// Ejercicio 1: Tipo A suma ambos descuentos
double DescuentoA::calcularDescuento(int cantTotal, double montoTotal) {
    // Descuento por cantidad: 1% cada 100 productos
    double descCantidad = (cantTotal / 100) * 1.0;

    // Descuento por monto
    double descMonto = 0;
    if(montoTotal > 20000) {
        descMonto = 25;
    } else if(montoTotal > 10000) {
        descMonto = 20;
    }

    return descCantidad + descMonto;
}

char DescuentoA::getTipo() {
    return 'A';
}
