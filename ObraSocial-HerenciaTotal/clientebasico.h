#ifndef CLIENTEBASICO_H
#define CLIENTEBASICO_H

#include "cliente.h"

using namespace std;

// Ejercicio 1: Plan Básico

class ClienteBasico : public Cliente {
public:
    ClienteBasico();
    char getTipo();
};

#endif
