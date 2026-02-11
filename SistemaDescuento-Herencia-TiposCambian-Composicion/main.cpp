#include "gestora.h"

using namespace std;

int main()
{
    Gestora gestora;

    // Ejercicio 3: Leer archivos binarios
    gestora.leerArchivos("cliente.dat", "ventaAnual.dat");

    // Guardar archivos binarios
    gestora.guardarArchivos("cliente.dat", "ventaAnual.dat");

    // Ejercicio 2: Calcular descuento para una nueva venta
    gestora.calcularDescuentoNuevaVenta(1, 50, 5000.0);

    // ========== agregar para punto libre ==========
    gestora.cambiarTipoCliente(1, 'C');

    // Ejercicio 4a: Clientes que compraron la mayor cantidad de items
    gestora.obtenerClientesConMasItems();

    // Ejercicio 4b: Monto total de todas las ventas
    gestora.obtenerMontoTotalVentas();

    // Ejercicio 4c: Nombres de clientes que se repiten
    gestora.obtenerNombresRepetidos();

    return 0;
}
