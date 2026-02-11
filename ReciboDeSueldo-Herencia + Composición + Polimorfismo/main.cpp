#include "gestora.h"
#include <iostream>

using namespace std;

int main()
{
    Gestora gestora;

    // Ejercicio 2: Leer archivo binario
    char archEmpleados[] = "empleados.dat";
    gestora.leerArchivo(archEmpleados);

    // ========== agregar para punto libre ==========
    // Leer qué items aplican a cada empleado
    char archItems[] = "empleados_items.dat";
    gestora.leerArchivoItems(archItems);

    // Ejercicio 3: Guardar recibo en archivo de texto
    char archRecibo[] = "recibo.txt";
    gestora.guardarRecibo(1, archRecibo);

    // Ejercicio 4a: Empleado con más empleados a cargo
    Empleado* masACargo = gestora.obtenerEmpleadoMasACargo();
    if(masACargo != nullptr) {
        cout << "Mas a cargo: " << masACargo->getNombre()
             << " (" << masACargo->getEmpleadosACargo() << ")" << endl;
    }

    // Ejercicio 4b: Monto total pagado
    double montoTotal = gestora.obtenerMontoTotalPagado();
    cout << "Monto total pagado: $" << montoTotal << endl;

    // Ejercicio 4c: 5 más antiguos por salario
    vector<Empleado*> top5 = gestora.obtener5MasAntiguosPorSalario();
    cout << "Top 5 mas antiguos por salario:" << endl;
    for(Empleado* e : top5) {
        cout << "  " << e->getNombre() << " - Antiguedad: "
             << e->getAniosAntiguedad() << " - Sueldo: $"
             << e->getSueldoNeto() << endl;
    }

    // ========== agregar para punto libre ==========
    // Guardar archivo de items por empleado
    gestora.guardarArchivoItems(archItems);

    return 0;
}
