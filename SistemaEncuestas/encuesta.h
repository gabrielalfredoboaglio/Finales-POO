#ifndef ENCUESTA_H
#define ENCUESTA_H

// ========== PUNTO 1: DISEÑO DEL SISTEMA ==========

#include "pregunta.h"
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

class Pregunta;

class Encuesta {
private:
    char titulo[200];
    vector<Pregunta*> preguntas;

public:
    Encuesta();
    Encuesta(char* titulo);
    ~Encuesta();

    char* getTitulo();
    vector<Pregunta*> getPreguntas();
    int getCantidadPreguntas();
    void setTitulo(char* titulo);
    void agregarPregunta(Pregunta* pregunta);
    
    friend ostream& operator<<(ostream& os, Encuesta& encuesta);
};

#endif // ENCUESTA_H
