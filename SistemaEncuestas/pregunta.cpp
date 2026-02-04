#include "pregunta.h"
#include "respuesta.h"
#include <iostream>
#include <cstring>

Pregunta::Pregunta() {
    strcpy(texto, "");
}

Pregunta::Pregunta(char* texto) {
    strcpy(this->texto, texto);
}

Pregunta::~Pregunta() {
    // Eliminar respuestas (composición)
    for(Respuesta* r : respuestas) {
        delete r;
    }
}

char* Pregunta::getTexto() {
    return texto;
}

vector<Respuesta*> Pregunta::getRespuestas() {
    return respuestas;
}

int Pregunta::getCantidadRespuestas() {
    return respuestas.size();
}

void Pregunta::setTexto(char* texto) {
    strcpy(this->texto, texto);
}

void Pregunta::agregarRespuesta(Respuesta* respuesta) {
    respuestas.push_back(respuesta);
}

ostream& operator<<(ostream& os, Pregunta& pregunta) {
    os << "Pregunta: " << pregunta.getTexto() << endl;
    os << "Respuestas:" << endl;
    
    for(Respuesta* r : pregunta.getRespuestas()) {
        os << *r;
    }
    
    return os;
}
