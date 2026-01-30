#include "empleadoacargo.h"

EmpleadoACargo::EmpleadoACargo() {}

double EmpleadoACargo::calcular(Empleado &empleado)
{
    return 1000* empleado.getEmpleadosACargo();
}
