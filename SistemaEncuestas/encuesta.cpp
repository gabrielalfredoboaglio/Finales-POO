#include "encuesta.h"
#include "pregunta.h"
#include <iostream>
#include <cstring>

Encuesta::Encuesta() {
    strcpy(titulo, "");
}

Encuesta::Encuesta(char* titulo) {
    strcpy(this->titulo, titulo);
}

Encuesta::~Encuesta() {
    // Eliminar preguntas (composición)
    for(Pregunta* p : preguntas) {
        delete p;
    }
}

char* Encuesta::getTitulo() {
    return titulo;
}

vector<Pregunta*> Encuesta::getPreguntas() {
    return preguntas;
}

int Encuesta::getCantidadPreguntas() {
    return preguntas.size();
}

void Encuesta::setTitulo(char* titulo) {
    strcpy(this->titulo, titulo);
}

void Encuesta::agregarPregunta(Pregunta* pregunta) {
    preguntas.push_back(pregunta);
}

ostream& operator<<(ostream& os, Encuesta& encuesta) {
    os << "ENCUESTA: " << encuesta.getTitulo() << endl;
    os << "========================================" << endl;
    
    for(Pregunta* p : encuesta.getPreguntas()) {
        os << *p << endl;
    }
    
    return os;
}
