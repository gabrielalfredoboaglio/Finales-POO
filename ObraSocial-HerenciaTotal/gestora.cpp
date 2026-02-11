#include "gestora.h"
#include <iostream>

using namespace std;

Gestora::Gestora() {}

Gestora::~Gestora() {
    for(Cliente* c : clientes) {
        delete c;
    }
}

// ========== MÉTODOS AUXILIARES ==========

Cliente* Gestora::buscarCliente(int id) {
    for(Cliente* c : clientes) {
        if(c->getId() == id) {
            return c;
        }
    }
    return nullptr;
}

void Gestora::cargarPrestacionesDesdeTexto(char* archivo, vector<string>& destino) {
    ifstream archi(archivo);

    if(!archi.is_open()) {
        cout << "Error al abrir: " << archivo << endl;
        return;
    }

    char linea[500];

    while(archi.getline(linea, 500)) {
        if(strlen(linea) > 0) {
            destino.push_back(string(linea));
        }
    }

    archi.close();
}

vector<string> Gestora::getPrestacionesPorTipo(char tipo) {
    switch(tipo) {
        case 'b': return prestacionesBasicas;
        case 'm': return prestacionesMedio;
        case 'p': return prestacionesPremium;
        default: return vector<string>();
    }
}

// ========== EJERCICIO 1: LEER ARCHIVOS ==========

void Gestora::leerArchivos(char* archClientes) {
    // 1. Cargar prestaciones desde los 3 archivos de texto
    char archivoBasico[] = "basica.txt";
    char archivoMedio[] = "medio.txt";
    char archivoPremium[] = "premium.txt";

    cargarPrestacionesDesdeTexto(archivoBasico, prestacionesBasicas);
    cargarPrestacionesDesdeTexto(archivoMedio, prestacionesMedio);
    cargarPrestacionesDesdeTexto(archivoPremium, prestacionesPremium);

    // 2. Leer clientes del archivo binario (herencia total: switch por tipo)
    ifstream archi(archClientes, ios::binary);

    if(!archi.is_open()) {
        cout << "Error al abrir: " << archClientes << endl;
        return;
    }

    ClienteArchivo caux;

    while(archi.read((char*)&caux, sizeof(ClienteArchivo))) {
        Cliente* cliente;

        switch(caux.tipo) {
            case 'b': cliente = new ClienteBasico(); break;
            case 'm': cliente = new ClienteMedio(); break;
            case 'p': cliente = new ClientePremium(); break;
            default: continue;
        }

        cliente->setId(caux.id);
        cliente->setNombre(caux.nombre);
        cliente->setCantidad(caux.cantidad);

        // Asignar prestaciones según tipo
        cliente->setPrestaciones(getPrestacionesPorTipo(caux.tipo));

        clientes.push_back(cliente);
    }

    archi.close();
}

// ========== EJERCICIO 1: VERIFICAR PRESTACIÓN ==========

bool Gestora::clienteTienePrestacion(int id, char* prestacion) {
    Cliente* cliente = buscarCliente(id);

    if(cliente == nullptr) {
        cout << "Cliente no encontrado" << endl;
        return false;
    }

    return cliente->tienePrestacion(prestacion);
}

// ========== EJERCICIO 2.1: TOP 5 QUE MÁS USARON EL SERVICIO ==========

vector<Cliente*> Gestora::obtener5MasUsaron() {
    vector<Cliente*> copia(clientes.begin(), clientes.end());

    sort(copia.begin(), copia.end(),
        [](Cliente* a, Cliente* b) {
            return a->getCantidad() > b->getCantidad();
        });

    int cant = min((int)copia.size(), 5);
    return vector<Cliente*>(copia.begin(), copia.begin() + cant);
}

// ========== EJERCICIO 2.2: TODAS LAS PRESTACIONES DE TODOS LOS PLANES ==========

vector<string> Gestora::obtenerTodasPrestaciones() {
    vector<string> todas;

    // Copiar todas las prestaciones con STL
    copy(prestacionesBasicas.begin(), prestacionesBasicas.end(), back_inserter(todas));
    copy(prestacionesMedio.begin(), prestacionesMedio.end(), back_inserter(todas));
    copy(prestacionesPremium.begin(), prestacionesPremium.end(), back_inserter(todas));

    // Eliminar duplicados con sort + unique
    sort(todas.begin(), todas.end());
    auto it = unique(todas.begin(), todas.end());
    todas.erase(it, todas.end());

    return todas;
}

// ========== EJERCICIO 2.3: CANTIDAD DE VECES POR TIPO DE PLAN ==========

map<char, int> Gestora::obtenerCantidadPorTipo() {
    map<char, int> resultado;

    for_each(clientes.begin(), clientes.end(),
        [&resultado](Cliente* c) {
            resultado[c->getTipo()] += c->getCantidad();
        });

    return resultado;
}

// ========== EJERCICIO 2.4: PRESTACIONES QUE ESTÁN EN TODOS LOS PLANES ==========

vector<string> Gestora::obtenerPrestacionesEnTodosPlanes() {
    vector<string> resultado;

    for(string& p : prestacionesBasicas) {
        bool enMedio = find(prestacionesMedio.begin(), prestacionesMedio.end(), p)
                       != prestacionesMedio.end();
        bool enPremium = find(prestacionesPremium.begin(), prestacionesPremium.end(), p)
                         != prestacionesPremium.end();

        if(enMedio && enPremium) {
            resultado.push_back(p);
        }
    }

    return resultado;
}
