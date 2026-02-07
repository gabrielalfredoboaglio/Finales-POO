#ifndef CARPETA_H
#define CARPETA_H

// ========== PUNTO 1: DISEÑO DEL SISTEMA ==========

#include "nodo.h"
#include <vector>
#include <algorithm>
using namespace std;

class Carpeta : public Nodo {
private:
    vector<Nodo*> elementos;

public:
    Carpeta();
    Carpeta(string path, string nombre);
    ~Carpeta();

    vector<Nodo*> getElementos();
    int getCantidadElementos();
    void agregarElemento(Nodo* elemento);
    Nodo* buscarElemento(string nombre);
    bool existeElemento(string nombre);
    
    char getTipo();
    int obtenerPeso();
    
    void ordenarPorNombre();
};

#endif // CARPETA_H
