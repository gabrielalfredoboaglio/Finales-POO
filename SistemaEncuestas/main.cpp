#include "gestora.h"

using namespace std;

int main()
{
    Gestora gestora;

    gestora.leerArchivos("encuestas.dat",
                         "preguntas.dat",
                         "respuestas.dat",
                         "preguntas_encadenadas.dat");

    gestora.guardarArchivos("encuestas.dat",
                             "preguntas.dat",
                             "respuestas.dat",
                             "preguntas_encadenadas.dat");

    gestora.responderEncuesta(0);

    gestora.obtenerPreguntasConMasRespuestas();

    gestora.obtenerRespuestasConPreguntasEncadenadas();

    gestora.guardarEnTexto("encuestas.txt");

    return 0;
}
