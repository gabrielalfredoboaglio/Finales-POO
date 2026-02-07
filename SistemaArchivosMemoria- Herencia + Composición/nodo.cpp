#include "nodo.h"

Nodo::Nodo() {
    path = "";
    nombre = "";
}

Nodo::Nodo(string path, string nombre) {
    this->path = path;
    this->nombre = nombre;
}

Nodo::~Nodo() {
}

string Nodo::getPath() {
    return path;
}

string Nodo::getNombre() {
    return nombre;
}

void Nodo::setPath(string path) {
    this->path = path;
}

void Nodo::setNombre(string nombre) {
    this->nombre = nombre;
}

ostream& operator<<(ostream& os, Nodo& nodo) {
    os << nodo.getNombre() << " (" << nodo.getPath() << ")";
    return os;
}
