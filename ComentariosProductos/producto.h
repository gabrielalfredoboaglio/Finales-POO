#ifndef PRODUCTO_H
#define PRODUCTO_H

#include "comentario.h"
#include <vector>
using namespace std;

// ========== EJERCICIO 1: Clase Producto ==========

class Producto {
private:
    char nombre[200];
    vector<Comentario*> comentarios;

public:
    Producto();
    Producto(char* nom);
    ~Producto();

    char* getNombre();
    vector<Comentario*> getComentarios();
    int getCantidadComentarios();

    void setNombre(char* nom);
    void agregarComentario(Comentario* comentario);

    double calcularPuntajePromedio();
    int contarComentariosNegativos();
    int contarTotalComentarios();
};

#endif // PRODUCTO_H
