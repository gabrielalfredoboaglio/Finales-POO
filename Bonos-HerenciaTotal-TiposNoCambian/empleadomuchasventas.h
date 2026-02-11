// ========== LIBRE: Clase EmpleadoMuchasVentas ==========
#ifndef EMPLEADOMUCHASVENTAS_H
#define EMPLEADOMUCHASVENTAS_H

#include "Empleado.h"
#include <vector>
using namespace std;

class empleadoMuchasVentas : public empleado {
private:
    vector<double> ventas_individuales;  // Vector para almacenar cada venta

public:
    empleadoMuchasVentas();
    char getTipo();
    void agregarVenta(double monto);
    double getVentas();  // Sobreescribir para calcular suma de todas las ventas
    double calcularBono();
};

#endif // EMPLEADOMUCHASVENTAS_H
