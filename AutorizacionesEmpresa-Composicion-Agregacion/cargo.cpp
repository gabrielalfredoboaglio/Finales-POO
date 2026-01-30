#include "Cargo.h"
#include <cstring>
#include <algorithm>

Cargo::Cargo() {
    id = 0;
    strcpy(nombre, "");
}

Cargo::Cargo(int id, const char* nombre) {
    this->id = id;
    strcpy(this->nombre, nombre);
}

Cargo::~Cargo() {
}

int Cargo::getId() const {
    return id;
}

const char* Cargo::getNombre() const {
    return nombre;
}

vector<string> Cargo::getPermisos() const {
    return permisos;
}

int Cargo::getCantidadPermisos() const {
    return permisos.size();
}

void Cargo::setId(int id) {
    this->id = id;
}

void Cargo::setNombre(const char* nombre) {
    strcpy(this->nombre, nombre);
}

void Cargo::agregarPermiso(const string& permiso) {
    // Verificar que no exista ya
    if(!tienePermiso(permiso)) {
        permisos.push_back(permiso);
    }
}

bool Cargo::tienePermiso(const string& permiso) const {
    // Buscar el permiso en el vector
    return find(permisos.begin(), permisos.end(), permiso) != permisos.end();
}

char Cargo::getTipo() const {
    return 'N';  // 'N' = Normal
}
