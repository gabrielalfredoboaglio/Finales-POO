#include "monto.h"

using namespace std;

Monto::Monto() {}

double Monto::calcular(Empleado& empleado) {
    return empleado.getSueldoNeto();
}

char* Monto::getNombreItem() {
    return (char*)"Monto";
}

// ========== agregar para punto libre ==========
char Monto::getTipo() {
    return 'M';
}