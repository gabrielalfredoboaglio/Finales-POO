#include "descuentob.h"

using namespace std;

DescuentoB::DescuentoB() {
}

DescuentoB::~DescuentoB() {
}

// Ejercicio 1: Tipo B solo descuento por monto
double DescuentoB::calcularDescuento(int cantTotal, double montoTotal) {
    if(montoTotal > 20000) {
        return 25;
    }
    if(montoTotal > 10000) {
        return 20;
    }
    return 0;
}

char DescuentoB::getTipo() {
    return 'B';
}
