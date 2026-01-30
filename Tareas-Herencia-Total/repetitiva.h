#ifndef REPETITIVA_H
#define REPETITIVA_H

#include "tarea.h"
#include "gestora.h"

class Repetitiva : public Tarea {
private:
    Gestora* g;

public:
    Repetitiva(Gestora* g);
    char getTipo();
    void ejecutar();
    void sumarUnDia(const char* fechaActual, char* fechaNueva);
};

#endif
