#include "Cliente.h"
#include "DescuentoA.h"
#include "DescuentoB.h"
#include "DescuentoC.h"
#include <cstring>

// Constructor: crea el cliente con la estrategia correspondiente
Cliente::Cliente(int n, const char* nom, char tipo) {
    nro = n;
    strcpy(nombre, nom);

    // Asigna la estrategia según el tipo
    if (tipo == 'A') {
        estrategiaDescuento = new DescuentoA();
    } else if (tipo == 'B') {
        estrategiaDescuento = new DescuentoB();
    } else if (tipo == 'C') {
        estrategiaDescuento = new DescuentoC();
    } else {
        estrategiaDescuento = nullptr;  // Tipo inválido
    }
}

// Destructor: libera la estrategia
Cliente::~Cliente() {
    delete estrategiaDescuento;
}

// MÉTODO CLAVE: permite cambiar el tipo de cliente sin destruir el objeto
void Cliente::cambiarTipo(char nuevoTipo) {
    // Elimina la estrategia actual
    delete estrategiaDescuento;

    // Asigna la nueva estrategia
    if (nuevoTipo == 'A') {
        estrategiaDescuento = new DescuentoA();
    } else if (nuevoTipo == 'B') {
        estrategiaDescuento = new DescuentoB();
    } else if (nuevoTipo == 'C') {
        estrategiaDescuento = new DescuentoC();
    } else {
        estrategiaDescuento = nullptr;
    }
}

// Delega el cálculo del descuento a la estrategia
double Cliente::calcularDescuento(int cantTotal, double montoTotal) const {
    if (estrategiaDescuento == nullptr) {
        return 0;
    }
    return estrategiaDescuento->calcularDescuento(cantTotal, montoTotal);
}

// Getters
int Cliente::getNro() const {
    return nro;
}

char* Cliente::getNombre() {
    return nombre;
}

char Cliente::getTipo() const {
    if (estrategiaDescuento == nullptr) {
        return '\0';  // Tipo desconocido
    }
    return estrategiaDescuento->getTipo();
}

// Setters
void Cliente::setNro(int n) {
    nro = n;
}

void Cliente::setNombre(const char* nom) {
    strcpy(nombre, nom);
}
