#include "gestora.h"
#include <fstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstring>

Gestora::Gestora() {
}

Gestora::~Gestora() {
    for(Paquete* p : paquetes) {
        delete p;
    }
    for(ConjuntoPaquetes* c : conjuntos) {
        delete c;
    }
}

// ========== MÉTODOS AUXILIARES ==========

Paquete* Gestora::buscarPaquete(char* codigo) {
    for(Paquete* p : paquetes) {
        if(strcmp(p->getCodigo(), codigo) == 0) {
            return p;
        }
    }
    return nullptr;
}

ConjuntoPaquetes* Gestora::buscarConjunto(char* codigo) {
    for(ConjuntoPaquetes* c : conjuntos) {
        if(strcmp(c->getCodigo(), codigo) == 0) {
            return c;
        }
    }
    return nullptr;
}

void Gestora::agregarPaquete(Paquete* paquete) {
    paquetes.push_back(paquete);
}

void Gestora::agregarConjunto(ConjuntoPaquetes* conjunto) {
    conjuntos.push_back(conjunto);
}

vector<Paquete*> Gestora::getPaquetes() {
    return paquetes;
}

vector<ConjuntoPaquetes*> Gestora::getConjuntos() {
    return conjuntos;
}

// ========== GUARDAR ARCHIVOS BINARIOS ==========

void Gestora::guardarArchivos(char* archPaquetes, char* archDependencias) {

    // ========== ARCHIVO 1: PAQUETES ==========
    ofstream archiP(archPaquetes, ios::binary);

    if(!archiP.is_open()) {
        cout << "Error al crear " << archPaquetes << endl;
        return;
    }

    PaqueteArchivo paux;

    for(Paquete* paq : paquetes) {
        strcpy(paux.codigo, paq->getCodigo());
        strcpy(paux.nombre, paq->getNombre());
        paux.version = paq->getVersion();

        archiP.write((char*)&paux, sizeof(PaqueteArchivo));
    }

    archiP.close();

    // ========== ARCHIVO 2: DEPENDENCIAS ==========
    ofstream archiD(archDependencias, ios::binary);

    if(!archiD.is_open()) {
        cout << "Error al crear " << archDependencias << endl;
        return;
    }

    DependenciaArchivo daux;

    for(Paquete* paq : paquetes) {
        vector<Paquete*> deps = paq->getDependencias();

        for(Paquete* dep : deps) {
            strcpy(daux.codigoPaquete, paq->getCodigo());
            strcpy(daux.codigoPaqueteDependencia, dep->getCodigo());

            archiD.write((char*)&daux, sizeof(DependenciaArchivo));
        }
    }

    archiD.close();
}

// ========== LEER ARCHIVOS BINARIOS ==========

void Gestora::leerArchivos(char* archPaquetes, char* archDependencias) {

    // ========== LEER PAQUETES ==========
    ifstream archiP(archPaquetes, ios::binary);

    if(archiP.is_open()) {
        PaqueteArchivo paux;

        while(archiP.read((char*)&paux, sizeof(PaqueteArchivo))) {
            Paquete* paq = new Paquete(paux.codigo, paux.nombre, paux.version);
            paquetes.push_back(paq);
        }

        archiP.close();
    }

    // ========== LEER DEPENDENCIAS ==========
    ifstream archiD(archDependencias, ios::binary);

    if(archiD.is_open()) {
        DependenciaArchivo daux;

        while(archiD.read((char*)&daux, sizeof(DependenciaArchivo))) {
            Paquete* paquete = buscarPaquete(daux.codigoPaquete);
            Paquete* dependencia = buscarPaquete(daux.codigoPaqueteDependencia);

            if(paquete != nullptr && dependencia != nullptr) {
                paquete->agregarDependencia(dependencia);
            }
        }

        archiD.close();
    }
}

// ========== EJERCICIO 1: Obtener todas las dependencias de un paquete ==========

vector<Paquete*> Gestora::obtenerTodasDependencias(char* codigoPaquete) {
    Paquete* paquete = buscarPaquete(codigoPaquete);

    if(paquete == nullptr) {
        return vector<Paquete*>();
    }

    return paquete->obtenerTodasDependencias();
}

// ========== EJERCICIO 2: Escribir árbol de dependencias en archivo de texto ==========

void Gestora::escribirArbolDependencias(char* codigoPaquete) {
    Paquete* paquete = buscarPaquete(codigoPaquete);

    if(paquete == nullptr) {
        return;
    }

    // El archivo se llama igual que el código del paquete
    char nombreArchivo[110];
    strcpy(nombreArchivo, codigoPaquete);
    strcat(nombreArchivo, ".txt");

    ofstream archivo(nombreArchivo);

    if(!archivo.is_open()) {
        return;
    }

    archivo << *paquete;

    archivo.close();
}

