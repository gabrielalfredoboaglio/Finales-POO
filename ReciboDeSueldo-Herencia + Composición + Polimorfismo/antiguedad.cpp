#include "antiguedad.h"

Antiguedad::Antiguedad() {}

double Antiguedad::calcular(Empleado &empleado)
{ return empleado.getSueldoNeto() *
                  empleado.getAniosAntiguedad() / 100.0;
}
