#include "gestora.h"

using namespace std;

int main()
{
    Gestora gestora;

    // Cargar datos desde archivos binarios
    gestora.leerArchivos("productos.dat",
                         "ingredientes.dat",
                         "productos_ingredientes.dat",
                         "productos_compuestos.dat");

    // Guardar datos en archivos binarios
    gestora.guardarArchivos("productos.dat",
                            "ingredientes.dat",
                            "productos_ingredientes.dat",
                            "productos_compuestos.dat");

    // Obtener ingrediente más utilizado
    gestora.obtenerIngredienteMasUtilizado();

    // Obtener producto con más ingredientes
    gestora.obtenerProductoConMasIngredientes();

    // ========== agregar para punto libre ==========
    gestora.guardarEnTexto("productos.txt");

    return 0;
}