// ========== EJERCICIO 3: Métodos con STL ==========

// Los 5 paquetes con mayor cantidad de dependencias no transitivas
vector<Paquete*> Gestora::obtenerTop5PaquetesConMasDependencias() {
    if(paquetes.empty()) {
        return vector<Paquete*>();
    }

    // Copiar el vector para ordenar
    vector<Paquete*> copia(paquetes.begin(), paquetes.end());

    // Ordenar de mayor a menor cantidad de dependencias directas
    sort(copia.begin(), copia.end(),
         [](Paquete* a, Paquete* b) {
             return a->getCantidadDependencias() > b->getCantidadDependencias();
         });

    // Tomar los primeros 5 (o menos si no hay suficientes)
    int cantidad = min((int)copia.size(), 5);
    vector<Paquete*> resultado(copia.begin(), copia.begin() + cantidad);

    return resultado;
}

// Todos los paquetes que no tienen dependencias
vector<Paquete*> Gestora::obtenerPaquetesSinDependencias() {
    vector<Paquete*> resultado;

    copy_if(paquetes.begin(), paquetes.end(), back_inserter(resultado),
            [](Paquete* p) {
                return p->getCantidadDependencias() == 0;
            });

    return resultado;
}

// ========== LIBRE: Conjuntos de paquetes ==========

void Gestora::guardarArchivosConjuntos(char* archConjuntos, char* archConjuntosPaquetes) {

    // ========== ARCHIVO: CONJUNTOS ==========
    ofstream archiC(archConjuntos, ios::binary);

    if(!archiC.is_open()) {
        cout << "Error al crear " << archConjuntos << endl;
        return;
    }

    ConjuntoArchivo caux;

    for(ConjuntoPaquetes* conj : conjuntos) {
        strcpy(caux.codigo, conj->getCodigo());
        strcpy(caux.nombre, conj->getNombre());
        caux.version = conj->getVersion();

        archiC.write((char*)&caux, sizeof(ConjuntoArchivo));
    }

    archiC.close();

    // ========== ARCHIVO: CONJUNTOS_PAQUETES ==========
    ofstream archiCP(archConjuntosPaquetes, ios::binary);

    if(!archiCP.is_open()) {
        cout << "Error al crear " << archConjuntosPaquetes << endl;
        return;
    }

    ConjuntoPaqueteArchivo cpaux;

    for(ConjuntoPaquetes* conj : conjuntos) {
        vector<Paquete*> paqs = conj->getPaquetes();

        for(Paquete* paq : paqs) {
            strcpy(cpaux.codigoConjunto, conj->getCodigo());
            strcpy(cpaux.codigoPaquete, paq->getCodigo());

            archiCP.write((char*)&cpaux, sizeof(ConjuntoPaqueteArchivo));
        }
    }

    archiCP.close();
}

void Gestora::leerArchivosConjuntos(char* archConjuntos, char* archConjuntosPaquetes) {

    // ========== LEER CONJUNTOS ==========
    ifstream archiC(archConjuntos, ios::binary);

    if(archiC.is_open()) {
        ConjuntoArchivo caux;

        while(archiC.read((char*)&caux, sizeof(ConjuntoArchivo))) {
            ConjuntoPaquetes* conj = new ConjuntoPaquetes(caux.codigo, caux.nombre, caux.version);
            conjuntos.push_back(conj);
        }

        archiC.close();
    }

    // ========== LEER CONJUNTOS_PAQUETES ==========
    ifstream archiCP(archConjuntosPaquetes, ios::binary);

    if(archiCP.is_open()) {
        ConjuntoPaqueteArchivo cpaux;

        while(archiCP.read((char*)&cpaux, sizeof(ConjuntoPaqueteArchivo))) {
            ConjuntoPaquetes* conjunto = buscarConjunto(cpaux.codigoConjunto);
            Paquete* paquete = buscarPaquete(cpaux.codigoPaquete);

            if(conjunto != nullptr && paquete != nullptr) {
                conjunto->agregarPaquete(paquete);
            }
        }

        archiCP.close();
    }
}

// Libre: Instalar todos los paquetes de un conjunto
vector<Paquete*> Gestora::instalarConjunto(char* codigoConjunto) {
    ConjuntoPaquetes* conjunto = buscarConjunto(codigoConjunto);

    if(conjunto == nullptr) {
        return vector<Paquete*>();
    }

    return conjunto->instalarDependientes();
}
