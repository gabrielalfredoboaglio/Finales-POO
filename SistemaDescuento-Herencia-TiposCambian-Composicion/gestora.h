#ifndef GESTORA_H
#define GESTORA_H

#include "cliente.h"
#include "venta.h"
#include <vector>
#include <fstream>
using namespace std;

// ========== STRUCTS PARA ARCHIVOS BINARIOS ==========

// Archivo: cliente.dat
struct ClienteArchivo {
    int nro;
    char nombre[200];
    char tipo;
};

// Archivo: ventaAnual.dat
struct VentaArchivo {
    int nro_cliente;
    int cantidad;
    double montoTotal;
};

// ========== CLASE GESTORA ==========

class Gestora {
private:
    vector<Cliente*> clientes;
    vector<Venta> ventas;

    // Métodos auxiliares privados
    Cliente* buscarCliente(int nro);
    int calcularCantidadTotal(int nro_cliente);
    double calcularMontoTotal(int nro_cliente);

public:
    Gestora();
    ~Gestora();

    // Ejercicio 3: Leer archivos binarios
    void leerArchivos(char* archClientes, char* archVentas);

    // Guardar archivos binarios
    void guardarArchivos(char* archClientes, char* archVentas);

    // Ejercicio 2: Calcular descuento para una nueva venta
    double calcularDescuentoNuevaVenta(int nro_cliente, int cantidad, double monto);

    // Cambiar tipo de cliente
    void cambiarTipoCliente(int nro_cliente, char nuevoTipo);

    // Ejercicio 4: Métodos con STL
    vector<Cliente*> obtenerClientesConMasItems();
    double obtenerMontoTotalVentas();
    vector<char*> obtenerNombresRepetidos();

    // Getters
    vector<Cliente*> getClientes();
    vector<Venta> getVentas();
};

#endif
