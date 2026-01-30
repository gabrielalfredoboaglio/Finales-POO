#include "ingrediente.h"
#include <cstring>

Ingrediente::Ingrediente() {
    codigo = 0;
    strcpy(nombre, "");
}

Ingrediente::Ingrediente(int codigo, char* nombre) {
    this->codigo = codigo;
    strcpy(this->nombre, nombre);
}

Ingrediente::~Ingrediente() {
}

int Ingrediente::getCodigo() {
    return codigo;
}

char* Ingrediente::getNombre() {
    return nombre;
}

void Ingrediente::setCodigo(int codigo) {
    this->codigo = codigo;
}

void Ingrediente::setNombre(char* nombre) {
    strcpy(this->nombre, nombre);
}
