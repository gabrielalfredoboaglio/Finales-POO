#include "respuesta.h"
#include "pregunta.h"
#include <iostream>
#include <cstring>

Respuesta::Respuesta() {
    strcpy(texto, "");
}

Respuesta::Respuesta(char* texto) {
    strcpy(this->texto, texto);
}

Respuesta::~Respuesta() {
    // Eliminar preguntas encadenadas (composición)
    for(Pregunta* p : preguntasEncadenadas) {
        delete p;
    }
}

char* Respuesta::getTexto() {
    return texto;
}

vector<Pregunta*> Respuesta::getPreguntasEncadenadas() {
    return preguntasEncadenadas;
}

int Respuesta::getCantidadPreguntasEncadenadas() {
    return preguntasEncadenadas.size();
}

void Respuesta::setTexto(char* texto) {
    strcpy(this->texto, texto);
}

void Respuesta::agregarPreguntaEncadenada(Pregunta* pregunta) {
    preguntasEncadenadas.push_back(pregunta);
}

bool Respuesta::tienePreguntasEncadenadas() {
    return !preguntasEncadenadas.empty();
}

ostream& operator<<(ostream& os, Respuesta& respuesta) {
    os << "  - " << respuesta.getTexto();
    if(respuesta.tienePreguntasEncadenadas()) {
        os << " (tiene preguntas encadenadas)";
    }
    os << endl;
    
    // Mostrar preguntas encadenadas
    for(Pregunta* p : respuesta.getPreguntasEncadenadas()) {
        os << "    -> " << *p;
    }
    
    return os;
}
