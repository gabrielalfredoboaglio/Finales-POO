#include "paquete.h"
#include <cstring>

Paquete::Paquete() {
    strcpy(codigo, "");
    strcpy(nombre, "");
    version = 0;
}

Paquete::Paquete(char* codigo, char* nombre, int version) {
    strcpy(this->codigo, codigo);
    strcpy(this->nombre, nombre);
    this->version = version;
}

Paquete::~Paquete() {
    // No eliminar dependencias porque son agregación (compartidas)
    dependencias.clear();
}

char* Paquete::getCodigo() {
    return codigo;
}

char* Paquete::getNombre() {
    return nombre;
}

int Paquete::getVersion() {
    return version;
}

vector<Paquete*> Paquete::getDependencias() {
    return dependencias;
}

int Paquete::getCantidadDependencias() {
    return dependencias.size();
}

void Paquete::setCodigo(char* codigo) {
    strcpy(this->codigo, codigo);
}

void Paquete::setNombre(char* nombre) {
    strcpy(this->nombre, nombre);
}

void Paquete::setVersion(int version) {
    this->version = version;
}

void Paquete::agregarDependencia(Paquete* paquete) {
    dependencias.push_back(paquete);
}

// ========== EJERCICIO 1: Obtener todas las dependencias (incluyendo transitivas) ==========

vector<Paquete*> Paquete::obtenerTodasDependencias() {
    vector<Paquete*> resultado;
    vector<Paquete*> visitados;
    obtenerTodasDependenciasRec(resultado, visitados);
    return resultado;
}

void Paquete::obtenerTodasDependenciasRec(vector<Paquete*>& resultado, vector<Paquete*>& visitados) {
    for(Paquete* dep : dependencias) {
        // Verificar si ya fue visitado para evitar ciclos
        bool encontrado = false;
        for(Paquete* v : visitados) {
            if(strcmp(v->getCodigo(), dep->getCodigo()) == 0) {
                encontrado = true;
                break;
            }
        }

        if(!encontrado) {
            visitados.push_back(dep);
            resultado.push_back(dep);
            dep->obtenerTodasDependenciasRec(resultado, visitados);
        }
    }
}

// ========== EJERCICIO 2: Escribir árbol de dependencias ==========

void Paquete::escribirArbol(ostream& os, int nivel) {
    // Escribir indentación según nivel
    for(int i = 0; i < nivel; i++) {
        os << "    ";
    }
    os << nombre << endl;

    // Escribir dependencias recursivamente
    for(Paquete* dep : dependencias) {
        dep->escribirArbol(os, nivel + 1);
    }
}

// Ejercicio 2: Operador << para Paquete
ostream& operator<<(ostream& os, Paquete& paquete) {
    paquete.escribirArbol(os, 0);
    return os;
}
