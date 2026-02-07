#include "gestora.h"

using namespace std;

int main()
{
    Gestora gestora;

    // Ejercicio 2: Leer archivo de texto
    gestora.leerArchivoTexto("comentarios.txt");

    // Ejercicio 3a: Productos con mayor puntaje
    gestora.obtenerProductosMayorPuntaje();

    // Ejercicio 3b: Productos con más comentarios negativos
    gestora.obtenerProductosMasComentariosNegativos();

    // Ejercicio 3c: Productos con mayor cantidad total de comentarios
    gestora.obtenerProductosMasComentarios();

    // Ejercicio 4: Guardar en archivo binario
    gestora.guardarArchivoBinario("resultados.dat");

    return 0;
}
