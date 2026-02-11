#ifndef GESTORA_H
#define GESTORA_H

#include "producto.h"
#include "productocompuesto.h"
#include "ingrediente.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// ========== STRUCTS PARA ARCHIVOS BINARIOS ==========

// Archivo: productos.dat
struct ProductoArchivo {
    int codigo;
    char nombre[200];
    char tipo;  // 'N' = Normal, 'C' = Compuesto
};

// Archivo: ingredientes.dat
struct IngredienteArchivo {
    int codigo;
    char nombre[200];
};

// Archivo: productos_ingredientes.dat
struct ProductoIngredienteArchivo {
    int codigo_producto;
    int codigo_ingrediente;
};

// Archivo: productos_compuestos.dat
struct ProductoCompuestoArchivo {
    int codigo_producto_compuesto;
    int codigo_producto_contenido;
};

// ========== CLASE GESTORA ==========

class Gestora {
private:
    vector<Producto*> productos;
    vector<Ingrediente*> ingredientes;

    // Métodos auxiliares privados
    Producto* buscarProducto(int codigo);
    Ingrediente* buscarIngrediente(int codigo);

public:
    Gestora();
    ~Gestora();

    // Métodos para agregar elementos
    void agregarProducto(Producto* producto);
    void agregarIngrediente(Ingrediente* ingrediente);

    // PUNTO 1: Guardar en archivos binarios
    void guardarArchivos(char* archProductos,
                         char* archIngredientes,
                         char* archProductosIngredientes,
                         char* archProductosCompuestos);

    // Métodos para leer archivos binarios
    void leerArchivos(char* archProductos,
                      char* archIngredientes,
                      char* archProductosIngredientes,
                      char* archProductosCompuestos);

    // PUNTO 3: Métodos con STL
    Ingrediente* obtenerIngredienteMasUtilizado();
    Producto* obtenerProductoConMasIngredientes();

    // ========== agregar para punto libre ==========
    void guardarEnTexto(char* archivoTexto);

    // Getters
    vector<Producto*> getProductos();
    vector<Ingrediente*> getIngredientes();
};

#endif // GESTORA_H
