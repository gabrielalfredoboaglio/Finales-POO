#include "repetitiva.h"
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>

Repetitiva::Repetitiva(Gestora* g) {
    this->g = g;
}

char Repetitiva::getTipo() {
    return 'R';
}

void Repetitiva::ejecutar()
{
    std::cout << "Tarea repetitiva: " << descripcion << std::endl;

    Repetitiva* nueva = new Repetitiva(g);

    TareaArchivo str = this->getStr();

    char fechaNueva[9];
    sumarUnDia(str.fecha, fechaNueva);
    strcpy(str.fecha, fechaNueva);

    nueva->setStr(str);

    g->add(nueva);
}


void Repetitiva::sumarUnDia(const char* actual, char* nueva) {
    std::string s(actual);

    int anio = std::stoi(s.substr(0,4));
    int mes  = std::stoi(s.substr(4,2));
    int dia  = std::stoi(s.substr(6,2));

    dia++;

    sprintf(nueva, "%04d%02d%02d", anio, mes, dia);
}
