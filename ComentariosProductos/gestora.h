#ifndef GESTORA_H
#define GESTORA_H

#include "producto.h"
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// ========== STRUCTS PARA ARCHIVOS BINARIOS ==========

// Archivo: resultados.dat
struct ProductoArchivo {
    char nombre[200];
    double puntajePromedio;
    int comentariosNegativos;
    int totalComentarios;
};

// ========== agregar para punto libre ==========
// Archivo: respuestas.dat (un comentario responde a varios comentarios)
struct RespuestaArchivo {
    int idComentarioHijo;
    int idComentarioPadre;
};

// ========== CLASE GESTORA ==========

class Gestora {
private:
    vector<Producto*> productos;

    Producto* buscarProducto(char* nombre);
    // ========== agregar para punto libre ==========
    Comentario* buscarComentario(int id);

public:
    Gestora();
    ~Gestora();

    // Ejercicio 2: Leer archivo de texto
    void leerArchivoTexto(char* archivo);

    // Ejercicio 3: Métodos con STL
    vector<Producto*> obtenerProductosMayorPuntaje();
    vector<Producto*> obtenerProductosMasComentariosNegativos();
    vector<Producto*> obtenerProductosMasComentarios();

    // Ejercicio 4: Guardar en archivo binario
    void guardarArchivoBinario(char* archivo);

    // ========== agregar para punto libre ==========
    // Leer/guardar respuestas múltiples desde archivo binario
    void leerRespuestas(char* archivo);
    void guardarRespuestas(char* archivo);

    // Getters
    vector<Producto*> getProductos();
};

#endif // GESTORA_H
