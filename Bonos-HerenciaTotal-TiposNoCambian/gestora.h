#ifndef GESTORA_H
#define GESTORA_H

#include <string>
#include <vector>
#include "Empleado.h"

using namespace std;

// ========== STRUCTS PARA ARCHIVOS ==========
struct EmpleadoArchivo {
    int nro;
    char nombre[200];
    double ventas;
    double porcentaje;
    char tipo;  // 'V' o 'J'
};

struct JefeArchivo {
    int nro_jefe;
    int nro_empleado;
};

struct VentaEmpleadoArchivo {
    int nro_empleado;
    double monto_venta;
};

// ========== CLASE GESTORA ==========
class Gestora {
private:
    vector<empleado*> empleados;

    // Métodos auxiliares privados
    empleado* buscarEmpleado(int nro);

public:
    Gestora();
    ~Gestora();

    // Punto 2: Leer archivos
    void leerArchivos();

    // Punto 3: Guardar archivo de texto (lo haremos después)
    void guardarArchivoTexto();

    // Punto 4: Métodos con STL (los haremos después)
    vector<empleado*> obtenerEmpleadosMayorBono();
    vector<empleado*> obtenerJefesMasEmpleados();
    vector<string> obtenerNombresRepetidos();
};

#endif
