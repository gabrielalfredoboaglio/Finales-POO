#include "gestora.h"
#include <fstream>
#include <algorithm>
#include <map>
#include <iostream>
#include <cstring>

Gestora::Gestora() {
}

Gestora::~Gestora() {
    // Liberar memoria de cursos
    for(Curso* c : cursos) {
        delete c;
    }
}

// ========== MÉTODOS AUXILIARES ==========

Curso* Gestora::buscarCurso(char* codigo) {
    for(Curso* c : cursos) {
        if(strcmp(c->getCodigo(), codigo) == 0) {
            return c;
        }
    }
    return nullptr;
}

void Gestora::agregarCurso(Curso* curso) {
    cursos.push_back(curso);
}

vector<Curso*> Gestora::getCursos() {
    return cursos;
}

// ========== PUNTO 1: GUARDAR ARCHIVOS BINARIOS ==========

void Gestora::guardarArchivos(char* archCursos,
                              char* archCorrelativas,
                              char* archCursosCompuestos) {

    // ========== ARCHIVO 1: CURSOS ==========
    ofstream archiC(archCursos, ios::binary);

    if(!archiC.is_open()) {
        cout << "Error al crear " << archCursos << endl;
        return;
    }

    CursoArchivo caux;

    for(Curso* curso : cursos) {
        strcpy(caux.codigo, curso->getCodigo());
        strcpy(caux.titulo, curso->getTitulo());
        caux.tiempoHoras = curso->getTiempoHoras();
        caux.tipo = curso->getTipo();

        archiC.write((char*)&caux, sizeof(CursoArchivo));
    }

    archiC.close();

    // ========== ARCHIVO 2: CORRELATIVAS ==========
    ofstream archiCorr(archCorrelativas, ios::binary);

    if(!archiCorr.is_open()) {
        cout << "Error al crear " << archCorrelativas << endl;
        return;
    }

    CorrelativaArchivo corraux;

    for(Curso* curso : cursos) {
        vector<Curso*> corr = curso->getCorrelativas();

        for(Curso* c : corr) {
            strcpy(corraux.codigo_curso, curso->getCodigo());
            strcpy(corraux.codigo_correlativa, c->getCodigo());

            archiCorr.write((char*)&corraux, sizeof(CorrelativaArchivo));
        }
    }

    archiCorr.close();

    // ========== LIBRE: ARCHIVO 3: CURSOS_COMPUESTOS ==========
    ofstream archiCC(archCursosCompuestos, ios::binary);

    if(!archiCC.is_open()) {
        cout << "Error al crear " << archCursosCompuestos << endl;
        return;
    }

    CursoCompuestoArchivo ccaux;

    for(Curso* curso : cursos) {
        if(curso->getTipo() == 'C') {
            CursoCompuesto* cc = dynamic_cast<CursoCompuesto*>(curso);
            vector<Curso*> cursosContenidos = cc->getCursos();

            for(Curso* cContenido : cursosContenidos) {
                strcpy(ccaux.codigo_compuesto, curso->getCodigo());
                strcpy(ccaux.codigo_curso_contenido, cContenido->getCodigo());

                archiCC.write((char*)&ccaux, sizeof(CursoCompuestoArchivo));
            }
        }
    }

    archiCC.close();
}

// ========== LEER ARCHIVOS BINARIOS ==========

void Gestora::leerArchivos(char* archCursos,
                           char* archCorrelativas,
                           char* archCursosCompuestos) {

    // ========== LEER CURSOS ==========
    ifstream archiC(archCursos, ios::binary);

    if(archiC.is_open()) {
        CursoArchivo caux;

        while(archiC.read((char*)&caux, sizeof(CursoArchivo))) {
            Curso* curso;

            // ========== LIBRE: Crear CursoCompuesto si tipo 'C' ==========
            if(caux.tipo == 'C') {
                curso = new CursoCompuesto(caux.codigo, caux.titulo, caux.tiempoHoras);
            } else {
                curso = new Curso(caux.codigo, caux.titulo, caux.tiempoHoras);
            }

            cursos.push_back(curso);
        }

        archiC.close();
    }

    // ========== LEER CORRELATIVAS ==========
    ifstream archiCorr(archCorrelativas, ios::binary);

    if(archiCorr.is_open()) {
        CorrelativaArchivo corraux;

        while(archiCorr.read((char*)&corraux, sizeof(CorrelativaArchivo))) {
            Curso* curso = buscarCurso(corraux.codigo_curso);
            Curso* correlativa = buscarCurso(corraux.codigo_correlativa);

            if(curso != nullptr && correlativa != nullptr) {
                curso->agregarCorrelativa(correlativa);
            }
        }

        archiCorr.close();
    }

    // ========== LIBRE: LEER CURSOS_COMPUESTOS ==========
    ifstream archiCC(archCursosCompuestos, ios::binary);

    if(archiCC.is_open()) {
        CursoCompuestoArchivo ccaux;

        while(archiCC.read((char*)&ccaux, sizeof(CursoCompuestoArchivo))) {
            Curso* cursoCompuesto = buscarCurso(ccaux.codigo_compuesto);
            Curso* cursoContenido = buscarCurso(ccaux.codigo_curso_contenido);

            if(cursoCompuesto != nullptr && cursoContenido != nullptr && cursoCompuesto->getTipo() == 'C') {
                CursoCompuesto* cc = dynamic_cast<CursoCompuesto*>(cursoCompuesto);
                cc->agregarCurso(cursoContenido);
            }
        }

        archiCC.close();
    }
}

// ========== PUNTO 2: MOSTRAR Y GUARDAR EN TEXTO ==========

void Gestora::mostrarYGuardarEnTexto(char* archivoTexto) {
    ofstream archivo(archivoTexto);

    if(!archivo.is_open()) {
        cout << "Error al crear " << archivoTexto << endl;
        return;
    }

    for(Curso* curso : cursos) {
        // Libre: Si es compuesto, usar operator<< de CursoCompuesto
        if(curso->getTipo() == 'C') {
            CursoCompuesto* cc = dynamic_cast<CursoCompuesto*>(curso);
            archivo << *cc;
        } else {
            archivo << *curso;
        }
        archivo << endl;
    }

    archivo.close();
}

// ========== PUNTO 3: MÉTODOS CON STL ==========

vector<Curso*> Gestora::obtenerCursosConMasCorrelativas() {
    if(cursos.empty()) {
        return vector<Curso*>();
    }

    // Encontrar el máximo
    auto maxIt = max_element(cursos.begin(), cursos.end(),
                             [](Curso* a, Curso* b) {
                                 return a->getCantidadCorrelativas() < b->getCantidadCorrelativas();
                             });

    int maxCorrelativas = (*maxIt)->getCantidadCorrelativas();

    // Recolectar todos los que tienen ese máximo
    vector<Curso*> resultado;

    for(Curso* c : cursos) {
        if(c->getCantidadCorrelativas() == maxCorrelativas) {
            resultado.push_back(c);
        }
    }

    return resultado;
}

int Gestora::obtenerTiempoTotalCurso(char* codigoCurso) {
    Curso* curso = buscarCurso(codigoCurso);

    if(curso == nullptr) {
        return -1; // Curso no encontrado
    }

    return curso->obtenerTiempoTotal();
}
