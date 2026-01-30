#ifndef JEFE_H
#define JEFE_H
#include "Empleado.h"
#include <vector>

using namespace std;

class Jefe : public empleado {
private:
    vector<empleado*> empleados_a_cargo;

public:
    Jefe();
    char getTipo();
    void agregarEmpleado(empleado* e);
    double calcularBono();
    double getVentas();  // ← Sobreescribir para calcular ventas totales
    int getCantidadEmpleados();

};

#endif
