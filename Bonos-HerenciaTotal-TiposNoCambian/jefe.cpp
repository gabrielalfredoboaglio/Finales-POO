#include "Jefe.h"


Jefe::Jefe() {
}

void Jefe::agregarEmpleado(empleado* e) {
    empleados_a_cargo.push_back(e);
}

char Jefe::getTipo() {  // ← IMPLEMENTAR
    return 'J';
}

double Jefe::getVentas() {
    // Calcular ventas totales de empleados a cargo
    double total = 0;
    for(empleado* e : empleados_a_cargo) {
        total += e->getVentas();
    }
    return total;
}

int Jefe::getCantidadEmpleados()
{
     return empleados_a_cargo.size();
}

double Jefe::calcularBono() {
    return getVentas() * (porcentaje / 100);
}
