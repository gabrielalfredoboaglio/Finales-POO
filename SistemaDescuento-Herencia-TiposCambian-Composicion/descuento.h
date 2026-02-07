#ifndef DESCUENTO_H
#define DESCUENTO_H

using namespace std;

// ========== EJERCICIO 1: Clase abstracta Descuento (Estrategia) ==========

class Descuento {
public:
    virtual ~Descuento();

    virtual double calcularDescuento(int cantTotal, double montoTotal) = 0;
    virtual char getTipo() = 0;
};

#endif
