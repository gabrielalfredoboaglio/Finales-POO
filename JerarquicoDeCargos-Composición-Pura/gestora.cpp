#include "Gestora.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <cstring>

Gestora::Gestora() {
}

Gestora::~Gestora() {
    // Liberar memoria de todos los empleados
    for(Empleado* e : empleados) {
        delete e;
    }
}

// ========== MÉTODOS AUXILIARES PRIVADOS ==========

Empleado* Gestora::buscarEmpleado(int numero) {
    for(Empleado* e : empleados) {
        if(e->getNumero() == numero) {
            return e;
        }
    }
    return nullptr;
}

int Gestora::contarGuiones(const string& linea) {
    int count = 0;
    for(char c : linea) {
        if(c == '-') {
            count++;
        } else {
            break;  // Dejar de contar cuando no sea guión
        }
    }
    return count;
}

void Gestora::parsearLinea(const string& linea, int& numero, string& nombre) {
    // Eliminar guiones al inicio
    size_t inicio = linea.find_first_not_of('-');
    string lineaSinGuiones = linea.substr(inicio);

    // Buscar el guión que separa número de nombre
    size_t posSeparador = lineaSinGuiones.find('-');

    if(posSeparador != string::npos) {
        // Extraer número
        string numStr = lineaSinGuiones.substr(0, posSeparador);
        numero = stoi(numStr);

        // Extraer nombre
        nombre = lineaSinGuiones.substr(posSeparador + 1);
    }
}

// ========== PUNTO 2: LEER ARCHIVO DE TEXTO ==========

void Gestora::leerArchivoTexto(const char* nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if(!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    vector<Empleado*> jerarquia;  // Para mantener la jerarquía por niveles

    while(getline(archivo, linea)) {
        if(linea.empty()) continue;

        // Contar nivel jerárquico (cantidad de guiones)
        int nivel = contarGuiones(linea);

        // Parsear número y nombre
        int numero;
        string nombre;
        parsearLinea(linea, numero, nombre);

        // Crear empleado
        Empleado* emp = new Empleado(numero, nombre.c_str());
        empleados.push_back(emp);

        // Establecer jerarquía
        if(nivel == 0) {
            // Es el jefe principal, no tiene responsable
            jerarquia.clear();
            jerarquia.push_back(emp);
        } else {
            // Ajustar el tamaño del vector de jerarquía al nivel actual
            if(nivel < jerarquia.size()) {
                jerarquia.resize(nivel);
            }

            // El jefe es el del nivel anterior
            Empleado* jefe = jerarquia[nivel - 1];
            jefe->agregarEmpleadoACargo(emp);

            // Agregar este empleado al nivel correspondiente
            if(nivel < jerarquia.size()) {
                jerarquia[nivel] = emp;
            } else {
                jerarquia.push_back(emp);
            }
        }
    }

    archivo.close();
}

// ========== PUNTO 3: OBTENER RESPONSABLE ==========

Empleado* Gestora::obtenerResponsable(int numeroEmpleado) {
    Empleado* emp = buscarEmpleado(numeroEmpleado);

    if(emp == nullptr) {
        return nullptr;  // Empleado no encontrado
    }

    return emp->getResponsable();  // Retorna nullptr si no tiene responsable
}

// ========== PUNTO 4: GUARDAR ARCHIVO BINARIO ==========

void Gestora::guardarArchivoBinario(const char* nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::binary);

    if(!archivo.is_open()) {
        cout << "Error al crear el archivo: " << nombreArchivo << endl;
        return;
    }

    EmpleadoArchivo eaux;

    for(Empleado* e : empleados) {
        eaux.numero = e->getNumero();
        strcpy(eaux.nombre, e->getNombre());
        eaux.cantidad_a_cargo = e->getCantidadACargo();

        archivo.write((char*)&eaux, sizeof(EmpleadoArchivo));
    }

    archivo.close();
}

// ========== PUNTO 5.1: EMPLEADO CON MÁS SUBORDINADOS ==========

Empleado* Gestora::obtenerEmpleadoMasSubordinados() {
    if(empleados.empty()) {
        return nullptr;
    }

    // Usar max_element con lambda
    auto maxIt = max_element(empleados.begin(), empleados.end(),
                             [](Empleado* a, Empleado* b) {
                                 return a->getCantidadACargo() < b->getCantidadACargo();
                             });

    return *maxIt;
}

// ========== PUNTO 5.2: NÚMEROS REPETIDOS ==========

vector<int> Gestora::obtenerNumerosRepetidos() {
    map<int, int> contadorNumeros;

    // Contar ocurrencias de cada número
    for(Empleado* e : empleados) {
        contadorNumeros[e->getNumero()]++;
    }

    // Recolectar números que aparecen más de una vez
    vector<int> numerosRepetidos;

    for(const auto& par : contadorNumeros) {
        if(par.second > 1) {
            numerosRepetidos.push_back(par.first);
        }
    }

    return numerosRepetidos;
}

// ========== PUNTO LIBRE: GUARDAR JERARQUÍA EN BINARIOS ==========

void Gestora::guardarJerarquiaBinaria(const char* nombreArchivoEmpleados,
                                      const char* nombreArchivoJerarquia) {
    // Archivo 1: Datos de empleados
    ofstream archiEmpleados(nombreArchivoEmpleados, ios::binary);

    if(!archiEmpleados.is_open()) {
        cout << "Error al crear el archivo: " << nombreArchivoEmpleados << endl;
        return;
    }

    EmpleadoArchivo eaux;

    for(Empleado* e : empleados) {
        eaux.numero = e->getNumero();
        strcpy(eaux.nombre, e->getNombre());
        eaux.cantidad_a_cargo = e->getCantidadACargo();

        archiEmpleados.write((char*)&eaux, sizeof(EmpleadoArchivo));
    }

    archiEmpleados.close();

    // Archivo 2: Relaciones jerárquicas
    ofstream archiJerarquia(nombreArchivoJerarquia, ios::binary);

    if(!archiJerarquia.is_open()) {
        cout << "Error al crear el archivo: " << nombreArchivoJerarquia << endl;
        return;
    }

    JerarquiaArchivo jaux;

    // Recorrer todos los empleados y guardar sus relaciones
    for(Empleado* e : empleados) {
        const vector<Empleado*>& subordinados = e->getEmpleadosACargo();

        for(Empleado* subordinado : subordinados) {
            jaux.numero_jefe = e->getNumero();
            jaux.numero_subordinado = subordinado->getNumero();

            archiJerarquia.write((char*)&jaux, sizeof(JerarquiaArchivo));
        }
    }

    archiJerarquia.close();
}

