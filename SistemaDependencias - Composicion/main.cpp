#include "gestora.h"
#include "vectorordenado.h"

using namespace std;

int main()
{
    Gestora gestora;

    // Leer archivos binarios
    gestora.leerArchivos("paquetes.dat", "dependencias.dat");

    // Guardar archivos binarios
    gestora.guardarArchivos("paquetes.dat", "dependencias.dat");

    // Ejercicio 1: Obtener todas las dependencias de un paquete (incluyendo transitivas)
    char codigoPaquete[] = "scala";
    gestora.obtenerTodasDependencias(codigoPaquete);

    // Ejercicio 2: Escribir árbol de dependencias en archivo de texto
    gestora.escribirArbolDependencias(codigoPaquete);

    // Ejercicio 3: STL - Top 5 paquetes con más dependencias no transitivas
    gestora.obtenerTop5PaquetesConMasDependencias();

    // Ejercicio 3: STL - Paquetes sin dependencias
    gestora.obtenerPaquetesSinDependencias();

    // Ejercicio 4: VectorOrdenado template
    VectorOrdenado<int> vectorInt;
    vectorInt.agregar(5);
    vectorInt.agregar(2);
    vectorInt.agregar(8);
    vectorInt.agregar(1);
    vectorInt.eliminar(0);
    vectorInt.imprimir();

    // ========== agregar para punto libre ==========
    gestora.leerArchivosConjuntos("conjuntos.dat", "conjuntos_paquetes.dat");
    gestora.guardarArchivosConjuntos("conjuntos.dat", "conjuntos_paquetes.dat");
    char codigoConjunto[] = "conjunto1";
    gestora.instalarConjunto(codigoConjunto);

    return 0;
}
