#ifndef COMENTARIO_H
#define COMENTARIO_H

#include <vector>
#include <iostream>
using namespace std;

// ========== EJERCICIO 1: Clase Comentario (estructura jerárquica) ==========

class Comentario {
private:
    // ========== agregar para punto libre ==========
    int id;
    char texto[500];
    int puntaje;
    vector<Comentario*> comentariosHijos;
    // ========== agregar para punto libre ==========
    vector<Comentario*> comentariosPadres;  // Puede responder a varios comentarios

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

    // ========== agregar para punto libre ==========
    int getId();
    void setId(int i);
    void agregarPadre(Comentario* padre);
    vector<Comentario*> getPadres();
    int getCantidadPadres();

    double calcularPuntajePromedio();
    int contarComentariosTotales();
    int contarComentariosNegativos();
    void obtenerTodosComentarios(vector<Comentario*>& resultado);
};

#endif // COMENTARIO_H
