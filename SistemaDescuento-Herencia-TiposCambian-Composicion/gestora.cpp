#include "gestora.h"
#include <fstream>
#include <algorithm>
#include <numeric>
#include <map>
#include <iostream>
#include <cstring>

using namespace std;

Gestora::Gestora() {
}

Gestora::~Gestora() {
    for(Cliente* c : clientes) {
        delete c;
    }
}

// ========== MÉTODOS AUXILIARES ==========

Cliente* Gestora::buscarCliente(int nro) {
    for(Cliente* c : clientes) {
        if(c->getNro() == nro) {
            return c;
        }
    }
    return nullptr;
}

int Gestora::calcularCantidadTotal(int nro_cliente) {
    int total = 0;
    for(Venta& v : ventas) {
        if(v.getNroCliente() == nro_cliente) {
            total += v.getCantidad();
        }
    }
    return total;
}

double Gestora::calcularMontoTotal(int nro_cliente) {
    double total = 0;
    for(Venta& v : ventas) {
        if(v.getNroCliente() == nro_cliente) {
            total += v.getMontoTotal();
        }
    }
    return total;
}

vector<Cliente*> Gestora::getClientes() {
    return clientes;
}

vector<Venta> Gestora::getVentas() {
    return ventas;
}

// ========== EJERCICIO 3: Leer archivos binarios ==========

void Gestora::leerArchivos(char* archClientes, char* archVentas) {

    // ========== LEER CLIENTES ==========
    ifstream archiC(archClientes, ios::binary);

    if(archiC.is_open()) {
        ClienteArchivo caux;

        while(archiC.read((char*)&caux, sizeof(ClienteArchivo))) {
            Cliente* cliente = new Cliente(caux.nro, caux.nombre, caux.tipo);
            clientes.push_back(cliente);
        }

        archiC.close();
    }

    // ========== LEER VENTAS ==========
    ifstream archiV(archVentas, ios::binary);

    if(archiV.is_open()) {
        VentaArchivo vaux;

        while(archiV.read((char*)&vaux, sizeof(VentaArchivo))) {
            Venta venta(vaux.nro_cliente, vaux.cantidad, vaux.montoTotal);
            ventas.push_back(venta);
        }

        archiV.close();
    }
}

// ========== GUARDAR ARCHIVOS BINARIOS ==========

void Gestora::guardarArchivos(char* archClientes, char* archVentas) {

    // ========== ARCHIVO 1: CLIENTES ==========
    ofstream archiC(archClientes, ios::binary);

    if(!archiC.is_open()) {
        cout << "Error al crear " << archClientes << endl;
        return;
    }

    ClienteArchivo caux;

    for(Cliente* cli : clientes) {
        caux.nro = cli->getNro();
        strcpy(caux.nombre, cli->getNombre());
        caux.tipo = cli->getTipo();

        archiC.write((char*)&caux, sizeof(ClienteArchivo));
    }

    archiC.close();

    // ========== ARCHIVO 2: VENTAS ==========
    ofstream archiV(archVentas, ios::binary);

    if(!archiV.is_open()) {
        cout << "Error al crear " << archVentas << endl;
        return;
    }

    VentaArchivo vaux;

    for(Venta& v : ventas) {
        vaux.nro_cliente = v.getNroCliente();
        vaux.cantidad = v.getCantidad();
        vaux.montoTotal = v.getMontoTotal();

        archiV.write((char*)&vaux, sizeof(VentaArchivo));
    }

    archiV.close();
}

// ========== EJERCICIO 2: Calcular descuento para una nueva venta ==========

double Gestora::calcularDescuentoNuevaVenta(int nro_cliente, int cantidad, double monto) {
    Cliente* cli = buscarCliente(nro_cliente);

    if(cli == nullptr) {
        return 0;
    }

    int cantidadTotal = calcularCantidadTotal(nro_cliente) + cantidad;
    double montoTotal = calcularMontoTotal(nro_cliente) + monto;

    return cli->calcularDescuento(cantidadTotal, montoTotal);
}

// ========== agregar para punto libre ==========

void Gestora::cambiarTipoCliente(int nro_cliente, char nuevoTipo) {
    Cliente* cli = buscarCliente(nro_cliente);

    if(cli != nullptr) {
        cli->cambiarTipo(nuevoTipo);
    }
}

// ========== EJERCICIO 4: Métodos con STL ==========

// 4a. Obtener el o los clientes que compraron la mayor cantidad de items
vector<Cliente*> Gestora::obtenerClientesConMasItems() {
    if(clientes.empty() || ventas.empty()) {
        return vector<Cliente*>();
    }

    // Calcular cantidad total por cliente usando map
    map<int, int> cantidadPorCliente;

    for(Venta& v : ventas) {
        cantidadPorCliente[v.getNroCliente()] += v.getCantidad();
    }

    // Encontrar el máximo usando max_element
    auto maxIt = max_element(cantidadPorCliente.begin(), cantidadPorCliente.end(),
                             [](pair<int, int> a, pair<int, int> b) {
                                 return a.second < b.second;
                             });

    int maxCantidad = maxIt->second;

    // Recolectar todos los clientes que tienen ese máximo
    vector<Cliente*> resultado;

    for(auto& par : cantidadPorCliente) {
        if(par.second == maxCantidad) {
            Cliente* cli = buscarCliente(par.first);
            if(cli != nullptr) {
                resultado.push_back(cli);
            }
        }
    }

    return resultado;
}

// 4b. Obtener el monto total de todas las ventas
double Gestora::obtenerMontoTotalVentas() {
    double total = 0;

    for_each(ventas.begin(), ventas.end(),
             [&total](Venta& v) {
                 total += v.getMontoTotal();
             });

    return total;
}

// 4c. Obtener los nombres de clientes que se repiten
vector<char*> Gestora::obtenerNombresRepetidos() {
    vector<char*> resultado;

    map<string, int> contadorNombres;

    // Contar cuántas veces aparece cada nombre
    for_each(clientes.begin(), clientes.end(),
             [&contadorNombres](Cliente* c) {
                 contadorNombres[string(c->getNombre())]++;
             });

    // Recolectar los que se repiten
    for(Cliente* c : clientes) {
        if(contadorNombres[string(c->getNombre())] > 1) {
            // Verificar que no esté ya en el resultado
            bool encontrado = false;
            for(char* nom : resultado) {
                if(strcmp(nom, c->getNombre()) == 0) {
                    encontrado = true;
                    break;
                }
            }
            if(!encontrado) {
                resultado.push_back(c->getNombre());
            }
        }
    }

    return resultado;
}
