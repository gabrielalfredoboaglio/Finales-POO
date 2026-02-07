#include "gestora.h"
#include <iostream>
#include <algorithm>

Gestora::Gestora() {
    root = new Carpeta("/", "root");
    carpetaActual = root;
}

Gestora::~Gestora() {
    delete root;
}

// ========== MÉTODOS AUXILIARES ==========

string Gestora::construirPath(string nombre) {
    string pathActual = carpetaActual->getPath();
    
    if(pathActual == "/") {
        return "/" + nombre;
    } else {
        return pathActual + "/" + nombre;
    }
}

bool Gestora::validarPathUnico(string path) {
    // Buscar en toda la estructura si el path ya existe
    // Por simplicidad, validamos solo en la carpeta actual
    // En un sistema real, habría que buscar recursivamente
    return true; // Simplificado para este ejercicio
}

Carpeta* Gestora::buscarCarpetaPorPath(string path) {
    // Búsqueda simplificada - en un sistema real sería recursiva
    if(path == "/") {
        return root;
    }
    
    // Buscar desde root
    vector<string> partes;
    stringstream ss(path);
    string parte;
    
    while(getline(ss, parte, '/')) {
        if(!parte.empty()) {
            partes.push_back(parte);
        }
    }
    
    Carpeta* actual = root;
    
    for(string p : partes) {
        Nodo* encontrado = actual->buscarElemento(p);
        
        if(encontrado == nullptr || encontrado->getTipo() != 'C') {
            return nullptr;
        }
        
        actual = dynamic_cast<Carpeta*>(encontrado);
    }
    
    return actual;
}

// ========== PUNTO 2: COMANDOS DEL SISTEMA ==========

bool Gestora::mkdir(string nombre) {
    if(carpetaActual->existeElemento(nombre)) {
        return false; // Ya existe un elemento con ese nombre
    }
    
    string path = construirPath(nombre);
    Carpeta* nuevaCarpeta = new Carpeta(path, nombre);
    carpetaActual->agregarElemento(nuevaCarpeta);
    
    return true;
}

bool Gestora::touch(string nombre, int peso) {
    if(carpetaActual->existeElemento(nombre)) {
        return false; // Ya existe un elemento con ese nombre
    }
    
    string path = construirPath(nombre);
    Archivo* nuevoArchivo = new Archivo(path, nombre, peso);
    carpetaActual->agregarElemento(nuevoArchivo);
    
    return true;
}

bool Gestora::cd(string nombre) {
    if(nombre == "..") {
        // Volver a la carpeta padre
        if(carpetaActual == root) {
            return false; // Ya estamos en root
        }
        
        // Buscar la carpeta padre
        string pathActual = carpetaActual->getPath();
        size_t pos = pathActual.find_last_of('/');
        
        if(pos == 0) {
            carpetaActual = root;
        } else {
            string pathPadre = pathActual.substr(0, pos);
            carpetaActual = buscarCarpetaPorPath(pathPadre);
        }
        
        return carpetaActual != nullptr;
    } else if(nombre == "/") {
        carpetaActual = root;
        return true;
    }
    
    Nodo* elemento = carpetaActual->buscarElemento(nombre);
    
    if(elemento == nullptr || elemento->getTipo() != 'C') {
        return false; // No existe o no es una carpeta
    }
    
    carpetaActual = dynamic_cast<Carpeta*>(elemento);
    return true;
}

void Gestora::ls() {
    vector<Nodo*> elementos = carpetaActual->getElementos();
    
    // Ordenar por nombre usando STL
    Carpeta* carpeta = dynamic_cast<Carpeta*>(carpetaActual);
    if(carpeta != nullptr) {
        carpeta->ordenarPorNombre();
        elementos = carpeta->getElementos();
    }
    
    for(Nodo* elem : elementos) {
        if(elem->getTipo() == 'C') {
            cout << "[DIR] " << elem->getNombre() << endl;
        } else {
            Archivo* arch = dynamic_cast<Archivo*>(elem);
            cout << "[FILE] " << elem->getNombre() << " (" << arch->getPeso() << " bytes)" << endl;
        }
    }
}

void Gestora::lsp() {
    ofstream archivo("display.txt");
    
    if(!archivo.is_open()) {
        cout << "Error al crear display.txt" << endl;
        return;
    }
    
    vector<Nodo*> elementos = carpetaActual->getElementos();
    
    // Ordenar por nombre usando STL
    Carpeta* carpeta = dynamic_cast<Carpeta*>(carpetaActual);
    if(carpeta != nullptr) {
        carpeta->ordenarPorNombre();
        elementos = carpeta->getElementos();
    }
    
    for(Nodo* elem : elementos) {
        if(elem->getTipo() == 'C') {
            Carpeta* carp = dynamic_cast<Carpeta*>(elem);
            archivo << "[DIR] " << elem->getNombre() << " (Peso: " << carp->obtenerPeso() << " bytes)" << endl;
        } else {
            Archivo* arch = dynamic_cast<Archivo*>(elem);
            archivo << "[FILE] " << elem->getNombre() << " (Peso: " << arch->getPeso() << " bytes)" << endl;
        }
    }
    
    archivo.close();
}

void Gestora::pwd() {
    cout << carpetaActual->getPath() << endl;
}

Carpeta* Gestora::getRoot() {
    return root;
}

Carpeta* Gestora::getCarpetaActual() {
    return carpetaActual;
}
