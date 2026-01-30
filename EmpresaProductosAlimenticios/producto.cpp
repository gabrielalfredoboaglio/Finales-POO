#include "producto.h"
#include <cstring>
#include <iostream>
#include <set>

Producto::Producto() {
    codigo = 0;
    strcpy(nombre, "");
}

Producto::Producto(int codigo, char* nombre) {
    this->codigo = codigo;
    strcpy(this->nombre, nombre);
}

Producto::~Producto() {
    for(Ingrediente* ing : ingredientes) {
        delete ing;
    }
}

int Producto::getCodigo() {
    return codigo;
}

char* Producto::getNombre() {
    return nombre;
}

vector<Ingrediente*> Producto::getIngredientes() {
    return ingredientes;
}

int Producto::getCantidadIngredientes() {
    return ingredientes.size();
}

void Producto::setCodigo(int codigo) {
    this->codigo = codigo;
}

void Producto::setNombre(char* nombre) {
    strcpy(this->nombre, nombre);
}

void Producto::agregarIngrediente(Ingrediente* ingrediente) {
    ingredientes.push_back(ingrediente);
}

char Producto::getTipo() {
    return 'N'; // Normal
}

// Operador << para Producto
ostream& operator<<(ostream& os, Producto& producto) {
    os << "Producto: " << producto.getNombre() << " (Codigo: " << producto.getCodigo() << ")" << endl;
    os << "Ingredientes:" << endl;
    
    vector<Ingrediente*> ings = producto.getIngredientes();
    for(Ingrediente* ing : ings) {
        os << "  - " << ing->getNombre() << " (Codigo: " << ing->getCodigo() << ")" << endl;
    }
    
    return os;
}
