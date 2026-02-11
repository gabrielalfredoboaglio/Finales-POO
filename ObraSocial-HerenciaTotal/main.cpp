#include "gestora.h"
#include <iostream>

using namespace std;

int main() {
    Gestora gestora;

    // Ejercicio 1: Leer archivos
    char archClientes[] = "clientes.dat";
    gestora.leerArchivos(archClientes);

    // Ejercicio 1: Verificar prestación
    char prestacion1[] = "Consulta medica";
    cout << "Cliente 1 tiene 'Consulta medica': "
         << (gestora.clienteTienePrestacion(1, prestacion1) ? "SI" : "NO") << endl;

    char prestacion2[] = "Cirugia estetica";
    cout << "Cliente 2 tiene 'Cirugia estetica': "
         << (gestora.clienteTienePrestacion(2, prestacion2) ? "SI" : "NO") << endl;

    // Ejercicio 2.1: Top 5 que más usaron el servicio
    cout << endl << "=== TOP 5 QUE MAS USARON EL SERVICIO ===" << endl;
    vector<Cliente*> top5 = gestora.obtener5MasUsaron();
    for(Cliente* c : top5) {
        cout << c->getNombre() << " - Tipo: " << c->getTipo()
             << " - Cantidad: " << c->getCantidad() << endl;
    }

    // Ejercicio 2.2: Todas las prestaciones de todos los planes
    cout << endl << "=== TODAS LAS PRESTACIONES ===" << endl;
    vector<string> todas = gestora.obtenerTodasPrestaciones();
    for(string& p : todas) {
        cout << "- " << p << endl;
    }

    // Ejercicio 2.3: Cantidad de veces por tipo de plan
    cout << endl << "=== CANTIDAD POR TIPO DE PLAN ===" << endl;
    map<char, int> porTipo = gestora.obtenerCantidadPorTipo();
    for(auto& par : porTipo) {
        cout << "Tipo " << par.first << ": " << par.second << " usos" << endl;
    }

    // Ejercicio 2.4: Prestaciones que están en todos los planes
    cout << endl << "=== PRESTACIONES EN TODOS LOS PLANES ===" << endl;
    vector<string> enTodos = gestora.obtenerPrestacionesEnTodosPlanes();
    for(string& p : enTodos) {
        cout << "- " << p << endl;
    }

    return 0;
}
