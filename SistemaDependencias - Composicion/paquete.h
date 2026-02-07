#ifndef PAQUETE_H
#define PAQUETE_H

#include <vector>
#include <iostream>
using namespace std;

class Paquete {
private:
    char codigo[100];
    char nombre[100];
    int version;
    vector<Paquete*> dependencias;

    // Ejercicio 1: Helper recursivo para dependencias transitivas
    void obtenerTodasDependenciasRec(vector<Paquete*>& resultado, vector<Paquete*>& visitados);

public:
    Paquete();
    Paquete(char* codigo, char* nombre, int version);
    ~Paquete();

    char* getCodigo();
    char* getNombre();
    int getVersion();
    vector<Paquete*> getDependencias();
    int getCantidadDependencias();

    void setCodigo(char* codigo);
    void setNombre(char* nombre);
    void setVersion(int version);
    void agregarDependencia(Paquete* paquete);

    // Ejercicio 1: Obtener todas las dependencias (incluyendo transitivas)
    vector<Paquete*> obtenerTodasDependencias();

    // Ejercicio 2: Escribir árbol de dependencias
    void escribirArbol(ostream& os, int nivel);

    // Ejercicio 2: Operador << para escribir árbol de dependencias
    friend ostream& operator<<(ostream& os, Paquete& paquete);
};

#endif // PAQUETE_H
