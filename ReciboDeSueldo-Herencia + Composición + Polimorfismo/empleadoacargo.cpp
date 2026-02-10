#include "empleadoacargo.h"

using namespace std;

EmpleadoACargo::EmpleadoACargo() {}

double EmpleadoACargo::calcular(Empleado& empleado) {
    return 1000 * empleado.getEmpleadosACargo();
}

char* EmpleadoACargo::getNombreItem() {
    return (char*)"Empleados a Cargo";
}