#include "Gestora.h"
#include <fstream>

using namespace std;

Gestora::Gestora() {}

Gestora::~Gestora() {
    for (Cliente* c : clientes) {
        delete c;
    }
}

void Gestora::leerArchivos() {
    // ========== LEER CLIENTES ==========
    ifstream archiClientes("cliente.dat", ios::binary);
    ClienteArchivo str;

    if (!archiClientes.is_open()) return;

    while (archiClientes.read((char*)&str, sizeof(ClienteArchivo))) {
        // SIMPLIFICADO: Ya no necesitamos switch, solo creamos un Cliente
        Cliente* cliente = new Cliente(str.nro, str.nombre, str.tipo);
        clientes.push_back(cliente);
    }

    archiClientes.close();

    // ========== LEER VENTAS ==========
    ifstream archiVentas("ventaAnual.dat", ios::binary);
    VentaArchivo vstr;

    if (!archiVentas.is_open()) return;

    while (archiVentas.read((char*)&vstr, sizeof(VentaArchivo))) {
        Venta v;
        v.setNroCliente(vstr.nro_cliente);
        v.setCantidad(vstr.cantidad);
        v.setMontoTotal(vstr.montoTotal);
        ventas.push_back(v);
    }

    archiVentas.close();
}

// ========== PUNTO 2 ==========
double Gestora::calcularDescuentoNuevaVenta(int nro_cliente, int cantidad, double monto) {
    Cliente* cli = buscarCliente(nro_cliente);

    if (cli == nullptr) {
        return 0;
    }

    int cantidadTotal = calcularCantidadTotal(nro_cliente) + cantidad;
    double montoTotal = calcularMontoTotal(nro_cliente) + monto;

    return cli->calcularDescuento(cantidadTotal, montoTotal);
}

// ========== NUEVO: CAMBIAR TIPO DE CLIENTE ==========
bool Gestora::cambiarTipoCliente(int nro_cliente, char nuevoTipo) {
    Cliente* cli = buscarCliente(nro_cliente);

    if (cli == nullptr) {
        return false;
    }

    // Usa el método cambiarTipo del cliente
    cli->cambiarTipo(nuevoTipo);
    return true;
}

// ========== MÉTODOS AUXILIARES ==========
Cliente* Gestora::buscarCliente(int nro) {
    for (Cliente* c : clientes) {
        if (c->getNro() == nro) {
            return c;
        }
    }
    return nullptr;
}

int Gestora::calcularCantidadTotal(int nro_cliente) {
    int total = 0;
    for (Venta& v : ventas) {
        if (v.getNroCliente() == nro_cliente) {
            total += v.getCantidad();
        }
    }
    return total;
}

double Gestora::calcularMontoTotal(int nro_cliente) {
    double total = 0;
    for (Venta& v : ventas) {
        if (v.getNroCliente() == nro_cliente) {
            total += v.getMontoTotal();
        }
    }
    return total;
}
