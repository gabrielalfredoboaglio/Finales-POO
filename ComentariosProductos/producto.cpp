#include "producto.h"
#include <cstring>

using namespace std;

Producto::Producto() {
    strcpy(nombre, "");
}

Producto::Producto(char* nom) {
    strcpy(nombre, nom);
}

Producto::~Producto() {
    for(Comentario* c : comentarios) {
        delete c;
    }
}

char* Producto::getNombre() {
    return nombre;
}

vector<Comentario*> Producto::getComentarios() {
    return comentarios;
}

int Producto::getCantidadComentarios() {
    return comentarios.size();
}

void Producto::setNombre(char* nom) {
    strcpy(nombre, nom);
}

void Producto::agregarComentario(Comentario* comentario) {
    comentarios.push_back(comentario);
}

double Producto::calcularPuntajePromedio() {
    if(comentarios.empty()) return 0;

    double suma = 0;
    for(Comentario* c : comentarios) {
        suma += c->calcularPuntajePromedio();
    }

    return suma / comentarios.size();
}

int Producto::contarComentariosNegativos() {
    int total = 0;
    for(Comentario* c : comentarios) {
        total += c->contarComentariosNegativos();
    }
    return total;
}

int Producto::contarTotalComentarios() {
    int total = 0;
    for(Comentario* c : comentarios) {
        total += c->contarComentariosTotales();
    }
    return total;
}
