#ifndef PREGUNTA_H
#define PREGUNTA_H

// ========== PUNTO 1: DISEÑO DEL SISTEMA ==========

#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

class Respuesta;

class Pregunta {
private:
    char texto[500];
    vector<Respuesta*> respuestas;

public:
    Pregunta();
    Pregunta(char* texto);
    ~Pregunta();

    char* getTexto();
    vector<Respuesta*> getRespuestas();
    int getCantidadRespuestas();
    void setTexto(char* texto);
    void agregarRespuesta(Respuesta* respuesta);
    
    friend ostream& operator<<(ostream& os, Pregunta& pregunta);
};

#endif // PREGUNTA_H
