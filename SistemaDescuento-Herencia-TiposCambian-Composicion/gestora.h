#ifndef GESTORA_H
#define GESTORA_H

#include <vector>
#include "Cliente.h"
#include "Venta.h"

using namespace std;

// ========== STRUCTS PARA ARCHIVOS ==========
struct ClienteArchivo {
    int nro;
    char nombre[200];
    char tipo;
};

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

    // Punto 2: Calcular descuento para una nueva venta
    double calcularDescuentoNuevaVenta(int nro_cliente, int cantidad, double monto);

    // Punto 3: Leer archivos
    void leerArchivos();

    // NUEVO: Método para cambiar el tipo de un cliente
    bool cambiarTipoCliente(int nro_cliente, char nuevoTipo);
};

#endif
