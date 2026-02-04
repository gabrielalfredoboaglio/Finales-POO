#ifndef RESPUESTA_H
#define RESPUESTA_H

// ========== PUNTO 1: DISEÑO DEL SISTEMA ==========

#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

class Pregunta;

class Respuesta {
private:
    char texto[200];
    vector<Pregunta*> preguntasEncadenadas;

public:
    Respuesta();
    Respuesta(char* texto);
    ~Respuesta();

    char* getTexto();
    vector<Pregunta*> getPreguntasEncadenadas();
    int getCantidadPreguntasEncadenadas();
    void setTexto(char* texto);
    void agregarPreguntaEncadenada(Pregunta* pregunta);
    bool tienePreguntasEncadenadas();
    
    friend ostream& operator<<(ostream& os, Respuesta& respuesta);
};

#endif // RESPUESTA_H
