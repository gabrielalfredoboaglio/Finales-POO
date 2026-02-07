#include "cliente.h"
#include "descuentoa.h"
#include "descuentob.h"
#include "descuentoc.h"
#include <cstring>

using namespace std;

Cliente::Cliente() {
    nro = 0;
    strcpy(nombre, "");
    estrategiaDescuento = nullptr;
}

// Ejercicio 1: Constructor con estrategia según tipo
Cliente::Cliente(int n, char* nom, char tipo) {
    nro = n;
    strcpy(nombre, nom);

    if(tipo == 'A') {
        estrategiaDescuento = new DescuentoA();
    } else if(tipo == 'B') {
        estrategiaDescuento = new DescuentoB();
    } else if(tipo == 'C') {
        estrategiaDescuento = new DescuentoC();
    } else {
        estrategiaDescuento = nullptr;
    }
}

Cliente::~Cliente() {
    delete estrategiaDescuento;
}

// Permite cambiar el tipo de cliente sin destruir el objeto
void Cliente::cambiarTipo(char nuevoTipo) {
    delete estrategiaDescuento;

    if(nuevoTipo == 'A') {
        estrategiaDescuento = new DescuentoA();
    } else if(nuevoTipo == 'B') {
        estrategiaDescuento = new DescuentoB();
    } else if(nuevoTipo == 'C') {
        estrategiaDescuento = new DescuentoC();
    } else {
        estrategiaDescuento = nullptr;
    }
}

// Ejercicio 2: Delega el cálculo del descuento a la estrategia
double Cliente::calcularDescuento(int cantTotal, double montoTotal) {
    if(estrategiaDescuento == nullptr) {
        return 0;
    }
    return estrategiaDescuento->calcularDescuento(cantTotal, montoTotal);
}

int Cliente::getNro() {
    return nro;
}

char* Cliente::getNombre() {
    return nombre;
}

char Cliente::getTipo() {
    if(estrategiaDescuento == nullptr) {
        return '\0';
    }
    return estrategiaDescuento->getTipo();
}

void Cliente::setNro(int n) {
    nro = n;
}

void Cliente::setNombre(char* nom) {
    strcpy(nombre, nom);
}
