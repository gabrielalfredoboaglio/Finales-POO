#ifndef GESTORA_H
#define GESTORA_H

#include "encuesta.h"
#include "pregunta.h"
#include "respuesta.h"
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

// ========== STRUCTS PARA ARCHIVOS BINARIOS ==========

// Archivo: encuestas.dat
struct EncuestaArchivo {
    char titulo[200];
    int cantidadPreguntas;
};

// Archivo: preguntas.dat
struct PreguntaArchivo {
    char texto[500];
    int idEncuesta;
    int cantidadRespuestas;
};

// Archivo: respuestas.dat
struct RespuestaArchivo {
    char texto[200];
    int idPregunta;
    int cantidadPreguntasEncadenadas;
};

// Archivo: preguntas_encadenadas.dat
struct PreguntaEncadenadaArchivo {
    int idRespuesta;
    int idPreguntaEncadenada;
};

class Gestora {
private:
    vector<Encuesta*> encuestas;

    // Métodos auxiliares privados
    Encuesta* buscarEncuesta(int indice);
    Pregunta* buscarPregunta(int idEncuesta, int idPregunta);
    Respuesta* buscarRespuesta(int idPregunta, int idRespuesta);

public:
    Gestora();
    ~Gestora();

    // Métodos para agregar elementos
    void agregarEncuesta(Encuesta* encuesta);

    // PUNTO 1: Guardar en archivos binarios
    void guardarArchivos(char* archEncuestas,
                         char* archPreguntas,
                         char* archRespuestas,
                         char* archPreguntasEncadenadas);

    // Métodos para leer archivos binarios
    void leerArchivos(char* archEncuestas,
                      char* archPreguntas,
                      char* archRespuestas,
                      char* archPreguntasEncadenadas);

    // PUNTO 2: Procedimiento para responder encuesta
    void responderEncuesta(int indiceEncuesta);
    void responderPreguntas(vector<Pregunta*> preguntas);

    // PUNTO 3: Métodos con STL
    vector<Pregunta*> obtenerPreguntasConMasRespuestas();
    vector<Respuesta*> obtenerRespuestasConPreguntasEncadenadas();

    // LIBRE: Guardar en archivo de texto con operador <<
    void guardarEnTexto(char* archivoTexto);

    // Getters
    vector<Encuesta*> getEncuestas();
};

#endif // GESTORA_H
