#ifndef GESTORA_H
#define GESTORA_H

#include "curso.h"
#include "cursocompuesto.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// ========== STRUCTS PARA ARCHIVOS BINARIOS ==========

// Archivo: cursos.dat
struct CursoArchivo {
    char codigo[50];
    char titulo[200];
    int tiempoHoras;
    char tipo;  // 'N' = Normal, 'C' = Compuesto
};

// Archivo: correlativas.dat
struct CorrelativaArchivo {
    char codigo_curso[50];
    char codigo_correlativa[50];
};

// Archivo: cursos_compuestos.dat
struct CursoCompuestoArchivo {
    char codigo_compuesto[50];
    char codigo_curso_contenido[50];
};

// ========== CLASE GESTORA ==========

class Gestora {
private:
    vector<Curso*> cursos;

    // Métodos auxiliares privados
    Curso* buscarCurso(char* codigo);

public:
    Gestora();
    ~Gestora();

    // Métodos para agregar elementos
    void agregarCurso(Curso* curso);

    // PUNTO 1: Guardar en archivos binarios
    void guardarArchivos(char* archCursos,
                         char* archCorrelativas,
                         char* archCursosCompuestos);

    // Métodos para leer archivos binarios
    void leerArchivos(char* archCursos,
                      char* archCorrelativas,
                      char* archCursosCompuestos);

    // PUNTO 2: Mostrar y guardar en archivo de texto
    void mostrarYGuardarEnTexto(char* archivoTexto);

    // PUNTO 3: Métodos con STL
    vector<Curso*> obtenerCursosConMasCorrelativas();
    int obtenerTiempoTotalCurso(char* codigoCurso);

    // Getters
    vector<Curso*> getCursos();
};

#endif // GESTORA_H
