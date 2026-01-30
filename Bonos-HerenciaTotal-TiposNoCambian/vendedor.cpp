#include "vendedor.h"

vendedor::vendedor() {
}

double vendedor::calcularBono()
{
    return ventas * (porcentaje / 100);
}


char vendedor::getTipo() {
    return 'V';
}
