#ifndef ARCHIVO_H
#define ARCHIVO_H

// ========== PUNTO 1: DISEÑO DEL SISTEMA ==========

#include "nodo.h"
using namespace std;

class Archivo : public Nodo {
private:
    // ========== LIBRE: Atributo peso ==========
    int peso;

public:
    Archivo();
    // Libre: Constructor con peso
    Archivo(string path, string nombre, int peso);
    ~Archivo();

    // ========== LIBRE: Getters/Setters de peso ==========
    int getPeso();
    void setPeso(int peso);
    
    char getTipo();
    // Libre: Implementación de obtenerPeso
    int obtenerPeso();
};

#endif // ARCHIVO_H
