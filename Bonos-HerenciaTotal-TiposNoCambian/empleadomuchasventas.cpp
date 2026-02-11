// ========== LIBRE: Implementación EmpleadoMuchasVentas ==========
#include "EmpleadoMuchasVentas.h"

empleadoMuchasVentas::empleadoMuchasVentas() {
    // El constructor base ya inicializa los atributos heredados
}

char empleadoMuchasVentas::getTipo() {
    return 'M';  // 'M' de Muchas ventas
}

void empleadoMuchasVentas::agregarVenta(double monto) {
    ventas_individuales.push_back(monto);
}

double empleadoMuchasVentas::getVentas() {
    // Calcular la suma de todas las ventas individuales
    double total = 0;
    for(double venta : ventas_individuales) {
        total += venta;
    }
    return total;
}

double empleadoMuchasVentas::calcularBono() {
    // El bono se calcula sobre el total de ventas
    return getVentas() * (porcentaje / 100);
}
