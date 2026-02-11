#ifndef CURSO_H
#define CURSO_H

#include <vector>
#include <iostream>
using namespace std;

class Curso {
protected:
    char codigo[50];
    char titulo[200];
    int tiempoHoras;
    vector<Curso*> correlativas;

public:
    Curso();
    Curso(char* codigo, char* titulo, int tiempoHoras);
    virtual ~Curso();

    char* getCodigo();
    char* getTitulo();
    int getTiempoHoras();
    vector<Curso*> getCorrelativas();
    int getCantidadCorrelativas();
    
    void setCodigo(char* codigo);
    void setTitulo(char* titulo);
    void setTiempoHoras(int tiempoHoras);
    void agregarCorrelativa(Curso* curso);
    
    // Libre: virtual para saber si es compuesto
    virtual char getTipo();
    int obtenerTiempoTotal();
    
    friend ostream& operator<<(ostream& os, Curso& curso);
};

#endif // CURSO_H
