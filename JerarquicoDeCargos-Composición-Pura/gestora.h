#ifndef GESTORA_H
#define GESTORA_H

#include "Empleado.h"
#include <vector>
#include <string>
using namespace std;

// ========== STRUCT PARA ARCHIVO BINARIO ==========
struct EmpleadoArchivo {
    int numero;
    char nombre[200];
    int cantidad_a_cargo;
};

// ========== STRUCT PARA JERARQUÍA BINARIA (PUNTO LIBRE) ==========
struct JerarquiaArchivo {
    int numero_jefe;
    int numero_subordinado;
};

class Gestora {
private:
    vector<Empleado*> empleados;

    // Métodos auxiliares privados
    Empleado* buscarEmpleado(int numero);
    void leerLineaRecursiva(ifstream& archivo, Empleado* jefe, int nivelPadre);
    int contarGuiones(const string& linea);
    void parsearLinea(const string& linea, int& numero, string& nombre);

    // Para guardar jerarquía binaria (punto libre)
    void guardarJerarquiaRecursiva(ofstream& archiJerarquia, Empleado* emp);

public:
    Gestora();
    ~Gestora();

    // Punto 2: Leer archivo de texto
    void leerArchivoTexto(const char* nombreArchivo);

    // Punto 3: Obtener responsable
    Empleado* obtenerResponsable(int numeroEmpleado);

    // Punto 4: Guardar archivo binario
    void guardarArchivoBinario(const char* nombreArchivo);

    // Punto 5.1: Empleado con más personas a cargo
    Empleado* obtenerEmpleadoMasSubordinados();

    // Punto 5.2: Empleados con número repetido
    vector<int> obtenerNumerosRepetidos();

    // Punto Libre: Guardar jerarquía en archivos binarios
    void guardarJerarquiaBinaria(const char* nombreArchivoEmpleados,
                                 const char* nombreArchivoJerarquia);


};

#endif // GESTORA_H
