#ifndef COMENTARIO_H
#define COMENTARIO_H

#include <vector>
#include <iostream>
using namespace std;

// ========== EJERCICIO 1: Clase Comentario (estructura jerárquica) ==========

class Comentario {
private:
    char texto[500];
    int puntaje;
    vector<Comentario*> comentariosHijos;

public:
    Comentario();
    Comentario(char* txt, int punt);
    ~Comentario();

    char* getTexto();
    int getPuntaje();
    vector<Comentario*> getComentariosHijos();
    int getCantidadComentariosHijos();

    void setTexto(char* txt);
    void setPuntaje(int punt);
    void agregarComentarioHijo(Comentario* comentario);

    double calcularPuntajePromedio();
    int contarComentariosTotales();
    int contarComentariosNegativos();
    void obtenerTodosComentarios(vector<Comentario*>& resultado);
};

#endif // COMENTARIO_H
