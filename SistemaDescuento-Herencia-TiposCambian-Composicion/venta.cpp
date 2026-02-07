#include "venta.h"

using namespace std;

Venta::Venta() {
    nro_cliente = 0;
    cantidad = 0;
    montoTotal = 0.0;
}

Venta::Venta(int nro_cli, int cant, double monto) {
    nro_cliente = nro_cli;
    cantidad = cant;
    montoTotal = monto;
}

int Venta::getNroCliente() {
    return nro_cliente;
}

int Venta::getCantidad() {
    return cantidad;
}

double Venta::getMontoTotal() {
    return montoTotal;
}

void Venta::setNroCliente(int nro) {
    nro_cliente = nro;
}

void Venta::setCantidad(int cant) {
    cantidad = cant;
}

void Venta::setMontoTotal(double monto) {
    montoTotal = monto;
}
