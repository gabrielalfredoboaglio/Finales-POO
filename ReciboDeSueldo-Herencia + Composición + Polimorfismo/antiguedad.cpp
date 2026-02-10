#include "antiguedad.h"

using namespace std;

Antiguedad::Antiguedad() {}

double Antiguedad::calcular(Empleado& empleado) {
    return empleado.getSueldoNeto() * empleado.getAniosAntiguedad() / 100.0;
}

char* Antiguedad::getNombreItem() {
    return (char*)"Antiguedad";
}