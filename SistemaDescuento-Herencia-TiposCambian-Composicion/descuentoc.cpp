#include "descuentoc.h"
#include <algorithm>

using namespace std;

DescuentoC::DescuentoC() {
}

DescuentoC::~DescuentoC() {
}

// Libre: Tipo C retorna el mayor de los dos descuentos
double DescuentoC::calcularDescuento(int cantTotal, double montoTotal) {
    // Descuento por cantidad
    double descCantidad = (cantTotal / 100) * 1.0;

    // Descuento por monto
    double descMonto = 0;
    if(montoTotal > 20000) {
        descMonto = 25;
    } else if(montoTotal > 10000) {
        descMonto = 20;
    }

    return max(descCantidad, descMonto);
}

char DescuentoC::getTipo() {
    return 'C';
}
