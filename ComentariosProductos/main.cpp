#include "gestora.h"

using namespace std;

int main()
{
    Gestora gestora;

    // Ejercicio 2: Leer archivo de texto
    char archComentarios[] = "comentarios.txt";
    gestora.leerArchivoTexto(archComentarios);

    // ========== agregar para punto libre ==========
    // Leer respuestas múltiples (un comentario responde a varios)
    char archRespuestas[] = "respuestas.dat";
    gestora.leerRespuestas(archRespuestas);

    // Ejercicio 3a: Productos con mayor puntaje
    gestora.obtenerProductosMayorPuntaje();

    // Ejercicio 3b: Productos con más comentarios negativos
    gestora.obtenerProductosMasComentariosNegativos();

    // Ejercicio 3c: Productos con mayor cantidad total de comentarios
    gestora.obtenerProductosMasComentarios();

    // Ejercicio 4: Guardar en archivo binario
    char archResultados[] = "resultados.dat";
    gestora.guardarArchivoBinario(archResultados);

    // ========== agregar para punto libre ==========
    // Guardar respuestas múltiples en archivo binario
    gestora.guardarRespuestas(archRespuestas);

    return 0;
}
