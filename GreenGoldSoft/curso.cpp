#include "curso.h"
#include <cstring>

Curso::Curso() {
    strcpy(codigo, "");
    strcpy(titulo, "");
    tiempoHoras = 0;
}

Curso::Curso(char* codigo, char* titulo, int tiempoHoras) {
    strcpy(this->codigo, codigo);
    strcpy(this->titulo, titulo);
    this->tiempoHoras = tiempoHoras;
}

Curso::~Curso() {
    // No eliminar correlativas porque son agregación
    correlativas.clear();
}

char* Curso::getCodigo() {
    return codigo;
}

char* Curso::getTitulo() {
    return titulo;
}

int Curso::getTiempoHoras() {
    return tiempoHoras;
}

vector<Curso*> Curso::getCorrelativas() {
    return correlativas;
}

int Curso::getCantidadCorrelativas() {
    return correlativas.size();
}

void Curso::setCodigo(char* codigo) {
    strcpy(this->codigo, codigo);
}

void Curso::setTitulo(char* titulo) {
    strcpy(this->titulo, titulo);
}

void Curso::setTiempoHoras(int tiempoHoras) {
    this->tiempoHoras = tiempoHoras;
}

void Curso::agregarCorrelativa(Curso* curso) {
    correlativas.push_back(curso);
}

char Curso::getTipo() {
    return 'N'; // Normal
}

int Curso::obtenerTiempoTotal() {
    int total = tiempoHoras;
    
    for(Curso* corr : correlativas) {
        total += corr->obtenerTiempoTotal();
    }
    
    return total;
}

ostream& operator<<(ostream& os, Curso& curso) {
    os << "Curso: " << curso.getTitulo() << " (Codigo: " << curso.getCodigo() << ")" << endl;
    os << "Tiempo: " << curso.getTiempoHoras() << " horas" << endl;
    
    if(curso.getCantidadCorrelativas() > 0) {
        os << "Correlativas:" << endl;
        vector<Curso*> corr = curso.getCorrelativas();
        for(Curso* c : corr) {
            os << "  - " << c->getTitulo() << " (Codigo: " << c->getCodigo() << ")" << endl;
        }
    } else {
        os << "Sin correlativas" << endl;
    }
    
    return os;
}
