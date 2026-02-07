#include "cursocompuesto.h"
#include <set>

CursoCompuesto::CursoCompuesto() : Curso() {
}

CursoCompuesto::CursoCompuesto(char* codigo, char* titulo, int tiempoHoras) : Curso(codigo, titulo, tiempoHoras) {
}

CursoCompuesto::~CursoCompuesto() {
    // No eliminar cursos porque son agregación
    cursos.clear();
}

vector<Curso*> CursoCompuesto::getCursos() {
    return cursos;
}

int CursoCompuesto::getCantidadCursos() {
    return cursos.size();
}

void CursoCompuesto::agregarCurso(Curso* curso) {
    cursos.push_back(curso);
}

char CursoCompuesto::getTipo() {
    return 'C'; // Compuesto
}

int CursoCompuesto::obtenerTiempoTotal() {
    int total = tiempoHoras;
    
    // Sumar tiempo de todos los cursos que contiene
    for(Curso* c : cursos) {
        total += c->obtenerTiempoTotal();
    }
    
    // También sumar tiempo de correlativas si las tiene
    for(Curso* corr : correlativas) {
        total += corr->obtenerTiempoTotal();
    }
    
    return total;
}

ostream& operator<<(ostream& os, CursoCompuesto& cursoCompuesto) {
    os << "Curso Compuesto: " << cursoCompuesto.getTitulo() << " (Codigo: " << cursoCompuesto.getCodigo() << ")" << endl;
    os << "Tiempo base: " << cursoCompuesto.getTiempoHoras() << " horas" << endl;
    
    if(cursoCompuesto.getCantidadCursos() > 0) {
        os << "Cursos contenidos:" << endl;
        vector<Curso*> cursos = cursoCompuesto.getCursos();
        for(Curso* c : cursos) {
            os << "  - " << c->getTitulo() << " (Codigo: " << c->getCodigo() << ")" << endl;
        }
    }
    
    if(cursoCompuesto.getCantidadCorrelativas() > 0) {
        os << "Correlativas:" << endl;
        vector<Curso*> corr = cursoCompuesto.getCorrelativas();
        for(Curso* c : corr) {
            os << "  - " << c->getTitulo() << " (Codigo: " << c->getCodigo() << ")" << endl;
        }
    }
    
    os << "Tiempo total (incluyendo cursos y correlativas): " << cursoCompuesto.obtenerTiempoTotal() << " horas" << endl;
    
    return os;
}
