#include "gestora.h"

using namespace std;

int main()
{
    Gestora gestora;

    // Cargar datos desde archivos binarios
    gestora.leerArchivos("cursos.dat",
                         "correlativas.dat",
                         "cursos_compuestos.dat");   // Libre: tercer archivo

    // Guardar datos en archivos binarios
    gestora.guardarArchivos("cursos.dat",
                            "correlativas.dat",
                            "cursos_compuestos.dat");   // Libre: tercer archivo

    // Mostrar y guardar en archivo de texto
    gestora.mostrarYGuardarEnTexto("cursos.txt");

    // Obtener cursos con más correlativas
    gestora.obtenerCursosConMasCorrelativas();

    // Obtener tiempo total de un curso
    char codigo[] = "CURSO001";
    gestora.obtenerTiempoTotalCurso(codigo);

    return 0;
}
