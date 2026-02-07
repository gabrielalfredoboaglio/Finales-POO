#ifndef CLIENTE_H
#define CLIENTE_H

#include "descuento.h"
using namespace std;

// ========== EJERCICIO 1: Clase Cliente con Composición (Estrategia) ==========

class Cliente {
private:
    int nro;
    char nombre[200];
    Descuento* estrategiaDescuento;

public:
    Cliente();
    Cliente(int n, char* nom, char tipo);
    ~Cliente();

    // Permite cambiar el tipo de cliente en tiempo de ejecución
    void cambiarTipo(char nuevoTipo);

    // Delega el cálculo a la estrategia
    double calcularDescuento(int cantTotal, double montoTotal);

    int getNro();
    char* getNombre();
    char getTipo();

    void setNro(int n);
    void setNombre(char* nom);
};

#endif
