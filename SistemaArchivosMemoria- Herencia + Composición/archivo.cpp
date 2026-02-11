#include "archivo.h"

Archivo::Archivo() : Nodo() {
    peso = 0;  // Libre: inicializar peso
}

// ========== LIBRE: Constructor con peso ==========
Archivo::Archivo(string path, string nombre, int peso) : Nodo(path, nombre) {
    this->peso = peso;
}

Archivo::~Archivo() {
}

// ========== LIBRE: Getters/Setters de peso ==========
int Archivo::getPeso() {
    return peso;
}

void Archivo::setPeso(int peso) {
    this->peso = peso;
}

char Archivo::getTipo() {
    return 'A'; // Archivo
}

// ========== LIBRE: PESO DE ARCHIVOS ==========
int Archivo::obtenerPeso() {
    return peso;
}
