#ifndef GESTORA_H
#define GESTORA_H

#include "clientebasico.h"
#include "clientemedio.h"
#include "clientepremium.h"
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

struct ClienteArchivo {
    int id;
    char nombre[200];
    char tipo;
    int cantidad;
};

class Gestora {
private:
    vector<Cliente*> clientes;
    vector<string> prestacionesBasicas;
    vector<string> prestacionesMedio;
    vector<string> prestacionesPremium;

    Cliente* buscarCliente(int id);
    void cargarPrestacionesDesdeTexto(char* archivo, vector<string>& destino);
    vector<string> getPrestacionesPorTipo(char tipo);

public:
    Gestora();
    ~Gestora();

    // Ejercicio 1: Leer archivos
    void leerArchivos(char* archClientes);

    // Ejercicio 1: Verificar prestación
    bool clienteTienePrestacion(int id, char* prestacion);

    // Ejercicio 2: STL
    vector<Cliente*> obtener5MasUsaron();
    vector<string> obtenerTodasPrestaciones();
    map<char, int> obtenerCantidadPorTipo();
    vector<string> obtenerPrestacionesEnTodosPlanes();
};

#endif
