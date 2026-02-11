#ifndef PRODUCTO_H
#define PRODUCTO_H

#include "ingrediente.h"
#include <vector>
#include <iostream>
using namespace std;

class Producto {
protected:
    int codigo;
    char nombre[200];
    vector<Ingrediente*> ingredientes;

public:
    Producto();
    Producto(int codigo, char* nombre);
    virtual ~Producto();

    int getCodigo();
    char* getNombre();
    vector<Ingrediente*> getIngredientes();
    int getCantidadIngredientes();
    void setCodigo(int codigo);
    void setNombre(char* nombre);
    void agregarIngrediente(Ingrediente* ingrediente);
    virtual char getTipo();

    friend ostream& operator<<(ostream& os, Producto& producto); // ========== agregar para punto libre ==========
};

#endif // PRODUCTO_H
