// ========== agregar para punto libre (ARCHIVO ENTERO) ==========
#include "conjuntopaquetes.h"
#include <cstring>

ConjuntoPaquetes::ConjuntoPaquetes() {
    strcpy(codigo, "");
    strcpy(nombre, "");
    version = 0;
}

ConjuntoPaquetes::ConjuntoPaquetes(char* codigo, char* nombre, int version) {
    strcpy(this->codigo, codigo);
    strcpy(this->nombre, nombre);
    this->version = version;
}

ConjuntoPaquetes::~ConjuntoPaquetes() {
    // No eliminar paquetes porque son agregación (compartidos)
    paquetes.clear();
}

char* ConjuntoPaquetes::getCodigo() {
    return codigo;
}

char* ConjuntoPaquetes::getNombre() {
    return nombre;
}

int ConjuntoPaquetes::getVersion() {
    return version;
}

vector<Paquete*> ConjuntoPaquetes::getPaquetes() {
    return paquetes;
}

int ConjuntoPaquetes::getCantidadPaquetes() {
    return paquetes.size();
}

void ConjuntoPaquetes::setCodigo(char* codigo) {
    strcpy(this->codigo, codigo);
}

void ConjuntoPaquetes::setNombre(char* nombre) {
    strcpy(this->nombre, nombre);
}

void ConjuntoPaquetes::setVersion(int version) {
    this->version = version;
}

void ConjuntoPaquetes::agregarPaquete(Paquete* paquete) {
    paquetes.push_back(paquete);
}

// ========== agregar para punto libre ==========

vector<Paquete*> ConjuntoPaquetes::instalarDependientes() {
    vector<Paquete*> todosLosPaquetes;

    for(Paquete* paq : paquetes) {
        // Agregar el paquete si no está ya en la lista
        bool encontrado = false;
        for(Paquete* p : todosLosPaquetes) {
            if(strcmp(p->getCodigo(), paq->getCodigo()) == 0) {
                encontrado = true;
                break;
            }
        }
        if(!encontrado) {
            todosLosPaquetes.push_back(paq);
        }

        // Agregar todas las dependencias transitivas
        vector<Paquete*> deps = paq->obtenerTodasDependencias();
        for(Paquete* dep : deps) {
            bool encontradoDep = false;
            for(Paquete* p : todosLosPaquetes) {
                if(strcmp(p->getCodigo(), dep->getCodigo()) == 0) {
                    encontradoDep = true;
                    break;
                }
            }
            if(!encontradoDep) {
                todosLosPaquetes.push_back(dep);
            }
        }
    }

    return todosLosPaquetes;
}
