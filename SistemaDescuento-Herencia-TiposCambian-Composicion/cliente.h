#ifndef CLIENTE_H
#define CLIENTE_H

#include "Descuento.h"

// CLASE PRINCIPAL CON COMPOSICIÓN
// Ahora Cliente NO es una clase abstracta, es una clase concreta
// que TIENE una estrategia de descuento
class Cliente {
private:
    int nro;
    char nombre[200];
    Descuento* estrategiaDescuento;  // COMPOSICIÓN - puntero a estrategia

public:
    Cliente(int n, const char* nom, char tipo);
    ~Cliente();

    // MÉTODO CLAVE: permite cambiar el tipo de cliente
    void cambiarTipo(char nuevoTipo);

    // Delega el cálculo a la estrategia
    double calcularDescuento(int cantTotal, double montoTotal) const;

    // Getters
    int getNro() const;
    char* getNombre();
    char getTipo() const;

    // Setters
    void setNro(int n);
    void setNombre(const char* nom);
};

#endif
