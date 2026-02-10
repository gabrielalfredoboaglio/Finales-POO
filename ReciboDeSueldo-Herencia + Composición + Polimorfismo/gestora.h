#ifndef GESTORA_H
#define GESTORA_H

#include "empleado.h"
#include "item.h"
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Struct para archivo binario (formato del enunciado)
struct EmpleadoArchivo {
    int id;
    char nombre[200];
    double sueldoNeto;
    int aniosAntiguedad;
    int empleadosACargo;
};

class Gestora {
private:
    vector<Empleado*> empleados;
    vector<Item*> items;  // Items del recibo (composición)

    Empleado* buscarEmpleado(int id);

public:
    Gestora();
    ~Gestora();

    // Ejercicio 2: Leer archivo binario
    void leerArchivo(char* archivo);

    // Ejercicio 3: Guardar recibo en archivo de texto
    void guardarRecibo(int idEmpleado, char* archivo);

    // Ejercicio 4: Métodos con STL
    Empleado* obtenerEmpleadoMasACargo();
    double obtenerMontoTotalPagado();
    vector<Empleado*> obtener5MasAntiguosPorSalario();
};

#endif