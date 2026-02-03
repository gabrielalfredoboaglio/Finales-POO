#ifndef ARCHIVO_H
#define ARCHIVO_H

// ========== PUNTO 1: DISEÑO DEL SISTEMA ==========

#include "nodo.h"
using namespace std;

class Archivo : public Nodo {
private:
    int peso;

public:
    Archivo();
    Archivo(string path, string nombre, int peso);
    ~Archivo();

    int getPeso();
    void setPeso(int peso);
    
    char getTipo();
    int obtenerPeso();
};

#endif // ARCHIVO_H
