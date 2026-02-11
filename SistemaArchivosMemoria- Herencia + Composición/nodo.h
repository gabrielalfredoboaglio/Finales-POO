#ifndef NODO_H
#define NODO_H

// ========== PUNTO 1: DISEÑO DEL SISTEMA ==========

#include <string>
#include <iostream>
using namespace std;

class Nodo {
protected:
    string path;
    string nombre;

public:
    Nodo();
    Nodo(string path, string nombre);
    virtual ~Nodo();

    string getPath();
    string getNombre();
    void setPath(string path);
    void setNombre(string nombre);

    virtual char getTipo() = 0;
    // ========== LIBRE: Método virtual puro para obtener peso ==========
    virtual int obtenerPeso() = 0;
    
    friend ostream& operator<<(ostream& os, Nodo& nodo);
};

#endif // NODO_H
