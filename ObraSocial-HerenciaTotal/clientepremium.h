#ifndef CLIENTEPREMIUM_H
#define CLIENTEPREMIUM_H

#include "cliente.h"

using namespace std;

// Ejercicio 1: Plan Premium

class ClientePremium : public Cliente {
public:
    ClientePremium();
    char getTipo();
};

#endif
