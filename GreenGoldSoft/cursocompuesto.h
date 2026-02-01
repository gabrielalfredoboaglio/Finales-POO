#ifndef CURSCOMPUESTO_H
#define CURSCOMPUESTO_H

#include "curso.h"
#include <vector>
#include <iostream>
using namespace std;

class CursoCompuesto : public Curso {
private:
    vector<Curso*> cursos;

public:
    CursoCompuesto();
    CursoCompuesto(char* codigo, char* titulo, int tiempoHoras);
    ~CursoCompuesto();

    vector<Curso*> getCursos();
    int getCantidadCursos();
    void agregarCurso(Curso* curso);
    char getTipo();
    int obtenerTiempoTotal();
    
    friend ostream& operator<<(ostream& os, CursoCompuesto& cursoCompuesto);
};

#endif // CURSCOMPUESTO_H
