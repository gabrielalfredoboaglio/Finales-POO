#ifndef GESTORA_H
#define GESTORA_H

#include "paquete.h"
#include "conjuntopaquetes.h"
#include <vector>
#include <fstream>
using namespace std;

// ========== STRUCTS PARA ARCHIVOS BINARIOS ==========

// Archivo: paquetes.dat
struct PaqueteArchivo {
    char codigo[100];
    char nombre[100];
    int version;
};

// Archivo: dependencias.dat
struct DependenciaArchivo {
    char codigoPaquete[100];
    char codigoPaqueteDependencia[100];
};

// ========== agregar para punto libre ==========
struct ConjuntoArchivo {
    char codigo[100];
    char nombre[100];
    int version;
};

// ========== agregar para punto libre ==========
struct ConjuntoPaqueteArchivo {
    char codigoConjunto[100];
    char codigoPaquete[100];
};

// ========== CLASE GESTORA ==========

class Gestora {
private:
    vector<Paquete*> paquetes;
    vector<ConjuntoPaquetes*> conjuntos; // ========== agregar para punto libre ==========

    // Métodos auxiliares privados
    Paquete* buscarPaquete(char* codigo);
    ConjuntoPaquetes* buscarConjunto(char* codigo); // ========== agregar para punto libre ==========

public:
    Gestora();
    ~Gestora();

    // Métodos para agregar elementos
    void agregarPaquete(Paquete* paquete);
    void agregarConjunto(ConjuntoPaquetes* conjunto); // ========== agregar para punto libre ==========

    // Guardar en archivos binarios
    void guardarArchivos(char* archPaquetes, char* archDependencias);

    // Leer archivos binarios
    void leerArchivos(char* archPaquetes, char* archDependencias);

    // Ejercicio 1: Obtener todas las dependencias de un paquete
    vector<Paquete*> obtenerTodasDependencias(char* codigoPaquete);

    // Ejercicio 2: Escribir árbol de dependencias en archivo de texto
    void escribirArbolDependencias(char* codigoPaquete);

    // Ejercicio 3: Métodos con STL
    vector<Paquete*> obtenerTop5PaquetesConMasDependencias();
    vector<Paquete*> obtenerPaquetesSinDependencias();

    // ========== agregar para punto libre ==========
    void guardarArchivosConjuntos(char* archConjuntos, char* archConjuntosPaquetes);
    void leerArchivosConjuntos(char* archConjuntos, char* archConjuntosPaquetes);
    vector<Paquete*> instalarConjunto(char* codigoConjunto);

    // Getters
    vector<Paquete*> getPaquetes();
    vector<ConjuntoPaquetes*> getConjuntos(); // ========== agregar para punto libre ==========
};

#endif // GESTORA_H
