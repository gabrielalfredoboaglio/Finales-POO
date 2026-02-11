#ifndef CLIENTE_H
#define CLIENTE_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

// Ejercicio 1: Clase abstracta Cliente (herencia total)

class Cliente {
protected:
    int id;
    char nombre[200];
    int cantidad;
    vector<string> prestaciones;

public:
    Cliente();
    virtual ~Cliente();
    virtual char getTipo() = 0;

    bool tienePrestacion(char* prestacion);

    int getId();
    char* getNombre();
    int getCantidad();
    vector<string> getPrestaciones();

    void setId(int i);
    void setNombre(char* nom);
    void setCantidad(int c);
    void setPrestaciones(vector<string> p);
};

#endif
