#include "carpeta.h"

Carpeta::Carpeta() : Nodo() {
}

Carpeta::Carpeta(string path, string nombre) : Nodo(path, nombre) {
}

Carpeta::~Carpeta() {
    // No eliminar elementos porque pueden ser compartidos
    elementos.clear();
}

vector<Nodo*> Carpeta::getElementos() {
    return elementos;
}

int Carpeta::getCantidadElementos() {
    return elementos.size();
}

void Carpeta::agregarElemento(Nodo* elemento) {
    elementos.push_back(elemento);
}

Nodo* Carpeta::buscarElemento(string nombre) {
    for(Nodo* elem : elementos) {
        if(elem->getNombre() == nombre) {
            return elem;
        }
    }
    return nullptr;
}

bool Carpeta::existeElemento(string nombre) {
    return buscarElemento(nombre) != nullptr;
}

char Carpeta::getTipo() {
    return 'C'; // Carpeta
}

int Carpeta::obtenerPeso() {
    int total = 0;
    
    for(Nodo* elem : elementos) {
        total += elem->obtenerPeso();
    }
    
    return total;
}

void Carpeta::ordenarPorNombre() {
    sort(elementos.begin(), elementos.end(),
         [](Nodo* a, Nodo* b) {
             return a->getNombre() < b->getNombre();
         });
}
